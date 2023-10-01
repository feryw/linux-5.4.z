// SPDX-License-Identifier: GPL-2.0-only
/*
 * HDMI interface DSS driver for TI's OMAP4 family of SoCs.
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - http://www.ti.com/
 * Authors: Yong Zhi
 *	Mythri pk <mythripk@ti.com>
 */

#define DSS_SUBSYS_NAME "HDMI"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/component.h>
#include <linux/of.h>
#include <linux/of_graph.h>
#include <sound/omap-hdmi-audio.h>
#include <media/cec.h>

#include "omapdss.h"
#include "hdmi4_core.h"
#include "hdmi4_cec.h"
#include "dss.h"
#include "hdmi.h"

static int hdmi_runtime_get(struct omap_hdmi *hdmi)
{
	int r;

	DSSDBG("hdmi_runtime_get\n");

	r = pm_runtime_get_sync(&hdmi->pdev->dev);
	WARN_ON(r < 0);
	if (r < 0)
		return r;

	return 0;
}

static void hdmi_runtime_put(struct omap_hdmi *hdmi)
{
	int r;

	DSSDBG("hdmi_runtime_put\n");

	r = pm_runtime_put_sync(&hdmi->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
}

static irqreturn_t hdmi_irq_handler(int irq, void *data)
{
	struct omap_hdmi *hdmi = data;
	struct hdmi_wp_data *wp = &hdmi->wp;
	u32 irqstatus;

	irqstatus = hdmi_wp_get_irqstatus(wp);
	hdmi_wp_set_irqstatus(wp, irqstatus);

	if ((irqstatus & HDMI_IRQ_LINK_CONNECT) &&
			irqstatus & HDMI_IRQ_LINK_DISCONNECT) {
		/*
		 * If we get both connect and disconnect interrupts at the same
		 * time, turn off the PHY, clear interrupts, and restart, which
		 * raises connect interrupt if a cable is connected, or nothing
		 * if cable is not connected.
		 */
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_OFF);

		hdmi_wp_set_irqstatus(wp, HDMI_IRQ_LINK_CONNECT |
				HDMI_IRQ_LINK_DISCONNECT);

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	} else if (irqstatus & HDMI_IRQ_LINK_CONNECT) {
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_TXON);
	} else if (irqstatus & HDMI_IRQ_LINK_DISCONNECT) {
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	}
	if (irqstatus & HDMI_IRQ_CORE) {
		u32 intr4 = hdmi_read_reg(hdmi->core.base, HDMI_CORE_SYS_INTR4);

		hdmi_write_reg(hdmi->core.base, HDMI_CORE_SYS_INTR4, intr4);
		if (intr4 & 8)
			hdmi4_cec_irq(&hdmi->core);
	}

	return IRQ_HANDLED;
}

static int hdmi_power_on_core(struct omap_hdmi *hdmi)
{
	int r;

	if (hdmi->core.core_pwr_cnt++)
		return 0;

	r = regulator_enable(hdmi->vdda_reg);
	if (r)
		goto err_reg_enable;

	r = hdmi_runtime_get(hdmi);
	if (r)
		goto err_runtime_get;

	hdmi4_core_powerdown_disable(&hdmi->core);

	/* Make selection of HDMI in DSS */
	dss_select_hdmi_venc_clk_source(hdmi->dss, DSS_HDMI_M_PCLK);

	hdmi->core_enabled = true;

	return 0;

err_runtime_get:
	regulator_disable(hdmi->vdda_reg);
err_reg_enable:
	hdmi->core.core_pwr_cnt--;

	return r;
}

static void hdmi_power_off_core(struct omap_hdmi *hdmi)
{
	if (--hdmi->core.core_pwr_cnt)
		return;

	hdmi->core_enabled = false;

	hdmi_runtime_put(hdmi);
	regulator_disable(hdmi->vdda_reg);
}

static int hdmi_power_on_full(struct omap_hdmi *hdmi)
{
	int r;
	const struct videomode *vm;
	struct hdmi_wp_data *wp = &hdmi->wp;
	struct dss_pll_clock_info hdmi_cinfo = { 0 };
	unsigned int pc;

	r = hdmi_power_on_core(hdmi);
	if (r)
		return r;

	/* disable and clear irqs */
	hdmi_wp_clear_irqenable(wp, ~HDMI_IRQ_CORE);
	hdmi_wp_set_irqstatus(wp, ~HDMI_IRQ_CORE);

	vm = &hdmi->cfg.vm;

	DSSDBG("hdmi_power_on hactive= %d vactive = %d\n", vm->hactive,
	       vm->vactive);

	pc = vm->pixelclock;
	if (vm->flags & DISPLAY_FLAGS_DOUBLECLK)
		pc *= 2;

	/* DSS_HDMI_TCLK is bitclk / 10 */
	pc *= 10;

	dss_pll_calc_b(&hdmi->pll.pll, clk_get_rate(hdmi->pll.pll.clkin),
		pc, &hdmi_cinfo);

	r = dss_pll_enable(&hdmi->pll.pll);
	if (r) {
		DSSERR("Failed to enable PLL\n");
		goto err_pll_enable;
	}

	r = dss_pll_set_config(&hdmi->pll.pll, &hdmi_cinfo);
	if (r) {
		DSSERR("Failed to configure PLL\n");
		goto err_pll_cfg;
	}

	r = hdmi_phy_configure(&hdmi->phy, hdmi_cinfo.clkdco,
		hdmi_cinfo.clkout[0]);
	if (r) {
		DSSDBG("Failed to configure PHY\n");
		goto err_phy_cfg;
	}

	r = hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	if (r)
		goto err_phy_pwr;

	hdmi4_configure(&hdmi->core, &hdmi->wp, &hdmi->cfg);

	r = dss_mgr_enable(&hdmi->output);
	if (r)
		goto err_mgr_enable;

	r = hdmi_wp_video_start(&hdmi->wp);
	if (r)
		goto err_vid_enable;

	hdmi_wp_set_irqenable(wp,
		HDMI_IRQ_LINK_CONNECT | HDMI_IRQ_LINK_DISCONNECT);

	return 0;

err_vid_enable:
	dss_mgr_disable(&hdmi->output);
err_mgr_enable:
	hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_OFF);
err_phy_pwr:
err_phy_cfg:
err_pll_cfg:
	dss_pll_disable(&hdmi->pll.pll);
err_pll_enable:
	hdmi_power_off_core(hdmi);
	return -EIO;
}

static void hdmi_power_off_full(struct omap_hdmi *hdmi)
{
	hdmi_wp_clear_irqenable(&hdmi->wp, ~HDMI_IRQ_CORE);

	hdmi_wp_video_stop(&hdmi->wp);

	dss_mgr_disable(&hdmi->output);

	hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_OFF);

	dss_pll_disable(&hdmi->pll.pll);

	hdmi_power_off_core(hdmi);
}

static void hdmi_display_set_timings(struct omap_dss_device *dssdev,
				     const struct drm_display_mode *mode)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	mutex_lock(&hdmi->lock);

	drm_display_mode_to_videomode(mode, &hdmi->cfg.vm);

	dispc_set_tv_pclk(hdmi->dss->dispc, mode->clock * 1000);

	mutex_unlock(&hdmi->lock);
}

static int hdmi_dump_regs(struct seq_file *s, void *p)
{
	struct omap_hdmi *hdmi = s->private;

	mutex_lock(&hdmi->lock);

	if (hdmi_runtime_get(hdmi)) {
		mutex_unlock(&hdmi->lock);
		return 0;
	}

	hdmi_wp_dump(&hdmi->wp, s);
	hdmi_pll_dump(&hdmi->pll, s);
	hdmi_phy_dump(&hdmi->phy, s);
	hdmi4_core_dump(&hdmi->core, s);

	hdmi_runtime_put(hdmi);
	mutex_unlock(&hdmi->lock);
	return 0;
}

static int read_edid(struct omap_hdmi *hdmi, u8 *buf, int len)
{
	int r;

	mutex_lock(&hdmi->lock);

	r = hdmi_runtime_get(hdmi);
	BUG_ON(r);

	r = hdmi4_read_edid(&hdmi->core,  buf, len);

	hdmi_runtime_put(hdmi);
	mutex_unlock(&hdmi->lock);

	return r;
}

static void hdmi_start_audio_stream(struct omap_hdmi *hd)
{
	hdmi_wp_audio_enable(&hd->wp, true);
	hdmi4_audio_start(&hd->core, &hd->wp);
}

static void hdmi_stop_audio_stream(struct omap_hdmi *hd)
{
	hdmi4_audio_stop(&hd->core, &hd->wp);
	hdmi_wp_audio_enable(&hd->wp, false);
}

static void hdmi_display_enable(struct omap_dss_device *dssdev)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	unsigned long flags;
	int r;

	DSSDBG("ENTER hdmi_display_enable\n");

	mutex_lock(&hdmi->lock);

	r = hdmi_power_on_full(hdmi);
	if (r) {
		DSSERR("failed to power on device\n");
		goto done;
	}

	if (hdmi->audio_configured) {
		r = hdmi4_audio_config(&hdmi->core, &hdmi->wp,
				       &hdmi->audio_config,
				       hdmi->cfg.vm.pixelclock);
		if (r) {
			DSSERR("Error restoring audio configuration: %d", r);
			hdmi->audio_abort_cb(&hdmi->pdev->dev);
			hdmi->audio_configured = false;
		}
	}

	spin_lock_irqsave(&hdmi->audio_playing_lock, flags);
	if (hdmi->audio_configured && hdmi->audio_playing)
		hdmi_start_audio_stream(hdmi);
	hdmi->display_enabled = true;
	spin_unlock_irqrestore(&hdmi->audio_playing_lock, flags);

done:
	mutex_unlock(&hdmi->lock);
}

static void hdmi_display_disable(struct omap_dss_device *dssdev)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	unsigned long flags;

	DSSDBG("Enter hdmi_display_disable\n");

	mutex_lock(&hdmi->lock);

	spin_lock_irqsave(&hdmi->audio_playing_lock, flags);
	hdmi_stop_audio_stream(hdmi);
	hdmi->display_enabled = false;
	spin_unlock_irqrestore(&hdmi->audio_playing_lock, flags);

	hdmi_power_off_full(hdmi);

	mutex_unlock(&hdmi->lock);
}

int hdmi4_core_enable(struct hdmi_core_data *core)
{
	struct omap_hdmi *hdmi = container_of(core, struct omap_hdmi, core);
	int r = 0;

	DSSDBG("ENTER omapdss_hdmi4_core_enable\n");

	mutex_lock(&hdmi->lock);

	r = hdmi_power_on_core(hdmi);
	if (r) {
		DSSERR("failed to power on device\n");
		goto err0;
	}

	mutex_unlock(&hdmi->lock);
	return 0;

err0:
	mutex_unlock(&hdmi->lock);
	return r;
}

void hdmi4_core_disable(struct hdmi_core_data *core)
{
	struct omap_hdmi *hdmi = container_of(core, struct omap_hdmi, core);

	DSSDBG("Enter omapdss_hdmi4_core_disable\n");

	mutex_lock(&hdmi->lock);

	hdmi_power_off_core(hdmi);

	mutex_unlock(&hdmi->lock);
}

static int hdmi_connect(struct omap_dss_device *src,
			struct omap_dss_device *dst)
{
	return omapdss_device_connect(dst->dss, dst, dst->next);
}

static void hdmi_disconnect(struct omap_dss_device *src,
			    struct omap_dss_device *dst)
{
	omapdss_device_disconnect(dst, dst->next);
}

static int hdmi_read_edid(struct omap_dss_device *dssdev,
		u8 *edid, int len)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	bool need_enable;
	int r;

	need_enable = hdmi->core_enabled == false;

	if (need_enable) {
		r = hdmi4_core_enable(&hdmi->core);
		if (r)
			return r;
	}

	r = read_edid(hdmi, edid, len);
	if (r >= 256)
		hdmi4_cec_set_phys_addr(&hdmi->core,
					cec_get_edid_phys_addr(edid, r, NULL));
	else
		hdmi4_cec_set_phys_addr(&hdmi->core, CEC_PHYS_ADDR_INVALID);
	if (need_enable)
		hdmi4_core_disable(&hdmi->core);

	return r;
}

static void hdmi_lost_hotplug(struct omap_dss_device *dssdev)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	hdmi4_cec_set_phys_addr(&hdmi->core, CEC_PHYS_ADDR_INVALID);
}

static int hdmi_set_infoframe(struct omap_dss_device *dssdev,
		const struct hdmi_avi_infoframe *avi)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	hdmi->cfg.infoframe = *avi;
	return 0;
}

static int hdmi_set_hdmi_mode(struct omap_dss_device *dssdev,
		bool hdmi_mode)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	hdmi->cfg.hdmi_dvi_mode = hdmi_mode ? HDMI_HDMI : HDMI_DVI;
	return 0;
}

static const struct omap_dss_device_ops hdmi_ops = {
	.connect		= hdmi_connect,
	.disconnect		= hdmi_disconnect,

	.enable			= hdmi_display_enable,
	.disable		= hdmi_display_disable,

	.set_timings		= hdmi_display_set_timings,

	.read_edid		= hdmi_read_edid,

	.hdmi = {
		.lost_hotplug		= hdmi_lost_hotplug,
		.set_infoframe		= hdmi_set_infoframe,
		.set_hdmi_mode		= hdmi_set_hdmi_mode,
	},
};

/* -----------------------------------------------------------------------------
 * Audio Callbacks
 */

static int hdmi_audio_startup(struct device *dev,
			      void (*abort_cb)(struct device *dev))
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);

	mutex_lock(&hd->lock);

	WARN_ON(hd->audio_abort_cb != NULL);

	hd->audio_abort_cb = abort_cb;

	mutex_unlock(&hd->lock);

	return 0;
}

static int hdmi_audio_shutdown(struct device *dev)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);

	mutex_lock(&hd->lock);
	hd->audio_abort_cb = NULL;
	hd->audio_configured = false;
	hd->audio_playing = false;
	mutex_unlock(&hd->lock);

	return 0;
}

static int hdmi_audio_start(struct device *dev)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&hd->audio_playing_lock, flags);

	if (hd->display_enabled) {
		if (!hdmi_mode_has_audio(&hd->cfg))
			DSSERR("%s: Video mode does not support audio\n",
			       __func__);
		hdmi_start_audio_stream(hd);
	}
	hd->audio_playing = true;

	spin_unlock_irqrestore(&hd->audio_playing_lock, flags);
	return 0;
}

static void hdmi_audio_stop(struct device *dev)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);
	unsigned long flags;

	WARN_ON(!hdmi_mode_has_audio(&hd->cfg));

	spin_lock_irqsave(&hd->audio_playing_lock, flags);

	if (hd->display_enabled)
		hdmi_stop_audio_stream(hd);
	hd->audio_playing = false;

	spin_unlock_irqrestore(&hd->audio_playing_lock, flags);
}

static int hdmi_audio_config(struct device *dev,
			     struct omap_dss_audio *dss_audio)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);
	int ret = 0;

	mutex_lock(&hd->lock);

	if (hd->display_enabled) {
		ret = hdmi4_audio_config(&hd->core, &hd->wp, dss_audio,
					 hd->cfg.vm.pixelclock);
		if (ret)
			goto out;
	}

	hd->audio_configured = true;
	hd->audio_config = *dss_audio;
out:
	mutex_unlock(&hd->lock);

	return ret;
}

static const struct omap_hdmi_audio_ops hdmi_audio_ops = {
	.audio_startup = hdmi_audio_startup,
	.audio_shutdown = hdmi_audio_shutdown,
	.audio_start = hdmi_audio_start,
	.audio_stop = hdmi_audio_stop,
	.audio_config = hdmi_audio_config,
};

static int hdmi_audio_register(struct omap_hdmi *hdmi)
{
	struct omap_hdmi_audio_pdata pdata = {
		.dev = &hdmi->pdev->dev,
		.version = 4,
		.audio_dma_addr = hdmi_wp_get_audio_dma_addr(&hdmi->wp),
		.ops = &hdmi_audio_ops,
	};

	hdmi->audio_pdev = platform_device_register_data(
		&hdmi->pdev->dev, "omap-hdmi-audio", PLATFORM_DEVID_AUTO,
		&pdata, sizeof(pdata));

	if (IS_ERR(hdmi->audio_pdev))
		return PTR_ERR(hdmi->audio_pdev);

	return 0;
}

/* -----------------------------------------------------------------------------
 * Component Bind & Unbind
 */

static int hdmi4_bind(struct device *dev, struct device *master, void *data)
{
	struct dss_device *dss = dss_get_device(master);
	struct omap_hdmi *hdmi = dev_get_drvdata(dev);
	int r;

	hdmi->dss = dss;

	r = hdmi_runtime_get(hdmi);
	if (r)
		return r;

	r = hdmi_pll_init(dss, hdmi->pdev, &hdmi->pll, &hdmi->wp);
	if (r)
		goto err_runtime_put;

	r = hdmi4_cec_init(hdmi->pdev, &hdmi->core, &hdmi->wp);
	if (r)
		goto err_pll_uninit;

	r = hdmi_audio_register(hdmi);
	if (r) {
		DSSERR("Registering HDMI audio failed\n");
		goto err_cec_uninit;
	}

	hdmi->debugfs = dss_debugfs_create_file(dss, "hdmi", hdmi_dump_regs,
					       hdmi);

	hdmi_runtime_put(hdmi);

	return 0;

err_cec_uninit:
	hdmi4_cec_uninit(&hdmi->core);
err_pll_uninit:
	hdmi_pll_uninit(&hdmi->pll);
err_runtime_put:
	hdmi_runtime_put(hdmi);
	return r;
}

static void hdmi4_unbind(struct device *dev, struct device *master, void *data)
{
	struct omap_hdmi *hdmi = dev_get_drvdata(dev);

	dss_debugfs_remove_file(hdmi->debugfs);

	if (hdmi->audio_pdev)
		platform_device_unregister(hdmi->audio_pdev);

	hdmi4_cec_uninit(&hdmi->core);
	hdmi_pll_uninit(&hdmi->pll);
}

static const struct component_ops hdmi4_component_ops = {
	.bind	= hdmi4_bind,
	.unbind	= hdmi4_unbind,
};

/* -----------------------------------------------------------------------------
 * Probe & Remove, Suspend & Resume
 */

static int hdmi4_init_output(struct omap_hdmi *hdmi)
{
	struct omap_dss_device *out = &hdmi->output;
	int r;

	out->dev = &hdmi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_HDMI;
	out->type = OMAP_DISPLAY_TYPE_HDMI;
	out->name = "hdmi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_DIGIT;
	out->ops = &hdmi_ops;
	out->owner = THIS_MODULE;
	out->of_ports = BIT(0);
	out->ops_flags = OMAP_DSS_DEVICE_OP_EDID;

	r = omapdss_device_init_output(out);
	if (r < 0)
		return r;

	omapdss_device_register(out);

	return 0;
}

static void hdmi4_uninit_output(struct omap_hdmi *hdmi)
{
	struct omap_dss_device *out = &hdmi->output;

	omapdss_device_unregister(out);
	omapdss_device_cleanup_output(out);
}

static int hdmi4_probe_of(struct omap_hdmi *hdmi)
{
	struct platform_device *pdev = hdmi->pdev;
	struct device_node *node = pdev->dev.of_node;
	struct device_node *ep;
	int r;

	ep = of_graph_get_endpoint_by_regs(node, 0, 0);
	if (!ep)
		return 0;

	r = hdmi_parse_lanes_of(pdev, ep, &hdmi->phy);
	of_node_put(ep);
	return r;
}

static int hdmi4_probe(struct platform_device *pdev)
{
	struct omap_hdmi *hdmi;
	int irq;
	int r;

	hdmi = kzalloc(sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->pdev = pdev;

	dev_set_drvdata(&pdev->dev, hdmi);

	mutex_init(&hdmi->lock);
	spin_lock_init(&hdmi->audio_playing_lock);

	r = hdmi4_probe_of(hdmi);
	if (r)
		goto err_free;

	r = hdmi_wp_init(pdev, &hdmi->wp, 4);
	if (r)
		goto err_free;

	r = hdmi_phy_init(pdev, &hdmi->phy, 4);
	if (r)
		goto err_free;

	r = hdmi4_core_init(pdev, &hdmi->core);
	if (r)
		goto err_free;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		goto err_free;
	}

	r = devm_request_threaded_irq(&pdev->dev, irq,
			NULL, hdmi_irq_handler,
			IRQF_ONESHOT, "OMAP HDMI", hdmi);
	if (r) {
		DSSERR("HDMI IRQ request failed\n");
		goto err_free;
	}

	hdmi->vdda_reg = devm_regulator_get(&pdev->dev, "vdda");
	if (IS_ERR(hdmi->vdda_reg)) {
		r = PTR_ERR(hdmi->vdda_reg);
		if (r != -EPROBE_DEFER)
			DSSERR("can't get VDDA regulator\n");
		goto err_free;
	}

	pm_runtime_enable(&pdev->dev);

	r = hdmi4_init_output(hdmi);
	if (r)
		goto err_pm_disable;

	r = component_add(&pdev->dev, &hdmi4_component_ops);
	if (r)
		goto err_uninit_output;

	return 0;

err_uninit_output:
	hdmi4_uninit_output(hdmi);
err_pm_disable:
	pm_runtime_disable(&pdev->dev);
err_free:
	kfree(hdmi);
	return r;
}

static int hdmi4_remove(struct platform_device *pdev)
{
	struct omap_hdmi *hdmi = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &hdmi4_component_ops);

	hdmi4_uninit_output(hdmi);

	pm_runtime_disable(&pdev->dev);

	kfree(hdmi);
	return 0;
}

static const struct of_device_id hdmi_of_match[] = {
	{ .compatible = "ti,omap4-hdmi", },
	{},
};

struct platform_driver omapdss_hdmi4hw_driver = {
	.probe		= hdmi4_probe,
	.remove		= hdmi4_remove,
	.driver         = {
		.name   = "omapdss_hdmi",
		.of_match_table = hdmi_of_match,
		.suppress_bind_attrs = true,
	},
};
