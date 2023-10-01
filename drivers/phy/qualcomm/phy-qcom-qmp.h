// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2017, The Linux Foundation. All rights reserved.
 */

#ifndef QCOM_PHY_QMP_H_
#define QCOM_PHY_QMP_H_

/* Only for QMP V2 PHY - QSERDES COM registers */
#define QSERDES_COM_BG_TIMER				0x00c
#define QSERDES_COM_SSC_EN_CENTER			0x010
#define QSERDES_COM_SSC_ADJ_PER1			0x014
#define QSERDES_COM_SSC_ADJ_PER2			0x018
#define QSERDES_COM_SSC_PER1				0x01c
#define QSERDES_COM_SSC_PER2				0x020
#define QSERDES_COM_SSC_STEP_SIZE1			0x024
#define QSERDES_COM_SSC_STEP_SIZE2			0x028
#define QSERDES_COM_BIAS_EN_CLKBUFLR_EN			0x034
#define QSERDES_COM_CLK_ENABLE1				0x038
#define QSERDES_COM_SYS_CLK_CTRL			0x03c
#define QSERDES_COM_SYSCLK_BUF_ENABLE			0x040
#define QSERDES_COM_PLL_IVCO				0x048
#define QSERDES_COM_LOCK_CMP1_MODE0			0x04c
#define QSERDES_COM_LOCK_CMP2_MODE0			0x050
#define QSERDES_COM_LOCK_CMP3_MODE0			0x054
#define QSERDES_COM_LOCK_CMP1_MODE1			0x058
#define QSERDES_COM_LOCK_CMP2_MODE1			0x05c
#define QSERDES_COM_LOCK_CMP3_MODE1			0x060
#define QSERDES_COM_BG_TRIM				0x070
#define QSERDES_COM_CLK_EP_DIV				0x074
#define QSERDES_COM_CP_CTRL_MODE0			0x078
#define QSERDES_COM_CP_CTRL_MODE1			0x07c
#define QSERDES_COM_PLL_RCTRL_MODE0			0x084
#define QSERDES_COM_PLL_RCTRL_MODE1			0x088
#define QSERDES_COM_PLL_CCTRL_MODE0			0x090
#define QSERDES_COM_PLL_CCTRL_MODE1			0x094
#define QSERDES_COM_BIAS_EN_CTRL_BY_PSM			0x0a8
#define QSERDES_COM_SYSCLK_EN_SEL			0x0ac
#define QSERDES_COM_RESETSM_CNTRL			0x0b4
#define QSERDES_COM_RESTRIM_CTRL			0x0bc
#define QSERDES_COM_RESCODE_DIV_NUM			0x0c4
#define QSERDES_COM_LOCK_CMP_EN				0x0c8
#define QSERDES_COM_LOCK_CMP_CFG			0x0cc
#define QSERDES_COM_DEC_START_MODE0			0x0d0
#define QSERDES_COM_DEC_START_MODE1			0x0d4
#define QSERDES_COM_DIV_FRAC_START1_MODE0		0x0dc
#define QSERDES_COM_DIV_FRAC_START2_MODE0		0x0e0
#define QSERDES_COM_DIV_FRAC_START3_MODE0		0x0e4
#define QSERDES_COM_DIV_FRAC_START1_MODE1		0x0e8
#define QSERDES_COM_DIV_FRAC_START2_MODE1		0x0ec
#define QSERDES_COM_DIV_FRAC_START3_MODE1		0x0f0
#define QSERDES_COM_INTEGLOOP_GAIN0_MODE0		0x108
#define QSERDES_COM_INTEGLOOP_GAIN1_MODE0		0x10c
#define QSERDES_COM_INTEGLOOP_GAIN0_MODE1		0x110
#define QSERDES_COM_INTEGLOOP_GAIN1_MODE1		0x114
#define QSERDES_COM_VCO_TUNE_CTRL			0x124
#define QSERDES_COM_VCO_TUNE_MAP			0x128
#define QSERDES_COM_VCO_TUNE1_MODE0			0x12c
#define QSERDES_COM_VCO_TUNE2_MODE0			0x130
#define QSERDES_COM_VCO_TUNE1_MODE1			0x134
#define QSERDES_COM_VCO_TUNE2_MODE1			0x138
#define QSERDES_COM_VCO_TUNE_TIMER1			0x144
#define QSERDES_COM_VCO_TUNE_TIMER2			0x148
#define QSERDES_COM_BG_CTRL				0x170
#define QSERDES_COM_CLK_SELECT				0x174
#define QSERDES_COM_HSCLK_SEL				0x178
#define QSERDES_COM_CORECLK_DIV				0x184
#define QSERDES_COM_CORE_CLK_EN				0x18c
#define QSERDES_COM_C_READY_STATUS			0x190
#define QSERDES_COM_CMN_CONFIG				0x194
#define QSERDES_COM_SVS_MODE_CLK_SEL			0x19c
#define QSERDES_COM_DEBUG_BUS0				0x1a0
#define QSERDES_COM_DEBUG_BUS1				0x1a4
#define QSERDES_COM_DEBUG_BUS2				0x1a8
#define QSERDES_COM_DEBUG_BUS3				0x1ac
#define QSERDES_COM_DEBUG_BUS_SEL			0x1b0
#define QSERDES_COM_CORECLK_DIV_MODE1			0x1bc

/* Only for QMP V2 PHY - TX registers */
#define QSERDES_TX_RES_CODE_LANE_OFFSET			0x054
#define QSERDES_TX_DEBUG_BUS_SEL			0x064
#define QSERDES_TX_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN	0x068
#define QSERDES_TX_LANE_MODE				0x094
#define QSERDES_TX_RCV_DETECT_LVL_2			0x0ac

/* Only for QMP V2 PHY - RX registers */
#define QSERDES_RX_UCDR_SO_GAIN_HALF			0x010
#define QSERDES_RX_UCDR_SO_GAIN				0x01c
#define QSERDES_RX_UCDR_FASTLOCK_FO_GAIN		0x040
#define QSERDES_RX_UCDR_SO_SATURATION_AND_ENABLE	0x048
#define QSERDES_RX_RX_TERM_BW				0x090
#define QSERDES_RX_RX_EQ_GAIN1_LSB			0x0c4
#define QSERDES_RX_RX_EQ_GAIN1_MSB			0x0c8
#define QSERDES_RX_RX_EQ_GAIN2_LSB			0x0cc
#define QSERDES_RX_RX_EQ_GAIN2_MSB			0x0d0
#define QSERDES_RX_RX_EQU_ADAPTOR_CNTRL2		0x0d8
#define QSERDES_RX_RX_EQU_ADAPTOR_CNTRL3		0x0dc
#define QSERDES_RX_RX_EQU_ADAPTOR_CNTRL4		0x0e0
#define QSERDES_RX_RX_EQ_OFFSET_ADAPTOR_CNTRL1		0x108
#define QSERDES_RX_RX_OFFSET_ADAPTOR_CNTRL2		0x10c
#define QSERDES_RX_SIGDET_ENABLES			0x110
#define QSERDES_RX_SIGDET_CNTRL				0x114
#define QSERDES_RX_SIGDET_LVL				0x118
#define QSERDES_RX_SIGDET_DEGLITCH_CNTRL		0x11c
#define QSERDES_RX_RX_BAND				0x120
#define QSERDES_RX_RX_INTERFACE_MODE			0x12c

/* Only for QMP V2 PHY - PCS registers */
#define QPHY_POWER_DOWN_CONTROL				0x04
#define QPHY_TXDEEMPH_M6DB_V0				0x24
#define QPHY_TXDEEMPH_M3P5DB_V0				0x28
#define QPHY_ENDPOINT_REFCLK_DRIVE			0x54
#define QPHY_RX_IDLE_DTCT_CNTRL				0x58
#define QPHY_POWER_STATE_CONFIG1			0x60
#define QPHY_POWER_STATE_CONFIG2			0x64
#define QPHY_POWER_STATE_CONFIG4			0x6c
#define QPHY_LOCK_DETECT_CONFIG1			0x80
#define QPHY_LOCK_DETECT_CONFIG2			0x84
#define QPHY_LOCK_DETECT_CONFIG3			0x88
#define QPHY_PWRUP_RESET_DLY_TIME_AUXCLK		0xa0
#define QPHY_LP_WAKEUP_DLY_TIME_AUXCLK			0xa4
#define QPHY_PLL_LOCK_CHK_DLY_TIME_AUXCLK_LSB		0x1A8
#define QPHY_OSC_DTCT_ACTIONS				0x1AC
#define QPHY_RX_SIGDET_LVL				0x1D8
#define QPHY_L1SS_WAKEUP_DLY_TIME_AUXCLK_LSB		0x1DC
#define QPHY_L1SS_WAKEUP_DLY_TIME_AUXCLK_MSB		0x1E0

/* Only for QMP V3 PHY - DP COM registers */
#define QPHY_V3_DP_COM_PHY_MODE_CTRL			0x00
#define QPHY_V3_DP_COM_SW_RESET				0x04
#define QPHY_V3_DP_COM_POWER_DOWN_CTRL			0x08
#define QPHY_V3_DP_COM_SWI_CTRL				0x0c
#define QPHY_V3_DP_COM_TYPEC_CTRL			0x10
#define QPHY_V3_DP_COM_TYPEC_PWRDN_CTRL			0x14
#define QPHY_V3_DP_COM_RESET_OVRD_CTRL			0x1c

/* Only for QMP V3 PHY - QSERDES COM registers */
#define QSERDES_V3_COM_BG_TIMER				0x00c
#define QSERDES_V3_COM_SSC_EN_CENTER			0x010
#define QSERDES_V3_COM_SSC_ADJ_PER1			0x014
#define QSERDES_V3_COM_SSC_ADJ_PER2			0x018
#define QSERDES_V3_COM_SSC_PER1				0x01c
#define QSERDES_V3_COM_SSC_PER2				0x020
#define QSERDES_V3_COM_SSC_STEP_SIZE1			0x024
#define QSERDES_V3_COM_SSC_STEP_SIZE2			0x028
#define QSERDES_V3_COM_BIAS_EN_CLKBUFLR_EN		0x034
#define QSERDES_V3_COM_CLK_ENABLE1			0x038
#define QSERDES_V3_COM_SYS_CLK_CTRL			0x03c
#define QSERDES_V3_COM_SYSCLK_BUF_ENABLE		0x040
#define QSERDES_V3_COM_PLL_IVCO				0x048
#define QSERDES_V3_COM_LOCK_CMP1_MODE0			0x098
#define QSERDES_V3_COM_LOCK_CMP2_MODE0			0x09c
#define QSERDES_V3_COM_LOCK_CMP3_MODE0			0x0a0
#define QSERDES_V3_COM_LOCK_CMP1_MODE1			0x0a4
#define QSERDES_V3_COM_LOCK_CMP2_MODE1			0x0a8
#define QSERDES_V3_COM_LOCK_CMP3_MODE1			0x0ac
#define QSERDES_V3_COM_CLK_EP_DIV			0x05c
#define QSERDES_V3_COM_CP_CTRL_MODE0			0x060
#define QSERDES_V3_COM_CP_CTRL_MODE1			0x064
#define QSERDES_V3_COM_PLL_RCTRL_MODE0			0x068
#define QSERDES_V3_COM_PLL_RCTRL_MODE1			0x06c
#define QSERDES_V3_COM_PLL_CCTRL_MODE0			0x070
#define QSERDES_V3_COM_PLL_CCTRL_MODE1			0x074
#define QSERDES_V3_COM_SYSCLK_EN_SEL			0x080
#define QSERDES_V3_COM_RESETSM_CNTRL			0x088
#define QSERDES_V3_COM_RESETSM_CNTRL2			0x08c
#define QSERDES_V3_COM_LOCK_CMP_EN			0x090
#define QSERDES_V3_COM_LOCK_CMP_CFG			0x094
#define QSERDES_V3_COM_DEC_START_MODE0			0x0b0
#define QSERDES_V3_COM_DEC_START_MODE1			0x0b4
#define QSERDES_V3_COM_DIV_FRAC_START1_MODE0		0x0b8
#define QSERDES_V3_COM_DIV_FRAC_START2_MODE0		0x0bc
#define QSERDES_V3_COM_DIV_FRAC_START3_MODE0		0x0c0
#define QSERDES_V3_COM_DIV_FRAC_START1_MODE1		0x0c4
#define QSERDES_V3_COM_DIV_FRAC_START2_MODE1		0x0c8
#define QSERDES_V3_COM_DIV_FRAC_START3_MODE1		0x0cc
#define QSERDES_V3_COM_INTEGLOOP_INITVAL		0x0d0
#define QSERDES_V3_COM_INTEGLOOP_GAIN0_MODE0		0x0d8
#define QSERDES_V3_COM_INTEGLOOP_GAIN1_MODE0		0x0dc
#define QSERDES_V3_COM_INTEGLOOP_GAIN0_MODE1		0x0e0
#define QSERDES_V3_COM_INTEGLOOP_GAIN1_MODE1		0x0e4
#define QSERDES_V3_COM_VCO_TUNE_CTRL			0x0ec
#define QSERDES_V3_COM_VCO_TUNE_MAP			0x0f0
#define QSERDES_V3_COM_VCO_TUNE1_MODE0			0x0f4
#define QSERDES_V3_COM_VCO_TUNE2_MODE0			0x0f8
#define QSERDES_V3_COM_VCO_TUNE1_MODE1			0x0fc
#define QSERDES_V3_COM_VCO_TUNE2_MODE1			0x100
#define QSERDES_V3_COM_VCO_TUNE_INITVAL1		0x104
#define QSERDES_V3_COM_VCO_TUNE_INITVAL2		0x108
#define QSERDES_V3_COM_VCO_TUNE_TIMER1			0x11c
#define QSERDES_V3_COM_VCO_TUNE_TIMER2			0x120
#define QSERDES_V3_COM_CLK_SELECT			0x138
#define QSERDES_V3_COM_HSCLK_SEL			0x13c
#define QSERDES_V3_COM_CORECLK_DIV_MODE0		0x148
#define QSERDES_V3_COM_CORECLK_DIV_MODE1		0x14c
#define QSERDES_V3_COM_CORE_CLK_EN			0x154
#define QSERDES_V3_COM_C_READY_STATUS			0x158
#define QSERDES_V3_COM_CMN_CONFIG			0x15c
#define QSERDES_V3_COM_SVS_MODE_CLK_SEL			0x164
#define QSERDES_V3_COM_DEBUG_BUS0			0x168
#define QSERDES_V3_COM_DEBUG_BUS1			0x16c
#define QSERDES_V3_COM_DEBUG_BUS2			0x170
#define QSERDES_V3_COM_DEBUG_BUS3			0x174
#define QSERDES_V3_COM_DEBUG_BUS_SEL			0x178
#define QSERDES_V3_COM_CMN_MODE				0x184

/* Only for QMP V3 PHY - TX registers */
#define QSERDES_V3_TX_RES_CODE_LANE_OFFSET_TX		0x044
#define QSERDES_V3_TX_RES_CODE_LANE_OFFSET_RX		0x048
#define QSERDES_V3_TX_DEBUG_BUS_SEL			0x058
#define QSERDES_V3_TX_HIGHZ_DRVR_EN			0x060
#define QSERDES_V3_TX_LANE_MODE_1			0x08c
#define QSERDES_V3_TX_RCV_DETECT_LVL_2			0x0a4

/* Only for QMP V3 PHY - RX registers */
#define QSERDES_V3_RX_UCDR_FO_GAIN			0x008
#define QSERDES_V3_RX_UCDR_SO_GAIN_HALF			0x00c
#define QSERDES_V3_RX_UCDR_SO_GAIN			0x014
#define QSERDES_V3_RX_UCDR_SVS_SO_GAIN_HALF		0x024
#define QSERDES_V3_RX_UCDR_SVS_SO_GAIN_QUARTER		0x028
#define QSERDES_V3_RX_UCDR_SVS_SO_GAIN			0x02c
#define QSERDES_V3_RX_UCDR_FASTLOCK_FO_GAIN		0x030
#define QSERDES_V3_RX_UCDR_SO_SATURATION_AND_ENABLE	0x034
#define QSERDES_V3_RX_UCDR_FASTLOCK_COUNT_LOW		0x03c
#define QSERDES_V3_RX_UCDR_FASTLOCK_COUNT_HIGH		0x040
#define QSERDES_V3_RX_UCDR_PI_CONTROLS			0x044
#define QSERDES_V3_RX_RX_TERM_BW			0x07c
#define QSERDES_V3_RX_VGA_CAL_CNTRL1			0x0bc
#define QSERDES_V3_RX_VGA_CAL_CNTRL2			0x0c0
#define QSERDES_V3_RX_RX_EQ_GAIN2_LSB			0x0c8
#define QSERDES_V3_RX_RX_EQ_GAIN2_MSB			0x0cc
#define QSERDES_V3_RX_RX_EQU_ADAPTOR_CNTRL2		0x0d4
#define QSERDES_V3_RX_RX_EQU_ADAPTOR_CNTRL3		0x0d8
#define QSERDES_V3_RX_RX_EQU_ADAPTOR_CNTRL4		0x0dc
#define QSERDES_V3_RX_RX_EQ_OFFSET_ADAPTOR_CNTRL1	0x0f8
#define QSERDES_V3_RX_RX_OFFSET_ADAPTOR_CNTRL2		0x0fc
#define QSERDES_V3_RX_SIGDET_ENABLES			0x100
#define QSERDES_V3_RX_SIGDET_CNTRL			0x104
#define QSERDES_V3_RX_SIGDET_LVL			0x108
#define QSERDES_V3_RX_SIGDET_DEGLITCH_CNTRL		0x10c
#define QSERDES_V3_RX_RX_BAND				0x110
#define QSERDES_V3_RX_RX_INTERFACE_MODE			0x11c
#define QSERDES_V3_RX_RX_MODE_00			0x164
#define QSERDES_V3_RX_RX_MODE_01			0x168

/* Only for QMP V3 PHY - PCS registers */
#define QPHY_V3_PCS_POWER_DOWN_CONTROL			0x004
#define QPHY_V3_PCS_TXMGN_V0				0x00c
#define QPHY_V3_PCS_TXMGN_V1				0x010
#define QPHY_V3_PCS_TXMGN_V2				0x014
#define QPHY_V3_PCS_TXMGN_V3				0x018
#define QPHY_V3_PCS_TXMGN_V4				0x01c
#define QPHY_V3_PCS_TXMGN_LS				0x020
#define QPHY_V3_PCS_TX_LARGE_AMP_DRV_LVL		0x02c
#define QPHY_V3_PCS_TX_SMALL_AMP_DRV_LVL		0x034
#define QPHY_V3_PCS_TXDEEMPH_M6DB_V0			0x024
#define QPHY_V3_PCS_TXDEEMPH_M3P5DB_V0			0x028
#define QPHY_V3_PCS_TXDEEMPH_M6DB_V1			0x02c
#define QPHY_V3_PCS_TXDEEMPH_M3P5DB_V1			0x030
#define QPHY_V3_PCS_TXDEEMPH_M6DB_V2			0x034
#define QPHY_V3_PCS_TXDEEMPH_M3P5DB_V2			0x038
#define QPHY_V3_PCS_TXDEEMPH_M6DB_V3			0x03c
#define QPHY_V3_PCS_TXDEEMPH_M3P5DB_V3			0x040
#define QPHY_V3_PCS_TXDEEMPH_M6DB_V4			0x044
#define QPHY_V3_PCS_TXDEEMPH_M3P5DB_V4			0x048
#define QPHY_V3_PCS_TXDEEMPH_M6DB_LS			0x04c
#define QPHY_V3_PCS_TXDEEMPH_M3P5DB_LS			0x050
#define QPHY_V3_PCS_ENDPOINT_REFCLK_DRIVE		0x054
#define QPHY_V3_PCS_RX_IDLE_DTCT_CNTRL			0x058
#define QPHY_V3_PCS_RATE_SLEW_CNTRL			0x05c
#define QPHY_V3_PCS_POWER_STATE_CONFIG1			0x060
#define QPHY_V3_PCS_POWER_STATE_CONFIG2			0x064
#define QPHY_V3_PCS_POWER_STATE_CONFIG4			0x06c
#define QPHY_V3_PCS_RCVR_DTCT_DLY_P1U2_L		0x070
#define QPHY_V3_PCS_RCVR_DTCT_DLY_P1U2_H		0x074
#define QPHY_V3_PCS_RCVR_DTCT_DLY_U3_L			0x078
#define QPHY_V3_PCS_RCVR_DTCT_DLY_U3_H			0x07c
#define QPHY_V3_PCS_LOCK_DETECT_CONFIG1			0x080
#define QPHY_V3_PCS_LOCK_DETECT_CONFIG2			0x084
#define QPHY_V3_PCS_LOCK_DETECT_CONFIG3			0x088
#define QPHY_V3_PCS_TSYNC_RSYNC_TIME			0x08c
#define QPHY_V3_PCS_PWRUP_RESET_DLY_TIME_AUXCLK		0x0a0
#define QPHY_V3_PCS_LP_WAKEUP_DLY_TIME_AUXCLK		0x0a4
#define QPHY_V3_PCS_PLL_LOCK_CHK_DLY_TIME		0x0a8
#define QPHY_V3_PCS_LFPS_TX_ECSTART_EQTLOCK		0x0b0
#define QPHY_V3_PCS_RXEQTRAINING_WAIT_TIME		0x0b8
#define QPHY_V3_PCS_RXEQTRAINING_RUN_TIME		0x0bc
#define QPHY_V3_PCS_FLL_CNTRL1				0x0c4
#define QPHY_V3_PCS_FLL_CNTRL2				0x0c8
#define QPHY_V3_PCS_FLL_CNT_VAL_L			0x0cc
#define QPHY_V3_PCS_FLL_CNT_VAL_H_TOL			0x0d0
#define QPHY_V3_PCS_FLL_MAN_CODE			0x0d4
#define QPHY_V3_PCS_RX_SYM_RESYNC_CTRL			0x134
#define QPHY_V3_PCS_RX_MIN_HIBERN8_TIME			0x138
#define QPHY_V3_PCS_RX_SIGDET_CTRL1			0x13c
#define QPHY_V3_PCS_RX_SIGDET_CTRL2			0x140
#define QPHY_V3_PCS_LP_WAKEUP_DLY_TIME_AUXCLK_MSB	0x1a8
#define QPHY_V3_PCS_OSC_DTCT_ACTIONS			0x1ac
#define QPHY_V3_PCS_SIGDET_CNTRL			0x1b0
#define QPHY_V3_PCS_TX_MID_TERM_CTRL1			0x1bc
#define QPHY_V3_PCS_MULTI_LANE_CTRL1			0x1c4
#define QPHY_V3_PCS_RX_SIGDET_LVL			0x1d8
#define QPHY_V3_PCS_L1SS_WAKEUP_DLY_TIME_AUXCLK_LSB	0x1dc
#define QPHY_V3_PCS_L1SS_WAKEUP_DLY_TIME_AUXCLK_MSB	0x1e0
#define QPHY_V3_PCS_REFGEN_REQ_CONFIG1			0x20c
#define QPHY_V3_PCS_REFGEN_REQ_CONFIG2			0x210

/* Only for QMP V3 PHY - PCS_MISC registers */
#define QPHY_V3_PCS_MISC_CLAMP_ENABLE			0x0c
#define QPHY_V3_PCS_MISC_OSC_DTCT_CONFIG2		0x2c
#define QPHY_V3_PCS_MISC_PCIE_INT_AUX_CLK_CONFIG1	0x44
#define QPHY_V3_PCS_MISC_OSC_DTCT_MODE2_CONFIG2		0x54
#define QPHY_V3_PCS_MISC_OSC_DTCT_MODE2_CONFIG4		0x5c
#define QPHY_V3_PCS_MISC_OSC_DTCT_MODE2_CONFIG5		0x60

#endif
