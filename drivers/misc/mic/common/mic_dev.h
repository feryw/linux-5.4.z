/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Intel MIC Platform Software Stack (MPSS)
 *
 * Copyright(c) 2013 Intel Corporation.
 *
 * Intel MIC driver.
 */
#ifndef __MIC_DEV_H__
#define __MIC_DEV_H__

/* The maximum number of MIC devices supported in a single host system. */
#define MIC_MAX_NUM_DEVS 128

/**
 * enum mic_hw_family - The hardware family to which a device belongs.
 */
enum mic_hw_family {
	MIC_FAMILY_X100 = 0,
	MIC_FAMILY_X200,
	MIC_FAMILY_UNKNOWN,
	MIC_FAMILY_LAST
};

/**
 * struct mic_mw - MIC memory window
 *
 * @pa: Base physical address.
 * @va: Base ioremap'd virtual address.
 * @len: Size of the memory window.
 */
struct mic_mw {
	phys_addr_t pa;
	void __iomem *va;
	resource_size_t len;
};

/*
 * Scratch pad register offsets used by the host to communicate
 * device page DMA address to the card.
 */
#define MIC_DPLO_SPAD 14
#define MIC_DPHI_SPAD 15

/*
 * These values are supposed to be in the config_change field of the
 * device page when the host sends a config change interrupt to the card.
 */
#define MIC_VIRTIO_PARAM_DEV_REMOVE 0x1
#define MIC_VIRTIO_PARAM_CONFIG_CHANGED 0x2

/* Maximum number of DMA channels */
#define MIC_MAX_DMA_CHAN 4

#endif
