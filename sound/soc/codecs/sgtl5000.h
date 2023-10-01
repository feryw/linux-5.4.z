/* SPDX-License-Identifier: GPL-2.0 */
/*
 * sgtl5000.h - SGTL5000 audio codec interface
 *
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 */

#ifndef _SGTL5000_H
#define _SGTL5000_H

/*
 * Registers addresses
 */
#define SGTL5000_CHIP_ID			0x0000
#define SGTL5000_CHIP_DIG_POWER			0x0002
#define SGTL5000_CHIP_CLK_CTRL			0x0004
#define SGTL5000_CHIP_I2S_CTRL			0x0006
#define SGTL5000_CHIP_SSS_CTRL			0x000a
#define SGTL5000_CHIP_ADCDAC_CTRL		0x000e
#define SGTL5000_CHIP_DAC_VOL			0x0010
#define SGTL5000_CHIP_PAD_STRENGTH		0x0014
#define SGTL5000_CHIP_ANA_ADC_CTRL		0x0020
#define SGTL5000_CHIP_ANA_HP_CTRL		0x0022
#define SGTL5000_CHIP_ANA_CTRL			0x0024
#define SGTL5000_CHIP_LINREG_CTRL		0x0026
#define SGTL5000_CHIP_REF_CTRL			0x0028
#define SGTL5000_CHIP_MIC_CTRL			0x002a
#define SGTL5000_CHIP_LINE_OUT_CTRL		0x002c
#define SGTL5000_CHIP_LINE_OUT_VOL		0x002e
#define SGTL5000_CHIP_ANA_POWER			0x0030
#define SGTL5000_CHIP_PLL_CTRL			0x0032
#define SGTL5000_CHIP_CLK_TOP_CTRL		0x0034
#define SGTL5000_CHIP_ANA_STATUS		0x0036
#define SGTL5000_CHIP_SHORT_CTRL		0x003c
#define SGTL5000_CHIP_ANA_TEST2			0x003a
#define SGTL5000_DAP_CTRL			0x0100
#define SGTL5000_DAP_PEQ			0x0102
#define SGTL5000_DAP_BASS_ENHANCE		0x0104
#define SGTL5000_DAP_BASS_ENHANCE_CTRL		0x0106
#define SGTL5000_DAP_AUDIO_EQ			0x0108
#define SGTL5000_DAP_SURROUND			0x010a
#define SGTL5000_DAP_FLT_COEF_ACCESS		0x010c
#define SGTL5000_DAP_COEF_WR_B0_MSB		0x010e
#define SGTL5000_DAP_COEF_WR_B0_LSB		0x0110
#define SGTL5000_DAP_EQ_BASS_BAND0		0x0116
#define SGTL5000_DAP_EQ_BASS_BAND1		0x0118
#define SGTL5000_DAP_EQ_BASS_BAND2		0x011a
#define SGTL5000_DAP_EQ_BASS_BAND3		0x011c
#define SGTL5000_DAP_EQ_BASS_BAND4		0x011e
#define SGTL5000_DAP_MAIN_CHAN			0x0120
#define SGTL5000_DAP_MIX_CHAN			0x0122
#define SGTL5000_DAP_AVC_CTRL			0x0124
#define SGTL5000_DAP_AVC_THRESHOLD		0x0126
#define SGTL5000_DAP_AVC_ATTACK			0x0128
#define SGTL5000_DAP_AVC_DECAY			0x012a
#define SGTL5000_DAP_COEF_WR_B1_MSB		0x012c
#define SGTL5000_DAP_COEF_WR_B1_LSB		0x012e
#define SGTL5000_DAP_COEF_WR_B2_MSB		0x0130
#define SGTL5000_DAP_COEF_WR_B2_LSB		0x0132
#define SGTL5000_DAP_COEF_WR_A1_MSB		0x0134
#define SGTL5000_DAP_COEF_WR_A1_LSB		0x0136
#define SGTL5000_DAP_COEF_WR_A2_MSB		0x0138
#define SGTL5000_DAP_COEF_WR_A2_LSB		0x013a

/*
 * Field Definitions.
 */

/*
 * SGTL5000_CHIP_ID
 */
#define SGTL5000_PARTID_MASK			0xff00
#define SGTL5000_PARTID_SHIFT			8
#define SGTL5000_PARTID_WIDTH			8
#define SGTL5000_PARTID_PART_ID			0xa0
#define SGTL5000_REVID_MASK			0x00ff
#define SGTL5000_REVID_SHIFT			0
#define SGTL5000_REVID_WIDTH			8

/*
 * SGTL5000_CHIP_DIG_POWER
 */
#define SGTL5000_ADC_EN				0x0040
#define SGTL5000_DAC_EN				0x0020
#define SGTL5000_DAP_POWERUP			0x0010
#define SGTL5000_I2S_OUT_POWERUP		0x0002
#define SGTL5000_I2S_IN_POWERUP			0x0001

/*
 * SGTL5000_CHIP_CLK_CTRL
 */
#define SGTL5000_CHIP_CLK_CTRL_DEFAULT		0x0008
#define SGTL5000_RATE_MODE_MASK			0x0030
#define SGTL5000_RATE_MODE_SHIFT		4
#define SGTL5000_RATE_MODE_WIDTH		2
#define SGTL5000_RATE_MODE_DIV_1		0
#define SGTL5000_RATE_MODE_DIV_2		1
#define SGTL5000_RATE_MODE_DIV_4		2
#define SGTL5000_RATE_MODE_DIV_6		3
#define SGTL5000_SYS_FS_MASK			0x000c
#define SGTL5000_SYS_FS_SHIFT			2
#define SGTL5000_SYS_FS_WIDTH			2
#define SGTL5000_SYS_FS_32k			0x0
#define SGTL5000_SYS_FS_44_1k			0x1
#define SGTL5000_SYS_FS_48k			0x2
#define SGTL5000_SYS_FS_96k			0x3
#define SGTL5000_MCLK_FREQ_MASK			0x0003
#define SGTL5000_MCLK_FREQ_SHIFT		0
#define SGTL5000_MCLK_FREQ_WIDTH		2
#define SGTL5000_MCLK_FREQ_256FS		0x0
#define SGTL5000_MCLK_FREQ_384FS		0x1
#define SGTL5000_MCLK_FREQ_512FS		0x2
#define SGTL5000_MCLK_FREQ_PLL			0x3

/*
 * SGTL5000_CHIP_I2S_CTRL
 */
#define SGTL5000_I2S_SCLKFREQ_MASK		0x0100
#define SGTL5000_I2S_SCLKFREQ_SHIFT		8
#define SGTL5000_I2S_SCLKFREQ_WIDTH		1
#define SGTL5000_I2S_SCLKFREQ_64FS		0x0
#define SGTL5000_I2S_SCLKFREQ_32FS		0x1	/* Not for RJ mode */
#define SGTL5000_I2S_MASTER			0x0080
#define SGTL5000_I2S_SCLK_INV			0x0040
#define SGTL5000_I2S_DLEN_MASK			0x0030
#define SGTL5000_I2S_DLEN_SHIFT			4
#define SGTL5000_I2S_DLEN_WIDTH			2
#define SGTL5000_I2S_DLEN_32			0x0
#define SGTL5000_I2S_DLEN_24			0x1
#define SGTL5000_I2S_DLEN_20			0x2
#define SGTL5000_I2S_DLEN_16			0x3
#define SGTL5000_I2S_MODE_MASK			0x000c
#define SGTL5000_I2S_MODE_SHIFT			2
#define SGTL5000_I2S_MODE_WIDTH			2
#define SGTL5000_I2S_MODE_I2S_LJ		0x0
#define SGTL5000_I2S_MODE_RJ			0x1
#define SGTL5000_I2S_MODE_PCM			0x2
#define SGTL5000_I2S_LRALIGN			0x0002
#define SGTL5000_I2S_LRPOL			0x0001	/* set for which mode */

/*
 * SGTL5000_CHIP_SSS_CTRL
 */
#define SGTL5000_DAP_MIX_LRSWAP			0x4000
#define SGTL5000_DAP_LRSWAP			0x2000
#define SGTL5000_DAC_LRSWAP			0x1000
#define SGTL5000_I2S_OUT_LRSWAP			0x0400
#define SGTL5000_DAP_MIX_SEL_MASK		0x0300
#define SGTL5000_DAP_MIX_SEL_SHIFT		8
#define SGTL5000_DAP_MIX_SEL_WIDTH		2
#define SGTL5000_DAP_MIX_SEL_ADC		0x0
#define SGTL5000_DAP_MIX_SEL_I2S_IN		0x1
#define SGTL5000_DAP_SEL_MASK			0x00c0
#define SGTL5000_DAP_SEL_SHIFT			6
#define SGTL5000_DAP_SEL_WIDTH			2
#define SGTL5000_DAP_SEL_ADC			0x0
#define SGTL5000_DAP_SEL_I2S_IN			0x1
#define SGTL5000_DAC_SEL_MASK			0x0030
#define SGTL5000_DAC_SEL_SHIFT			4
#define SGTL5000_DAC_SEL_WIDTH			2
#define SGTL5000_DAC_SEL_ADC			0x0
#define SGTL5000_DAC_SEL_I2S_IN			0x1
#define SGTL5000_DAC_SEL_DAP			0x3
#define SGTL5000_I2S_OUT_SEL_MASK		0x0003
#define SGTL5000_I2S_OUT_SEL_SHIFT		0
#define SGTL5000_I2S_OUT_SEL_WIDTH		2
#define SGTL5000_I2S_OUT_SEL_ADC		0x0
#define SGTL5000_I2S_OUT_SEL_I2S_IN		0x1
#define SGTL5000_I2S_OUT_SEL_DAP		0x3

/*
 * SGTL5000_CHIP_ADCDAC_CTRL
 */
#define SGTL5000_VOL_BUSY_DAC_RIGHT		0x2000
#define SGTL5000_VOL_BUSY_DAC_LEFT		0x1000
#define SGTL5000_DAC_VOL_RAMP_EN		0x0200
#define SGTL5000_DAC_VOL_RAMP_EXPO		0x0100
#define SGTL5000_DAC_MUTE_RIGHT			0x0008
#define SGTL5000_DAC_MUTE_LEFT			0x0004
#define SGTL5000_ADC_HPF_FREEZE			0x0002
#define SGTL5000_ADC_HPF_BYPASS			0x0001

/*
 * SGTL5000_CHIP_DAC_VOL
 */
#define SGTL5000_DAC_VOL_RIGHT_MASK		0xff00
#define SGTL5000_DAC_VOL_RIGHT_SHIFT		8
#define SGTL5000_DAC_VOL_RIGHT_WIDTH		8
#define SGTL5000_DAC_VOL_LEFT_MASK		0x00ff
#define SGTL5000_DAC_VOL_LEFT_SHIFT		0
#define SGTL5000_DAC_VOL_LEFT_WIDTH		8

/*
 * SGTL5000_CHIP_PAD_STRENGTH
 */
#define SGTL5000_PAD_I2S_LRCLK_MASK		0x0300
#define SGTL5000_PAD_I2S_LRCLK_SHIFT		8
#define SGTL5000_PAD_I2S_LRCLK_WIDTH		2
#define SGTL5000_PAD_I2S_SCLK_MASK		0x00c0
#define SGTL5000_PAD_I2S_SCLK_SHIFT		6
#define SGTL5000_PAD_I2S_SCLK_WIDTH		2
#define SGTL5000_PAD_I2S_DOUT_MASK		0x0030
#define SGTL5000_PAD_I2S_DOUT_SHIFT		4
#define SGTL5000_PAD_I2S_DOUT_WIDTH		2
#define SGTL5000_PAD_I2C_SDA_MASK		0x000c
#define SGTL5000_PAD_I2C_SDA_SHIFT		2
#define SGTL5000_PAD_I2C_SDA_WIDTH		2
#define SGTL5000_PAD_I2C_SCL_MASK		0x0003
#define SGTL5000_PAD_I2C_SCL_SHIFT		0
#define SGTL5000_PAD_I2C_SCL_WIDTH		2

/*
 * SGTL5000_CHIP_ANA_ADC_CTRL
 */
#define SGTL5000_ADC_VOL_M6DB			0x0100
#define SGTL5000_ADC_VOL_RIGHT_MASK		0x00f0
#define SGTL5000_ADC_VOL_RIGHT_SHIFT		4
#define SGTL5000_ADC_VOL_RIGHT_WIDTH		4
#define SGTL5000_ADC_VOL_LEFT_MASK		0x000f
#define SGTL5000_ADC_VOL_LEFT_SHIFT		0
#define SGTL5000_ADC_VOL_LEFT_WIDTH		4

/*
 * SGTL5000_CHIP_ANA_HP_CTRL
 */
#define SGTL5000_HP_VOL_RIGHT_MASK		0x7f00
#define SGTL5000_HP_VOL_RIGHT_SHIFT		8
#define SGTL5000_HP_VOL_RIGHT_WIDTH		7
#define SGTL5000_HP_VOL_LEFT_MASK		0x007f
#define SGTL5000_HP_VOL_LEFT_SHIFT		0
#define SGTL5000_HP_VOL_LEFT_WIDTH		7

/*
 * SGTL5000_CHIP_ANA_CTRL
 */
#define SGTL5000_LINE_OUT_MUTE			0x0100
#define SGTL5000_HP_SEL_MASK			0x0040
#define SGTL5000_HP_SEL_SHIFT			6
#define SGTL5000_HP_SEL_WIDTH			1
#define SGTL5000_HP_SEL_DAC			0x0
#define SGTL5000_HP_SEL_LINE_IN			0x1
#define SGTL5000_HP_ZCD_EN			0x0020
#define SGTL5000_HP_MUTE			0x0010
#define SGTL5000_ADC_SEL_MASK			0x0004
#define SGTL5000_ADC_SEL_SHIFT			2
#define SGTL5000_ADC_SEL_WIDTH			1
#define SGTL5000_ADC_SEL_MIC			0x0
#define SGTL5000_ADC_SEL_LINE_IN		0x1
#define SGTL5000_ADC_ZCD_EN			0x0002
#define SGTL5000_ADC_MUTE			0x0001

/*
 * SGTL5000_CHIP_LINREG_CTRL
 */
#define SGTL5000_VDDC_MAN_ASSN_MASK		0x0040
#define SGTL5000_VDDC_MAN_ASSN_SHIFT		6
#define SGTL5000_VDDC_MAN_ASSN_WIDTH		1
#define SGTL5000_VDDC_MAN_ASSN_VDDA		0x0
#define SGTL5000_VDDC_MAN_ASSN_VDDIO		0x1
#define SGTL5000_VDDC_ASSN_OVRD			0x0020
#define SGTL5000_LINREG_VDDD_MASK		0x000f
#define SGTL5000_LINREG_VDDD_SHIFT		0
#define SGTL5000_LINREG_VDDD_WIDTH		4

/*
 * SGTL5000_CHIP_REF_CTRL
 */
#define SGTL5000_ANA_GND_MASK			0x01f0
#define SGTL5000_ANA_GND_SHIFT			4
#define SGTL5000_ANA_GND_WIDTH			5
#define SGTL5000_ANA_GND_BASE			800	/* mv */
#define SGTL5000_ANA_GND_STP			25	/*mv */
#define SGTL5000_BIAS_CTRL_MASK			0x000e
#define SGTL5000_BIAS_CTRL_SHIFT		1
#define SGTL5000_BIAS_CTRL_WIDTH		3
#define SGTL5000_SMALL_POP			0x0001

/*
 * SGTL5000_CHIP_MIC_CTRL
 */
#define SGTL5000_BIAS_R_MASK			0x0300
#define SGTL5000_BIAS_R_SHIFT			8
#define SGTL5000_BIAS_R_WIDTH			2
#define SGTL5000_BIAS_R_off			0x0
#define SGTL5000_BIAS_R_2K			0x1
#define SGTL5000_BIAS_R_4k			0x2
#define SGTL5000_BIAS_R_8k			0x3
#define SGTL5000_BIAS_VOLT_MASK			0x0070
#define SGTL5000_BIAS_VOLT_SHIFT		4
#define SGTL5000_BIAS_VOLT_WIDTH		3
#define SGTL5000_MIC_GAIN_MASK			0x0003
#define SGTL5000_MIC_GAIN_SHIFT			0
#define SGTL5000_MIC_GAIN_WIDTH			2

/*
 * SGTL5000_CHIP_LINE_OUT_CTRL
 */
#define SGTL5000_LINE_OUT_CURRENT_MASK		0x0f00
#define SGTL5000_LINE_OUT_CURRENT_SHIFT		8
#define SGTL5000_LINE_OUT_CURRENT_WIDTH		4
#define SGTL5000_LINE_OUT_CURRENT_180u		0x0
#define SGTL5000_LINE_OUT_CURRENT_270u		0x1
#define SGTL5000_LINE_OUT_CURRENT_360u		0x3
#define SGTL5000_LINE_OUT_CURRENT_450u		0x7
#define SGTL5000_LINE_OUT_CURRENT_540u		0xf
#define SGTL5000_LINE_OUT_GND_MASK		0x003f
#define SGTL5000_LINE_OUT_GND_SHIFT		0
#define SGTL5000_LINE_OUT_GND_WIDTH		6
#define SGTL5000_LINE_OUT_GND_BASE		800	/* mv */
#define SGTL5000_LINE_OUT_GND_STP		25
#define SGTL5000_LINE_OUT_GND_MAX		0x23

/*
 * SGTL5000_CHIP_LINE_OUT_VOL
 */
#define SGTL5000_LINE_OUT_VOL_RIGHT_MASK	0x1f00
#define SGTL5000_LINE_OUT_VOL_RIGHT_SHIFT	8
#define SGTL5000_LINE_OUT_VOL_RIGHT_WIDTH	5
#define SGTL5000_LINE_OUT_VOL_LEFT_MASK		0x001f
#define SGTL5000_LINE_OUT_VOL_LEFT_SHIFT	0
#define SGTL5000_LINE_OUT_VOL_LEFT_WIDTH	5

/*
 * SGTL5000_CHIP_ANA_POWER
 */
#define SGTL5000_ANA_POWER_DEFAULT		0x7060
#define SGTL5000_DAC_STEREO			0x4000
#define SGTL5000_LINREG_SIMPLE_POWERUP		0x2000
#define SGTL5000_STARTUP_POWERUP		0x1000
#define SGTL5000_VDDC_CHRGPMP_POWERUP		0x0800
#define SGTL5000_PLL_POWERUP			0x0400
#define SGTL5000_LINEREG_D_POWERUP		0x0200
#define SGTL5000_VCOAMP_POWERUP			0x0100
#define SGTL5000_VAG_POWERUP			0x0080
#define SGTL5000_ADC_STEREO			0x0040
#define SGTL5000_REFTOP_POWERUP			0x0020
#define SGTL5000_HP_POWERUP			0x0010
#define SGTL5000_DAC_POWERUP			0x0008
#define SGTL5000_CAPLESS_HP_POWERUP		0x0004
#define SGTL5000_ADC_POWERUP			0x0002
#define SGTL5000_LINE_OUT_POWERUP		0x0001

/*
 * SGTL5000_CHIP_PLL_CTRL
 */
#define SGTL5000_PLL_INT_DIV_MASK		0xf800
#define SGTL5000_PLL_INT_DIV_SHIFT		11
#define SGTL5000_PLL_INT_DIV_WIDTH		5
#define SGTL5000_PLL_FRAC_DIV_MASK		0x07ff
#define SGTL5000_PLL_FRAC_DIV_SHIFT		0
#define SGTL5000_PLL_FRAC_DIV_WIDTH		11

/*
 * SGTL5000_CHIP_CLK_TOP_CTRL
 */
#define SGTL5000_INT_OSC_EN			0x0800
#define SGTL5000_INPUT_FREQ_DIV2		0x0008

/*
 * SGTL5000_CHIP_ANA_STATUS
 */
#define SGTL5000_HP_LRSHORT			0x0200
#define SGTL5000_CAPLESS_SHORT			0x0100
#define SGTL5000_PLL_LOCKED			0x0010

/*
 * SGTL5000_CHIP_SHORT_CTRL
 */
#define SGTL5000_LVLADJR_MASK			0x7000
#define SGTL5000_LVLADJR_SHIFT			12
#define SGTL5000_LVLADJR_WIDTH			3
#define SGTL5000_LVLADJL_MASK			0x0700
#define SGTL5000_LVLADJL_SHIFT			8
#define SGTL5000_LVLADJL_WIDTH			3
#define SGTL5000_LVLADJC_MASK			0x0070
#define SGTL5000_LVLADJC_SHIFT			4
#define SGTL5000_LVLADJC_WIDTH			3
#define SGTL5000_LR_SHORT_MOD_MASK		0x000c
#define SGTL5000_LR_SHORT_MOD_SHIFT		2
#define SGTL5000_LR_SHORT_MOD_WIDTH		2
#define SGTL5000_CM_SHORT_MOD_MASK		0x0003
#define SGTL5000_CM_SHORT_MOD_SHIFT		0
#define SGTL5000_CM_SHORT_MOD_WIDTH		2

/*
 *SGTL5000_CHIP_ANA_TEST2
 */
#define SGTL5000_MONO_DAC			0x1000

/*
 * SGTL5000_DAP_CTRL
 */
#define SGTL5000_DAP_MIX_EN			0x0010
#define SGTL5000_DAP_EN				0x0001

#define SGTL5000_SYSCLK				0x00
#define SGTL5000_LRCLK				0x01

/*
 * SGTL5000_DAP_AUDIO_EQ
 */
#define SGTL5000_DAP_SEL_PEQ			1
#define SGTL5000_DAP_SEL_TONE_CTRL		2
#define SGTL5000_DAP_SEL_GEQ			3

#endif
