/*
 * arch/xtensa/include/asm/xchal_vaddr_remap.h
 *
 * Xtensa macros for MMU V3 Support. Deals with re-mapping the Virtual
 * Memory Addresses from "Virtual == Physical" to their prevvious V2 MMU
 * mappings (KSEG at 0xD0000000 and KIO at 0XF0000000).
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008 - 2012 Tensilica Inc.
 *
 * Pete Delaney <piet@tensilica.com>
 * Marc Gauthier <marc@tensilica.com
 */

#ifndef _XTENSA_VECTORS_H
#define _XTENSA_VECTORS_H

#include <asm/core.h>
#include <asm/kmem_layout.h>

#if defined(CONFIG_MMU) && XCHAL_HAVE_PTP_MMU && XCHAL_HAVE_SPANNING_WAY
#define KERNELOFFSET			(CONFIG_KERNEL_LOAD_ADDRESS + \
					 XCHAL_KSEG_CACHED_VADDR - \
					 XCHAL_KSEG_PADDR)
#else
#define KERNELOFFSET			CONFIG_KERNEL_LOAD_ADDRESS
#endif

#define RESET_VECTOR1_VADDR		(XCHAL_RESET_VECTOR1_VADDR)
#ifdef CONFIG_VECTORS_OFFSET
#define VECBASE_VADDR			(KERNELOFFSET - CONFIG_VECTORS_OFFSET)
#else
#define VECBASE_VADDR			_vecbase
#endif

#if defined(XCHAL_HAVE_VECBASE) && XCHAL_HAVE_VECBASE

#define VECTOR_VADDR(offset)		(VECBASE_VADDR + offset)

#define USER_VECTOR_VADDR		VECTOR_VADDR(XCHAL_USER_VECOFS)
#define KERNEL_VECTOR_VADDR		VECTOR_VADDR(XCHAL_KERNEL_VECOFS)
#define DOUBLEEXC_VECTOR_VADDR		VECTOR_VADDR(XCHAL_DOUBLEEXC_VECOFS)
#define WINDOW_VECTORS_VADDR		VECTOR_VADDR(XCHAL_WINDOW_OF4_VECOFS)
#define INTLEVEL2_VECTOR_VADDR		VECTOR_VADDR(XCHAL_INTLEVEL2_VECOFS)
#define INTLEVEL3_VECTOR_VADDR		VECTOR_VADDR(XCHAL_INTLEVEL3_VECOFS)
#define INTLEVEL4_VECTOR_VADDR		VECTOR_VADDR(XCHAL_INTLEVEL4_VECOFS)
#define INTLEVEL5_VECTOR_VADDR		VECTOR_VADDR(XCHAL_INTLEVEL5_VECOFS)
#define INTLEVEL6_VECTOR_VADDR		VECTOR_VADDR(XCHAL_INTLEVEL6_VECOFS)
#define INTLEVEL7_VECTOR_VADDR		VECTOR_VADDR(XCHAL_INTLEVEL7_VECOFS)
#define DEBUG_VECTOR_VADDR		VECTOR_VADDR(XCHAL_DEBUG_VECOFS)

/*
 * These XCHAL_* #defines from varian/core.h
 * are not valid to use with V3 MMU. Non-XCHAL
 * constants are defined above and should be used.
 */
#undef  XCHAL_VECBASE_RESET_VADDR
#undef  XCHAL_USER_VECTOR_VADDR
#undef  XCHAL_KERNEL_VECTOR_VADDR
#undef  XCHAL_DOUBLEEXC_VECTOR_VADDR
#undef  XCHAL_WINDOW_VECTORS_VADDR
#undef  XCHAL_INTLEVEL2_VECTOR_VADDR
#undef  XCHAL_INTLEVEL3_VECTOR_VADDR
#undef  XCHAL_INTLEVEL4_VECTOR_VADDR
#undef  XCHAL_INTLEVEL5_VECTOR_VADDR
#undef  XCHAL_INTLEVEL6_VECTOR_VADDR
#undef  XCHAL_INTLEVEL7_VECTOR_VADDR
#undef  XCHAL_DEBUG_VECTOR_VADDR

#else

#define USER_VECTOR_VADDR		XCHAL_USER_VECTOR_VADDR
#define KERNEL_VECTOR_VADDR		XCHAL_KERNEL_VECTOR_VADDR
#define DOUBLEEXC_VECTOR_VADDR		XCHAL_DOUBLEEXC_VECTOR_VADDR
#define WINDOW_VECTORS_VADDR		XCHAL_WINDOW_VECTORS_VADDR
#define INTLEVEL2_VECTOR_VADDR		XCHAL_INTLEVEL2_VECTOR_VADDR
#define INTLEVEL3_VECTOR_VADDR		XCHAL_INTLEVEL3_VECTOR_VADDR
#define INTLEVEL4_VECTOR_VADDR		XCHAL_INTLEVEL4_VECTOR_VADDR
#define INTLEVEL5_VECTOR_VADDR		XCHAL_INTLEVEL5_VECTOR_VADDR
#define INTLEVEL6_VECTOR_VADDR		XCHAL_INTLEVEL6_VECTOR_VADDR
#define INTLEVEL7_VECTOR_VADDR		XCHAL_INTLEVEL6_VECTOR_VADDR
#define DEBUG_VECTOR_VADDR		XCHAL_DEBUG_VECTOR_VADDR

#endif

#endif /* _XTENSA_VECTORS_H */
