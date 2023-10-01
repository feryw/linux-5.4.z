/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * ALSA SoC CS53L30 codec driver
 *
 * Copyright 2015 Cirrus Logic, Inc.
 *
 * Author: Paul Handrigan <Paul.Handrigan@cirrus.com>,
 *         Tim Howe <Tim.Howe@cirrus.com>
 */

#ifndef __CS53L30_H__
#define __CS53L30_H__

/* I2C Registers */
#define CS53L30_DEVID_AB	0x01	 /* Device ID A & B [RO]. */
#define CS53L30_DEVID_CD	0x02     /* Device ID C & D [RO]. */
#define CS53L30_DEVID_E		0x03     /* Device ID E [RO]. */
#define CS53L30_REVID		0x05     /* Revision ID [RO]. */
#define CS53L30_PWRCTL		0x06     /* Power Control. */
#define CS53L30_MCLKCTL		0x07     /* MCLK Control. */
#define CS53L30_INT_SR_CTL	0x08     /* Internal Sample Rate Control. */
#define CS53L30_MICBIAS_CTL	0x0A     /* Mic Bias Control. */
#define CS53L30_ASPCFG_CTL	0x0C     /* ASP Config Control. */
#define CS53L30_ASP_CTL1	0x0D     /* ASP1 Control. */
#define CS53L30_ASP_TDMTX_CTL1	0x0E     /* ASP1 TDM TX Control 1 */
#define CS53L30_ASP_TDMTX_CTL2	0x0F     /* ASP1 TDM TX Control 2 */
#define CS53L30_ASP_TDMTX_CTL3	0x10     /* ASP1 TDM TX Control 3 */
#define CS53L30_ASP_TDMTX_CTL4	0x11     /* ASP1 TDM TX Control 4 */
#define CS53L30_ASP_TDMTX_EN1	0x12     /* ASP1 TDM TX Enable 1 */
#define CS53L30_ASP_TDMTX_EN2	0x13     /* ASP1 TDM TX Enable 2 */
#define CS53L30_ASP_TDMTX_EN3	0x14     /* ASP1 TDM TX Enable 3 */
#define CS53L30_ASP_TDMTX_EN4	0x15     /* ASP1 TDM TX Enable 4 */
#define CS53L30_ASP_TDMTX_EN5	0x16     /* ASP1 TDM TX Enable 5 */
#define CS53L30_ASP_TDMTX_EN6	0x17     /* ASP1 TDM TX Enable 6 */
#define CS53L30_ASP_CTL2	0x18     /* ASP2 Control. */
#define CS53L30_SFT_RAMP	0x1A     /* Soft Ramp Control. */
#define CS53L30_LRCK_CTL1	0x1B     /* LRCK Control 1. */
#define CS53L30_LRCK_CTL2	0x1C     /* LRCK Control 2. */
#define CS53L30_MUTEP_CTL1	0x1F     /* Mute Pin Control 1. */
#define CS53L30_MUTEP_CTL2	0x20     /* Mute Pin Control 2. */
#define CS53L30_INBIAS_CTL1	0x21     /* Input Bias Control 1. */
#define CS53L30_INBIAS_CTL2	0x22     /* Input Bias Control 2. */
#define CS53L30_DMIC1_STR_CTL   0x23     /* DMIC1 Stereo Control. */
#define CS53L30_DMIC2_STR_CTL   0x24     /* DMIC2 Stereo Control. */
#define CS53L30_ADCDMIC1_CTL1   0x25     /* ADC1/DMIC1 Control 1. */
#define CS53L30_ADCDMIC1_CTL2   0x26     /* ADC1/DMIC1 Control 2. */
#define CS53L30_ADC1_CTL3	0x27     /* ADC1 Control 3. */
#define CS53L30_ADC1_NG_CTL	0x28     /* ADC1 Noise Gate Control. */
#define CS53L30_ADC1A_AFE_CTL	0x29     /* ADC1A AFE Control. */
#define CS53L30_ADC1B_AFE_CTL	0x2A     /* ADC1B AFE Control. */
#define CS53L30_ADC1A_DIG_VOL	0x2B     /* ADC1A Digital Volume. */
#define CS53L30_ADC1B_DIG_VOL	0x2C     /* ADC1B Digital Volume. */
#define CS53L30_ADCDMIC2_CTL1   0x2D     /* ADC2/DMIC2 Control 1. */
#define CS53L30_ADCDMIC2_CTL2   0x2E     /* ADC2/DMIC2 Control 2. */
#define CS53L30_ADC2_CTL3	0x2F     /* ADC2 Control 3. */
#define CS53L30_ADC2_NG_CTL	0x30     /* ADC2 Noise Gate Control. */
#define CS53L30_ADC2A_AFE_CTL	0x31     /* ADC2A AFE Control. */
#define CS53L30_ADC2B_AFE_CTL	0x32     /* ADC2B AFE Control. */
#define CS53L30_ADC2A_DIG_VOL	0x33     /* ADC2A Digital Volume. */
#define CS53L30_ADC2B_DIG_VOL	0x34     /* ADC2B Digital Volume. */
#define CS53L30_INT_MASK	0x35     /* Interrupt Mask. */
#define CS53L30_IS		0x36     /* Interrupt Status. */
#define CS53L30_MAX_REGISTER	0x36

#define CS53L30_TDM_SLOT_MAX		4
#define CS53L30_ASP_TDMTX_CTL(x)	(CS53L30_ASP_TDMTX_CTL1 + (x))
/* x : index for registers; n : index for slot; 8 slots per register */
#define CS53L30_ASP_TDMTX_ENx(x)	(CS53L30_ASP_TDMTX_EN6 - (x))
#define CS53L30_ASP_TDMTX_ENn(n)	CS53L30_ASP_TDMTX_ENx((n) >> 3)
#define CS53L30_ASP_TDMTX_ENx_MAX	6

/* Device ID */
#define CS53L30_DEVID		0x53A30

/* PDN_DONE Poll Maximum
 * If soft ramp is set it will take much longer to power down
 * the system.
 */
#define CS53L30_PDN_POLL_MAX	90

/* Bitfield Definitions */

/* R6 (0x06) CS53L30_PWRCTL - Power Control */
#define CS53L30_PDN_ULP_SHIFT		7
#define CS53L30_PDN_ULP_MASK		(1 << CS53L30_PDN_ULP_SHIFT)
#define CS53L30_PDN_ULP			(1 << CS53L30_PDN_ULP_SHIFT)
#define CS53L30_PDN_LP_SHIFT		6
#define CS53L30_PDN_LP_MASK		(1 << CS53L30_PDN_LP_SHIFT)
#define CS53L30_PDN_LP			(1 << CS53L30_PDN_LP_SHIFT)
#define CS53L30_DISCHARGE_FILT_SHIFT	5
#define CS53L30_DISCHARGE_FILT_MASK	(1 << CS53L30_DISCHARGE_FILT_SHIFT)
#define CS53L30_DISCHARGE_FILT		(1 << CS53L30_DISCHARGE_FILT_SHIFT)
#define CS53L30_THMS_PDN_SHIFT		4
#define CS53L30_THMS_PDN_MASK		(1 << CS53L30_THMS_PDN_SHIFT)
#define CS53L30_THMS_PDN		(1 << CS53L30_THMS_PDN_SHIFT)

#define CS53L30_PWRCTL_DEFAULT		(CS53L30_THMS_PDN)

/* R7 (0x07) CS53L30_MCLKCTL - MCLK Control */
#define CS53L30_MCLK_DIS_SHIFT		7
#define CS53L30_MCLK_DIS_MASK		(1 << CS53L30_MCLK_DIS_SHIFT)
#define CS53L30_MCLK_DIS		(1 << CS53L30_MCLK_DIS_SHIFT)
#define CS53L30_MCLK_INT_SCALE_SHIFT	6
#define CS53L30_MCLK_INT_SCALE_MASK	(1 << CS53L30_MCLK_INT_SCALE_SHIFT)
#define CS53L30_MCLK_INT_SCALE		(1 << CS53L30_MCLK_INT_SCALE_SHIFT)
#define CS53L30_DMIC_DRIVE_SHIFT	5
#define CS53L30_DMIC_DRIVE_MASK		(1 << CS53L30_DMIC_DRIVE_SHIFT)
#define CS53L30_DMIC_DRIVE		(1 << CS53L30_DMIC_DRIVE_SHIFT)
#define CS53L30_MCLK_DIV_SHIFT		2
#define CS53L30_MCLK_DIV_WIDTH		2
#define CS53L30_MCLK_DIV_MASK		(((1 << CS53L30_MCLK_DIV_WIDTH) - 1) << CS53L30_MCLK_DIV_SHIFT)
#define CS53L30_MCLK_DIV_BY_1		(0x0 << CS53L30_MCLK_DIV_SHIFT)
#define CS53L30_MCLK_DIV_BY_2		(0x1 << CS53L30_MCLK_DIV_SHIFT)
#define CS53L30_MCLK_DIV_BY_3		(0x2 << CS53L30_MCLK_DIV_SHIFT)
#define CS53L30_SYNC_EN_SHIFT		1
#define CS53L30_SYNC_EN_MASK		(1 << CS53L30_SYNC_EN_SHIFT)
#define CS53L30_SYNC_EN			(1 << CS53L30_SYNC_EN_SHIFT)

#define CS53L30_MCLKCTL_DEFAULT		(CS53L30_MCLK_DIV_BY_2)

/* R8 (0x08) CS53L30_INT_SR_CTL - Internal Sample Rate Control */
#define CS53L30_INTRNL_FS_RATIO_SHIFT	4
#define CS53L30_INTRNL_FS_RATIO_MASK	(1 << CS53L30_INTRNL_FS_RATIO_SHIFT)
#define CS53L30_INTRNL_FS_RATIO		(1 << CS53L30_INTRNL_FS_RATIO_SHIFT)
#define CS53L30_MCLK_19MHZ_EN_SHIFT	0
#define CS53L30_MCLK_19MHZ_EN_MASK	(1 << CS53L30_MCLK_19MHZ_EN_SHIFT)
#define CS53L30_MCLK_19MHZ_EN		(1 << CS53L30_MCLK_19MHZ_EN_SHIFT)

/* 0x6 << 1 is reserved bits */
#define CS53L30_INT_SR_CTL_DEFAULT	(CS53L30_INTRNL_FS_RATIO | 0x6 << 1)

/* R10 (0x0A) CS53L30_MICBIAS_CTL - Mic Bias Control */
#define CS53L30_MIC4_BIAS_PDN_SHIFT	7
#define CS53L30_MIC4_BIAS_PDN_MASK	(1 << CS53L30_MIC4_BIAS_PDN_SHIFT)
#define CS53L30_MIC4_BIAS_PDN		(1 << CS53L30_MIC4_BIAS_PDN_SHIFT)
#define CS53L30_MIC3_BIAS_PDN_SHIFT	6
#define CS53L30_MIC3_BIAS_PDN_MASK	(1 << CS53L30_MIC3_BIAS_PDN_SHIFT)
#define CS53L30_MIC3_BIAS_PDN		(1 << CS53L30_MIC3_BIAS_PDN_SHIFT)
#define CS53L30_MIC2_BIAS_PDN_SHIFT	5
#define CS53L30_MIC2_BIAS_PDN_MASK	(1 << CS53L30_MIC2_BIAS_PDN_SHIFT)
#define CS53L30_MIC2_BIAS_PDN		(1 << CS53L30_MIC2_BIAS_PDN_SHIFT)
#define CS53L30_MIC1_BIAS_PDN_SHIFT	4
#define CS53L30_MIC1_BIAS_PDN_MASK	(1 << CS53L30_MIC1_BIAS_PDN_SHIFT)
#define CS53L30_MIC1_BIAS_PDN		(1 << CS53L30_MIC1_BIAS_PDN_SHIFT)
#define CS53L30_MICx_BIAS_PDN		(0xf << CS53L30_MIC1_BIAS_PDN_SHIFT)
#define CS53L30_VP_MIN_SHIFT		2
#define CS53L30_VP_MIN_MASK		(1 << CS53L30_VP_MIN_SHIFT)
#define CS53L30_VP_MIN			(1 << CS53L30_VP_MIN_SHIFT)
#define CS53L30_MIC_BIAS_CTRL_SHIFT	0
#define CS53L30_MIC_BIAS_CTRL_WIDTH	2
#define CS53L30_MIC_BIAS_CTRL_MASK	(((1 << CS53L30_MIC_BIAS_CTRL_WIDTH) - 1) << CS53L30_MIC_BIAS_CTRL_SHIFT)
#define CS53L30_MIC_BIAS_CTRL_HIZ	(0 << CS53L30_MIC_BIAS_CTRL_SHIFT)
#define CS53L30_MIC_BIAS_CTRL_1V8	(1 << CS53L30_MIC_BIAS_CTRL_SHIFT)
#define CS53L30_MIC_BIAS_CTRL_2V75	(2 << CS53L30_MIC_BIAS_CTRL_SHIFT)

#define CS53L30_MICBIAS_CTL_DEFAULT	(CS53L30_MICx_BIAS_PDN | CS53L30_VP_MIN)

/* R12 (0x0C) CS53L30_ASPCFG_CTL - ASP Configuration Control */
#define CS53L30_ASP_MS_SHIFT		7
#define CS53L30_ASP_MS_MASK		(1 << CS53L30_ASP_MS_SHIFT)
#define CS53L30_ASP_MS			(1 << CS53L30_ASP_MS_SHIFT)
#define CS53L30_ASP_SCLK_INV_SHIFT	4
#define CS53L30_ASP_SCLK_INV_MASK	(1 << CS53L30_ASP_SCLK_INV_SHIFT)
#define CS53L30_ASP_SCLK_INV		(1 << CS53L30_ASP_SCLK_INV_SHIFT)
#define CS53L30_ASP_RATE_SHIFT		0
#define CS53L30_ASP_RATE_WIDTH		4
#define CS53L30_ASP_RATE_MASK		(((1 << CS53L30_ASP_RATE_WIDTH) - 1) << CS53L30_ASP_RATE_SHIFT)
#define CS53L30_ASP_RATE_48K		(0xc << CS53L30_ASP_RATE_SHIFT)

#define CS53L30_ASPCFG_CTL_DEFAULT	(CS53L30_ASP_RATE_48K)

/* R13/R24 (0x0D/0x18) CS53L30_ASP_CTL1 & CS53L30_ASP_CTL2 - ASP Control 1~2 */
#define CS53L30_ASP_TDM_PDN_SHIFT	7
#define CS53L30_ASP_TDM_PDN_MASK	(1 << CS53L30_ASP_TDM_PDN_SHIFT)
#define CS53L30_ASP_TDM_PDN		(1 << CS53L30_ASP_TDM_PDN_SHIFT)
#define CS53L30_ASP_SDOUTx_PDN_SHIFT	6
#define CS53L30_ASP_SDOUTx_PDN_MASK	(1 << CS53L30_ASP_SDOUTx_PDN_SHIFT)
#define CS53L30_ASP_SDOUTx_PDN		(1 << CS53L30_ASP_SDOUTx_PDN_SHIFT)
#define CS53L30_ASP_3ST_SHIFT		5
#define CS53L30_ASP_3ST_MASK		(1 << CS53L30_ASP_3ST_SHIFT)
#define CS53L30_ASP_3ST			(1 << CS53L30_ASP_3ST_SHIFT)
#define CS53L30_SHIFT_LEFT_SHIFT	4
#define CS53L30_SHIFT_LEFT_MASK		(1 << CS53L30_SHIFT_LEFT_SHIFT)
#define CS53L30_SHIFT_LEFT		(1 << CS53L30_SHIFT_LEFT_SHIFT)
#define CS53L30_ASP_SDOUTx_DRIVE_SHIFT	0
#define CS53L30_ASP_SDOUTx_DRIVE_MASK	(1 << CS53L30_ASP_SDOUTx_DRIVE_SHIFT)
#define CS53L30_ASP_SDOUTx_DRIVE	(1 << CS53L30_ASP_SDOUTx_DRIVE_SHIFT)

#define CS53L30_ASP_CTL1_DEFAULT	(CS53L30_ASP_TDM_PDN)
#define CS53L30_ASP_CTL2_DEFAULT	(0)

/* R14 (0x0E) ~ R17 (0x11) CS53L30_ASP_TDMTX_CTLx - ASP TDM TX Control 1~4 */
#define CS53L30_ASP_CHx_TX_STATE_SHIFT	7
#define CS53L30_ASP_CHx_TX_STATE_MASK	(1 << CS53L30_ASP_CHx_TX_STATE_SHIFT)
#define CS53L30_ASP_CHx_TX_STATE	(1 << CS53L30_ASP_CHx_TX_STATE_SHIFT)
#define CS53L30_ASP_CHx_TX_LOC_SHIFT	0
#define CS53L30_ASP_CHx_TX_LOC_WIDTH	6
#define CS53L30_ASP_CHx_TX_LOC_MASK	(((1 << CS53L30_ASP_CHx_TX_LOC_WIDTH) - 1) << CS53L30_ASP_CHx_TX_LOC_SHIFT)
#define CS53L30_ASP_CHx_TX_LOC_MAX	(47 << CS53L30_ASP_CHx_TX_LOC_SHIFT)
#define CS53L30_ASP_CHx_TX_LOC(x)	((x) << CS53L30_ASP_CHx_TX_LOC_SHIFT)

#define CS53L30_ASP_TDMTX_CTLx_DEFAULT	(CS53L30_ASP_CHx_TX_LOC_MAX)

/* R18 (0x12) ~ R23 (0x17) CS53L30_ASP_TDMTX_ENx - ASP TDM TX Enable 1~6 */
#define CS53L30_ASP_TDMTX_ENx_DEFAULT	(0)

/* R26 (0x1A) CS53L30_SFT_RAMP - Soft Ramp Control */
#define CS53L30_DIGSFT_SHIFT		5
#define CS53L30_DIGSFT_MASK		(1 << CS53L30_DIGSFT_SHIFT)
#define CS53L30_DIGSFT			(1 << CS53L30_DIGSFT_SHIFT)

#define CS53L30_SFT_RMP_DEFAULT		(0)

/* R28 (0x1C) CS53L30_LRCK_CTL2 - LRCK Control 2 */
#define CS53L30_LRCK_50_NPW_SHIFT	3
#define CS53L30_LRCK_50_NPW_MASK	(1 << CS53L30_LRCK_50_NPW_SHIFT)
#define CS53L30_LRCK_50_NPW		(1 << CS53L30_LRCK_50_NPW_SHIFT)
#define CS53L30_LRCK_TPWH_SHIFT		0
#define CS53L30_LRCK_TPWH_WIDTH		3
#define CS53L30_LRCK_TPWH_MASK		(((1 << CS53L30_LRCK_TPWH_WIDTH) - 1) << CS53L30_LRCK_TPWH_SHIFT)
#define CS53L30_LRCK_TPWH(x)		(((x) << CS53L30_LRCK_TPWH_SHIFT) & CS53L30_LRCK_TPWH_MASK)

#define CS53L30_LRCK_CTLx_DEFAULT	(0)

/* R31 (0x1F) CS53L30_MUTEP_CTL1 - MUTE Pin Control 1 */
#define CS53L30_MUTE_PDN_ULP_SHIFT	7
#define CS53L30_MUTE_PDN_ULP_MASK	(1 << CS53L30_MUTE_PDN_ULP_SHIFT)
#define CS53L30_MUTE_PDN_ULP		(1 << CS53L30_MUTE_PDN_ULP_SHIFT)
#define CS53L30_MUTE_PDN_LP_SHIFT	6
#define CS53L30_MUTE_PDN_LP_MASK	(1 << CS53L30_MUTE_PDN_LP_SHIFT)
#define CS53L30_MUTE_PDN_LP		(1 << CS53L30_MUTE_PDN_LP_SHIFT)
#define CS53L30_MUTE_M4B_PDN_SHIFT	4
#define CS53L30_MUTE_M4B_PDN_MASK	(1 << CS53L30_MUTE_M4B_PDN_SHIFT)
#define CS53L30_MUTE_M4B_PDN		(1 << CS53L30_MUTE_M4B_PDN_SHIFT)
#define CS53L30_MUTE_M3B_PDN_SHIFT	3
#define CS53L30_MUTE_M3B_PDN_MASK	(1 << CS53L30_MUTE_M3B_PDN_SHIFT)
#define CS53L30_MUTE_M3B_PDN		(1 << CS53L30_MUTE_M3B_PDN_SHIFT)
#define CS53L30_MUTE_M2B_PDN_SHIFT	2
#define CS53L30_MUTE_M2B_PDN_MASK	(1 << CS53L30_MUTE_M2B_PDN_SHIFT)
#define CS53L30_MUTE_M2B_PDN		(1 << CS53L30_MUTE_M2B_PDN_SHIFT)
#define CS53L30_MUTE_M1B_PDN_SHIFT	1
#define CS53L30_MUTE_M1B_PDN_MASK	(1 << CS53L30_MUTE_M1B_PDN_SHIFT)
#define CS53L30_MUTE_M1B_PDN		(1 << CS53L30_MUTE_M1B_PDN_SHIFT)
/* Note: be careful - x starts from 0 */
#define CS53L30_MUTE_MxB_PDN_SHIFT(x)	(CS53L30_MUTE_M1B_PDN_SHIFT + (x))
#define CS53L30_MUTE_MxB_PDN_MASK(x)	(1 << CS53L30_MUTE_MxB_PDN_SHIFT(x))
#define CS53L30_MUTE_MxB_PDN(x)		(1 << CS53L30_MUTE_MxB_PDN_SHIFT(x))
#define CS53L30_MUTE_MB_ALL_PDN_SHIFT	0
#define CS53L30_MUTE_MB_ALL_PDN_MASK	(1 << CS53L30_MUTE_MB_ALL_PDN_SHIFT)
#define CS53L30_MUTE_MB_ALL_PDN		(1 << CS53L30_MUTE_MB_ALL_PDN_SHIFT)

#define CS53L30_MUTEP_CTL1_MUTEALL	(0xdf)
#define CS53L30_MUTEP_CTL1_DEFAULT	(0)

/* R32 (0x20) CS53L30_MUTEP_CTL2 - MUTE Pin Control 2 */
#define CS53L30_MUTE_PIN_POLARITY_SHIFT	7
#define CS53L30_MUTE_PIN_POLARITY_MASK	(1 << CS53L30_MUTE_PIN_POLARITY_SHIFT)
#define CS53L30_MUTE_PIN_POLARITY	(1 << CS53L30_MUTE_PIN_POLARITY_SHIFT)
#define CS53L30_MUTE_ASP_TDM_PDN_SHIFT	6
#define CS53L30_MUTE_ASP_TDM_PDN_MASK	(1 << CS53L30_MUTE_ASP_TDM_PDN_SHIFT)
#define CS53L30_MUTE_ASP_TDM_PDN	(1 << CS53L30_MUTE_ASP_TDM_PDN_SHIFT)
#define CS53L30_MUTE_ASP_SDOUT2_PDN_SHIFT 5
#define CS53L30_MUTE_ASP_SDOUT2_PDN_MASK (1 << CS53L30_MUTE_ASP_SDOUT2_PDN_SHIFT)
#define CS53L30_MUTE_ASP_SDOUT2_PDN	(1 << CS53L30_MUTE_ASP_SDOUT2_PDN_SHIFT)
#define CS53L30_MUTE_ASP_SDOUT1_PDN_SHIFT 4
#define CS53L30_MUTE_ASP_SDOUT1_PDN_MASK (1 << CS53L30_MUTE_ASP_SDOUT1_PDN_SHIFT)
#define CS53L30_MUTE_ASP_SDOUT1_PDN	(1 << CS53L30_MUTE_ASP_SDOUT1_PDN_SHIFT)
/* Note: be careful - x starts from 0 */
#define CS53L30_MUTE_ASP_SDOUTx_PDN_SHIFT(x) ((x) + CS53L30_MUTE_ASP_SDOUT1_PDN_SHIFT)
#define CS53L30_MUTE_ASP_SDOUTx_PDN_MASK(x) (1 << CS53L30_MUTE_ASP_SDOUTx_PDN_SHIFT(x))
#define CS53L30_MUTE_ASP_SDOUTx_PDN	(1 << CS53L30_MUTE_ASP_SDOUTx_PDN_SHIFT(x))
#define CS53L30_MUTE_ADC2B_PDN_SHIFT	3
#define CS53L30_MUTE_ADC2B_PDN_MASK	(1 << CS53L30_MUTE_ADC2B_PDN_SHIFT)
#define CS53L30_MUTE_ADC2B_PDN		(1 << CS53L30_MUTE_ADC2B_PDN_SHIFT)
#define CS53L30_MUTE_ADC2A_PDN_SHIFT	2
#define CS53L30_MUTE_ADC2A_PDN_MASK	(1 << CS53L30_MUTE_ADC2A_PDN_SHIFT)
#define CS53L30_MUTE_ADC2A_PDN		(1 << CS53L30_MUTE_ADC2A_PDN_SHIFT)
#define CS53L30_MUTE_ADC1B_PDN_SHIFT	1
#define CS53L30_MUTE_ADC1B_PDN_MASK	(1 << CS53L30_MUTE_ADC1B_PDN_SHIFT)
#define CS53L30_MUTE_ADC1B_PDN		(1 << CS53L30_MUTE_ADC1B_PDN_SHIFT)
#define CS53L30_MUTE_ADC1A_PDN_SHIFT	0
#define CS53L30_MUTE_ADC1A_PDN_MASK	(1 << CS53L30_MUTE_ADC1A_PDN_SHIFT)
#define CS53L30_MUTE_ADC1A_PDN		(1 << CS53L30_MUTE_ADC1A_PDN_SHIFT)

#define CS53L30_MUTEP_CTL2_DEFAULT	(CS53L30_MUTE_PIN_POLARITY)

/* R33 (0x21) CS53L30_INBIAS_CTL1 - Input Bias Control 1 */
#define CS53L30_IN4M_BIAS_SHIFT		6
#define CS53L30_IN4M_BIAS_WIDTH		2
#define CS53L30_IN4M_BIAS_MASK		(((1 << CS53L30_IN4M_BIAS_WIDTH) - 1) << CS53L30_IN4M_BIAS_SHIFT)
#define CS53L30_IN4M_BIAS_OPEN		(0 << CS53L30_IN4M_BIAS_SHIFT)
#define CS53L30_IN4M_BIAS_PULL_DOWN	(1 << CS53L30_IN4M_BIAS_SHIFT)
#define CS53L30_IN4M_BIAS_VCM		(2 << CS53L30_IN4M_BIAS_SHIFT)
#define CS53L30_IN4P_BIAS_SHIFT		4
#define CS53L30_IN4P_BIAS_WIDTH		2
#define CS53L30_IN4P_BIAS_MASK		(((1 << CS53L30_IN4P_BIAS_WIDTH) - 1) << CS53L30_IN4P_BIAS_SHIFT)
#define CS53L30_IN4P_BIAS_OPEN		(0 << CS53L30_IN4P_BIAS_SHIFT)
#define CS53L30_IN4P_BIAS_PULL_DOWN	(1 << CS53L30_IN4P_BIAS_SHIFT)
#define CS53L30_IN4P_BIAS_VCM		(2 << CS53L30_IN4P_BIAS_SHIFT)
#define CS53L30_IN3M_BIAS_SHIFT		2
#define CS53L30_IN3M_BIAS_WIDTH		2
#define CS53L30_IN3M_BIAS_MASK		(((1 << CS53L30_IN3M_BIAS_WIDTH) - 1) << CS53L30_IN4M_BIAS_SHIFT)
#define CS53L30_IN3M_BIAS_OPEN		(0 << CS53L30_IN3M_BIAS_SHIFT)
#define CS53L30_IN3M_BIAS_PULL_DOWN	(1 << CS53L30_IN3M_BIAS_SHIFT)
#define CS53L30_IN3M_BIAS_VCM		(2 << CS53L30_IN3M_BIAS_SHIFT)
#define CS53L30_IN3P_BIAS_SHIFT		0
#define CS53L30_IN3P_BIAS_WIDTH		2
#define CS53L30_IN3P_BIAS_MASK		(((1 << CS53L30_IN3P_BIAS_WIDTH) - 1) << CS53L30_IN3P_BIAS_SHIFT)
#define CS53L30_IN3P_BIAS_OPEN		(0 << CS53L30_IN3P_BIAS_SHIFT)
#define CS53L30_IN3P_BIAS_PULL_DOWN	(1 << CS53L30_IN3P_BIAS_SHIFT)
#define CS53L30_IN3P_BIAS_VCM		(2 << CS53L30_IN3P_BIAS_SHIFT)

#define CS53L30_INBIAS_CTL1_DEFAULT	(CS53L30_IN4M_BIAS_VCM | CS53L30_IN4P_BIAS_VCM |\
					 CS53L30_IN3M_BIAS_VCM | CS53L30_IN3P_BIAS_VCM)

/* R34 (0x22) CS53L30_INBIAS_CTL2 - Input Bias Control 2 */
#define CS53L30_IN2M_BIAS_SHIFT		6
#define CS53L30_IN2M_BIAS_WIDTH		2
#define CS53L30_IN2M_BIAS_MASK		(((1 << CS53L30_IN2M_BIAS_WIDTH) - 1) << CS53L30_IN2M_BIAS_SHIFT)
#define CS53L30_IN2M_BIAS_OPEN		(0 << CS53L30_IN2M_BIAS_SHIFT)
#define CS53L30_IN2M_BIAS_PULL_DOWN	(1 << CS53L30_IN2M_BIAS_SHIFT)
#define CS53L30_IN2M_BIAS_VCM		(2 << CS53L30_IN2M_BIAS_SHIFT)
#define CS53L30_IN2P_BIAS_SHIFT		4
#define CS53L30_IN2P_BIAS_WIDTH		2
#define CS53L30_IN2P_BIAS_MASK		(((1 << CS53L30_IN2P_BIAS_WIDTH) - 1) << CS53L30_IN2P_BIAS_SHIFT)
#define CS53L30_IN2P_BIAS_OPEN		(0 << CS53L30_IN2P_BIAS_SHIFT)
#define CS53L30_IN2P_BIAS_PULL_DOWN	(1 << CS53L30_IN2P_BIAS_SHIFT)
#define CS53L30_IN2P_BIAS_VCM		(2 << CS53L30_IN2P_BIAS_SHIFT)
#define CS53L30_IN1M_BIAS_SHIFT		2
#define CS53L30_IN1M_BIAS_WIDTH		2
#define CS53L30_IN1M_BIAS_MASK		(((1 << CS53L30_IN1M_BIAS_WIDTH) - 1) << CS53L30_IN1M_BIAS_SHIFT)
#define CS53L30_IN1M_BIAS_OPEN		(0 << CS53L30_IN1M_BIAS_SHIFT)
#define CS53L30_IN1M_BIAS_PULL_DOWN	(1 << CS53L30_IN1M_BIAS_SHIFT)
#define CS53L30_IN1M_BIAS_VCM		(2 << CS53L30_IN1M_BIAS_SHIFT)
#define CS53L30_IN1P_BIAS_SHIFT		0
#define CS53L30_IN1P_BIAS_WIDTH		2
#define CS53L30_IN1P_BIAS_MASK		(((1 << CS53L30_IN1P_BIAS_WIDTH) - 1) << CS53L30_IN1P_BIAS_SHIFT)
#define CS53L30_IN1P_BIAS_OPEN		(0 << CS53L30_IN1P_BIAS_SHIFT)
#define CS53L30_IN1P_BIAS_PULL_DOWN	(1 << CS53L30_IN1P_BIAS_SHIFT)
#define CS53L30_IN1P_BIAS_VCM		(2 << CS53L30_IN1P_BIAS_SHIFT)

#define CS53L30_INBIAS_CTL2_DEFAULT	(CS53L30_IN2M_BIAS_VCM | CS53L30_IN2P_BIAS_VCM |\
					 CS53L30_IN1M_BIAS_VCM | CS53L30_IN1P_BIAS_VCM)

/* R35 (0x23) & R36 (0x24) CS53L30_DMICx_STR_CTL - DMIC1 & DMIC2 Stereo Control */
#define CS53L30_DMICx_STEREO_ENB_SHIFT	5
#define CS53L30_DMICx_STEREO_ENB_MASK	(1 << CS53L30_DMICx_STEREO_ENB_SHIFT)
#define CS53L30_DMICx_STEREO_ENB	(1 << CS53L30_DMICx_STEREO_ENB_SHIFT)

/* 0x88 and 0xCC are reserved bits */
#define CS53L30_DMIC1_STR_CTL_DEFAULT	(CS53L30_DMICx_STEREO_ENB | 0x88)
#define CS53L30_DMIC2_STR_CTL_DEFAULT	(CS53L30_DMICx_STEREO_ENB | 0xCC)

/* R37/R45 (0x25/0x2D) CS53L30_ADCDMICx_CTL1 - ADC1/DMIC1 & ADC2/DMIC2 Control 1 */
#define CS53L30_ADCxB_PDN_SHIFT		7
#define CS53L30_ADCxB_PDN_MASK		(1 << CS53L30_ADCxB_PDN_SHIFT)
#define CS53L30_ADCxB_PDN		(1 << CS53L30_ADCxB_PDN_SHIFT)
#define CS53L30_ADCxA_PDN_SHIFT		6
#define CS53L30_ADCxA_PDN_MASK		(1 << CS53L30_ADCxA_PDN_SHIFT)
#define CS53L30_ADCxA_PDN		(1 << CS53L30_ADCxA_PDN_SHIFT)
#define CS53L30_DMICx_PDN_SHIFT		2
#define CS53L30_DMICx_PDN_MASK		(1 << CS53L30_DMICx_PDN_SHIFT)
#define CS53L30_DMICx_PDN		(1 << CS53L30_DMICx_PDN_SHIFT)
#define CS53L30_DMICx_SCLK_DIV_SHIFT	1
#define CS53L30_DMICx_SCLK_DIV_MASK	(1 << CS53L30_DMICx_SCLK_DIV_SHIFT)
#define CS53L30_DMICx_SCLK_DIV		(1 << CS53L30_DMICx_SCLK_DIV_SHIFT)
#define CS53L30_CH_TYPE_SHIFT		0
#define CS53L30_CH_TYPE_MASK		(1 << CS53L30_CH_TYPE_SHIFT)
#define CS53L30_CH_TYPE			(1 << CS53L30_CH_TYPE_SHIFT)

#define CS53L30_ADCDMICx_PDN_MASK	0xFF
#define CS53L30_ADCDMICx_CTL1_DEFAULT	(CS53L30_DMICx_PDN)

/* R38/R46 (0x26/0x2E) CS53L30_ADCDMICx_CTL2 - ADC1/DMIC1 & ADC2/DMIC2 Control 2 */
#define CS53L30_ADCx_NOTCH_DIS_SHIFT	7
#define CS53L30_ADCx_NOTCH_DIS_MASK	(1 << CS53L30_ADCx_NOTCH_DIS_SHIFT)
#define CS53L30_ADCx_NOTCH_DIS		(1 << CS53L30_ADCx_NOTCH_DIS_SHIFT)
#define CS53L30_ADCxB_INV_SHIFT		5
#define CS53L30_ADCxB_INV_MASK		(1 << CS53L30_ADCxB_INV_SHIFT)
#define CS53L30_ADCxB_INV		(1 << CS53L30_ADCxB_INV_SHIFT)
#define CS53L30_ADCxA_INV_SHIFT		4
#define CS53L30_ADCxA_INV_MASK		(1 << CS53L30_ADCxA_INV_SHIFT)
#define CS53L30_ADCxA_INV		(1 << CS53L30_ADCxA_INV_SHIFT)
#define CS53L30_ADCxB_DIG_BOOST_SHIFT	1
#define CS53L30_ADCxB_DIG_BOOST_MASK	(1 << CS53L30_ADCxB_DIG_BOOST_SHIFT)
#define CS53L30_ADCxB_DIG_BOOST		(1 << CS53L30_ADCxB_DIG_BOOST_SHIFT)
#define CS53L30_ADCxA_DIG_BOOST_SHIFT	0
#define CS53L30_ADCxA_DIG_BOOST_MASK	(1 << CS53L30_ADCxA_DIG_BOOST_SHIFT)
#define CS53L30_ADCxA_DIG_BOOST		(1 << CS53L30_ADCxA_DIG_BOOST_SHIFT)

#define CS53L30_ADCDMIC1_CTL2_DEFAULT	(0)

/* R39/R47 (0x27/0x2F) CS53L30_ADCx_CTL3 - ADC1/ADC2 Control 3 */
#define CS53L30_ADCx_HPF_EN_SHIFT	3
#define CS53L30_ADCx_HPF_EN_MASK	(1 << CS53L30_ADCx_HPF_EN_SHIFT)
#define CS53L30_ADCx_HPF_EN		(1 << CS53L30_ADCx_HPF_EN_SHIFT)
#define CS53L30_ADCx_HPF_CF_SHIFT	1
#define CS53L30_ADCx_HPF_CF_WIDTH	2
#define CS53L30_ADCx_HPF_CF_MASK	(((1 << CS53L30_ADCx_HPF_CF_WIDTH) - 1) << CS53L30_ADCx_HPF_CF_SHIFT)
#define CS53L30_ADCx_HPF_CF_1HZ86	(0 << CS53L30_ADCx_HPF_CF_SHIFT)
#define CS53L30_ADCx_HPF_CF_120HZ	(1 << CS53L30_ADCx_HPF_CF_SHIFT)
#define CS53L30_ADCx_HPF_CF_235HZ	(2 << CS53L30_ADCx_HPF_CF_SHIFT)
#define CS53L30_ADCx_HPF_CF_466HZ	(3 << CS53L30_ADCx_HPF_CF_SHIFT)
#define CS53L30_ADCx_NG_ALL_SHIFT	0
#define CS53L30_ADCx_NG_ALL_MASK	(1 << CS53L30_ADCx_NG_ALL_SHIFT)
#define CS53L30_ADCx_NG_ALL		(1 << CS53L30_ADCx_NG_ALL_SHIFT)

#define CS53L30_ADCx_CTL3_DEFAULT	(CS53L30_ADCx_HPF_EN)

/* R40/R48 (0x28/0x30) CS53L30_ADCx_NG_CTL - ADC1/ADC2 Noise Gate Control */
#define CS53L30_ADCxB_NG_SHIFT		7
#define CS53L30_ADCxB_NG_MASK		(1 << CS53L30_ADCxB_NG_SHIFT)
#define CS53L30_ADCxB_NG		(1 << CS53L30_ADCxB_NG_SHIFT)
#define CS53L30_ADCxA_NG_SHIFT		6
#define CS53L30_ADCxA_NG_MASK		(1 << CS53L30_ADCxA_NG_SHIFT)
#define CS53L30_ADCxA_NG		(1 << CS53L30_ADCxA_NG_SHIFT)
#define CS53L30_ADCx_NG_BOOST_SHIFT	5
#define CS53L30_ADCx_NG_BOOST_MASK	(1 << CS53L30_ADCx_NG_BOOST_SHIFT)
#define CS53L30_ADCx_NG_BOOST		(1 << CS53L30_ADCx_NG_BOOST_SHIFT)
#define CS53L30_ADCx_NG_THRESH_SHIFT	2
#define CS53L30_ADCx_NG_THRESH_WIDTH	3
#define CS53L30_ADCx_NG_THRESH_MASK	(((1 << CS53L30_ADCx_NG_THRESH_WIDTH) - 1) << CS53L30_ADCx_NG_THRESH_SHIFT)
#define CS53L30_ADCx_NG_DELAY_SHIFT	0
#define CS53L30_ADCx_NG_DELAY_WIDTH	2
#define CS53L30_ADCx_NG_DELAY_MASK	(((1 << CS53L30_ADCx_NG_DELAY_WIDTH) - 1) << CS53L30_ADCx_NG_DELAY_SHIFT)

#define CS53L30_ADCx_NG_CTL_DEFAULT	(0)

/* R41/R42/R49/R50 (0x29/0x2A/0x31/0x32) CS53L30_ADCxy_AFE_CTL - ADC1A/1B/2A/2B AFE Control */
#define CS53L30_ADCxy_PREAMP_SHIFT	6
#define CS53L30_ADCxy_PREAMP_WIDTH	2
#define CS53L30_ADCxy_PREAMP_MASK	(((1 << CS53L30_ADCxy_PREAMP_WIDTH) - 1) << CS53L30_ADCxy_PREAMP_SHIFT)
#define CS53L30_ADCxy_PGA_VOL_SHIFT	0
#define CS53L30_ADCxy_PGA_VOL_WIDTH	6
#define CS53L30_ADCxy_PGA_VOL_MASK	(((1 << CS53L30_ADCxy_PGA_VOL_WIDTH) - 1) << CS53L30_ADCxy_PGA_VOL_SHIFT)

#define CS53L30_ADCxy_AFE_CTL_DEFAULT	(0)

/* R43/R44/R51/R52 (0x2B/0x2C/0x33/0x34) CS53L30_ADCxy_DIG_VOL - ADC1A/1B/2A/2B Digital Volume */
#define CS53L30_ADCxy_VOL_MUTE		(0x80)

#define CS53L30_ADCxy_DIG_VOL_DEFAULT	(0x0)

/* CS53L30_INT */
#define CS53L30_PDN_DONE		(1 << 7)
#define CS53L30_THMS_TRIP		(1 << 6)
#define CS53L30_SYNC_DONE		(1 << 5)
#define CS53L30_ADC2B_OVFL		(1 << 4)
#define CS53L30_ADC2A_OVFL		(1 << 3)
#define CS53L30_ADC1B_OVFL		(1 << 2)
#define CS53L30_ADC1A_OVFL		(1 << 1)
#define CS53L30_MUTE_PIN		(1 << 0)
#define CS53L30_DEVICE_INT_MASK		0xFF

#endif	/* __CS53L30_H__ */
