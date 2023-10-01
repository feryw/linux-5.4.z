// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *	Dong Aisheng <aisheng.dong@nxp.com>
 */

#include <dt-bindings/pinctrl/pads-imx8qxp.h>
#include <linux/err.h>
#include <linux/firmware/imx/sci.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-imx.h"

static const struct pinctrl_pin_desc imx8qxp_pinctrl_pads[] = {
	IMX_PINCTRL_PIN(IMX8QXP_PCIE_CTRL0_PERST_B),
	IMX_PINCTRL_PIN(IMX8QXP_PCIE_CTRL0_CLKREQ_B),
	IMX_PINCTRL_PIN(IMX8QXP_PCIE_CTRL0_WAKE_B),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_PCIESEP),
	IMX_PINCTRL_PIN(IMX8QXP_USB_SS3_TC0),
	IMX_PINCTRL_PIN(IMX8QXP_USB_SS3_TC1),
	IMX_PINCTRL_PIN(IMX8QXP_USB_SS3_TC2),
	IMX_PINCTRL_PIN(IMX8QXP_USB_SS3_TC3),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_3V3_USB3IO),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_CLK),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_CMD),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA0),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA1),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA2),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA3),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_SD1FIX0),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA4),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA5),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA6),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_DATA7),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_STROBE),
	IMX_PINCTRL_PIN(IMX8QXP_EMMC0_RESET_B),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_SD1FIX1),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_RESET_B),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_VSELECT),
	IMX_PINCTRL_PIN(IMX8QXP_CTL_NAND_RE_P_N),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_WP),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_CD_B),
	IMX_PINCTRL_PIN(IMX8QXP_CTL_NAND_DQS_P_N),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_VSELSEP),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_CLK),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_CMD),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_DATA0),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_DATA1),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_DATA2),
	IMX_PINCTRL_PIN(IMX8QXP_USDHC1_DATA3),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_VSEL3),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_TXC),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_TX_CTL),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_TXD0),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_TXD1),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_TXD2),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_TXD3),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_ENET_ENETB0),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_RXC),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_RX_CTL),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_RXD0),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_RXD1),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_RXD2),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_RGMII_RXD3),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_ENET_ENETB1),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_REFCLK_125M_25M),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_MDIO),
	IMX_PINCTRL_PIN(IMX8QXP_ENET0_MDC),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_GPIOCT),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_FSR),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_FST),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_SCKR),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_SCKT),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_TX0),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_TX1),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_TX2_RX3),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_TX3_RX2),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_TX4_RX1),
	IMX_PINCTRL_PIN(IMX8QXP_ESAI0_TX5_RX0),
	IMX_PINCTRL_PIN(IMX8QXP_SPDIF0_RX),
	IMX_PINCTRL_PIN(IMX8QXP_SPDIF0_TX),
	IMX_PINCTRL_PIN(IMX8QXP_SPDIF0_EXT_CLK),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_GPIORHB),
	IMX_PINCTRL_PIN(IMX8QXP_SPI3_SCK),
	IMX_PINCTRL_PIN(IMX8QXP_SPI3_SDO),
	IMX_PINCTRL_PIN(IMX8QXP_SPI3_SDI),
	IMX_PINCTRL_PIN(IMX8QXP_SPI3_CS0),
	IMX_PINCTRL_PIN(IMX8QXP_SPI3_CS1),
	IMX_PINCTRL_PIN(IMX8QXP_MCLK_IN1),
	IMX_PINCTRL_PIN(IMX8QXP_MCLK_IN0),
	IMX_PINCTRL_PIN(IMX8QXP_MCLK_OUT0),
	IMX_PINCTRL_PIN(IMX8QXP_UART1_TX),
	IMX_PINCTRL_PIN(IMX8QXP_UART1_RX),
	IMX_PINCTRL_PIN(IMX8QXP_UART1_RTS_B),
	IMX_PINCTRL_PIN(IMX8QXP_UART1_CTS_B),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_GPIORHK),
	IMX_PINCTRL_PIN(IMX8QXP_SAI0_TXD),
	IMX_PINCTRL_PIN(IMX8QXP_SAI0_TXC),
	IMX_PINCTRL_PIN(IMX8QXP_SAI0_RXD),
	IMX_PINCTRL_PIN(IMX8QXP_SAI0_TXFS),
	IMX_PINCTRL_PIN(IMX8QXP_SAI1_RXD),
	IMX_PINCTRL_PIN(IMX8QXP_SAI1_RXC),
	IMX_PINCTRL_PIN(IMX8QXP_SAI1_RXFS),
	IMX_PINCTRL_PIN(IMX8QXP_SPI2_CS0),
	IMX_PINCTRL_PIN(IMX8QXP_SPI2_SDO),
	IMX_PINCTRL_PIN(IMX8QXP_SPI2_SDI),
	IMX_PINCTRL_PIN(IMX8QXP_SPI2_SCK),
	IMX_PINCTRL_PIN(IMX8QXP_SPI0_SCK),
	IMX_PINCTRL_PIN(IMX8QXP_SPI0_SDI),
	IMX_PINCTRL_PIN(IMX8QXP_SPI0_SDO),
	IMX_PINCTRL_PIN(IMX8QXP_SPI0_CS1),
	IMX_PINCTRL_PIN(IMX8QXP_SPI0_CS0),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_GPIORHT),
	IMX_PINCTRL_PIN(IMX8QXP_ADC_IN1),
	IMX_PINCTRL_PIN(IMX8QXP_ADC_IN0),
	IMX_PINCTRL_PIN(IMX8QXP_ADC_IN3),
	IMX_PINCTRL_PIN(IMX8QXP_ADC_IN2),
	IMX_PINCTRL_PIN(IMX8QXP_ADC_IN5),
	IMX_PINCTRL_PIN(IMX8QXP_ADC_IN4),
	IMX_PINCTRL_PIN(IMX8QXP_FLEXCAN0_RX),
	IMX_PINCTRL_PIN(IMX8QXP_FLEXCAN0_TX),
	IMX_PINCTRL_PIN(IMX8QXP_FLEXCAN1_RX),
	IMX_PINCTRL_PIN(IMX8QXP_FLEXCAN1_TX),
	IMX_PINCTRL_PIN(IMX8QXP_FLEXCAN2_RX),
	IMX_PINCTRL_PIN(IMX8QXP_FLEXCAN2_TX),
	IMX_PINCTRL_PIN(IMX8QXP_UART0_RX),
	IMX_PINCTRL_PIN(IMX8QXP_UART0_TX),
	IMX_PINCTRL_PIN(IMX8QXP_UART2_TX),
	IMX_PINCTRL_PIN(IMX8QXP_UART2_RX),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_GPIOLH),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI0_I2C0_SCL),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI0_I2C0_SDA),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI0_GPIO0_00),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI0_GPIO0_01),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI1_I2C0_SCL),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI1_I2C0_SDA),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI1_GPIO0_00),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_DSI1_GPIO0_01),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_MIPIDSIGPIO),
	IMX_PINCTRL_PIN(IMX8QXP_JTAG_TRST_B),
	IMX_PINCTRL_PIN(IMX8QXP_PMIC_I2C_SCL),
	IMX_PINCTRL_PIN(IMX8QXP_PMIC_I2C_SDA),
	IMX_PINCTRL_PIN(IMX8QXP_PMIC_INT_B),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_GPIO0_00),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_GPIO0_01),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_PMIC_STANDBY),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_BOOT_MODE0),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_BOOT_MODE1),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_BOOT_MODE2),
	IMX_PINCTRL_PIN(IMX8QXP_SCU_BOOT_MODE3),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D00),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D01),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D02),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D03),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D04),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D05),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D06),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_D07),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_HSYNC),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_VSYNC),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_PCLK),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_MCLK),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_EN),
	IMX_PINCTRL_PIN(IMX8QXP_CSI_RESET),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_GPIORHD),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_CSI0_MCLK_OUT),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_CSI0_I2C0_SCL),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_CSI0_I2C0_SDA),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_CSI0_GPIO0_01),
	IMX_PINCTRL_PIN(IMX8QXP_MIPI_CSI0_GPIO0_00),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_DATA0),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_DATA1),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_DATA2),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_DATA3),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_DQS),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_SS0_B),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_SS1_B),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0A_SCLK),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_QSPI0A),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_SCLK),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_DATA0),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_DATA1),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_DATA2),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_DATA3),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_DQS),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_SS0_B),
	IMX_PINCTRL_PIN(IMX8QXP_QSPI0B_SS1_B),
	IMX_PINCTRL_PIN(IMX8QXP_COMP_CTL_GPIO_1V8_3V3_QSPI0B),
};

static struct imx_pinctrl_soc_info imx8qxp_pinctrl_info = {
	.pins = imx8qxp_pinctrl_pads,
	.npins = ARRAY_SIZE(imx8qxp_pinctrl_pads),
	.flags = IMX_USE_SCU,
};

static const struct of_device_id imx8qxp_pinctrl_of_match[] = {
	{ .compatible = "fsl,imx8qxp-iomuxc", },
	{ /* sentinel */ }
};

static int imx8qxp_pinctrl_probe(struct platform_device *pdev)
{
	int ret;

	ret = imx_pinctrl_sc_ipc_init(pdev);
	if (ret)
		return ret;

	return imx_pinctrl_probe(pdev, &imx8qxp_pinctrl_info);
}

static struct platform_driver imx8qxp_pinctrl_driver = {
	.driver = {
		.name = "imx8qxp-pinctrl",
		.of_match_table = of_match_ptr(imx8qxp_pinctrl_of_match),
		.suppress_bind_attrs = true,
	},
	.probe = imx8qxp_pinctrl_probe,
};

static int __init imx8qxp_pinctrl_init(void)
{
	return platform_driver_register(&imx8qxp_pinctrl_driver);
}
arch_initcall(imx8qxp_pinctrl_init);
