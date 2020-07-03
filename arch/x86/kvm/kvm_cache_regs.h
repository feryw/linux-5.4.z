/* SPDX-License-Identifier: GPL-2.0 */
#ifndef ASM_KVM_CACHE_REGS_H
#define ASM_KVM_CACHE_REGS_H

#include <linux/kvm_host.h>

#define KVM_POSSIBLE_CR0_GUEST_BITS X86_CR0_TS
#define KVM_POSSIBLE_CR4_GUEST_BITS				  \
	(X86_CR4_PVI | X86_CR4_DE | X86_CR4_PCE | X86_CR4_OSFXSR  \
	 | X86_CR4_OSXMMEXCPT | X86_CR4_LA57 | X86_CR4_PGE | X86_CR4_TSD)

#define BUILD_KVM_GPR_ACCESSORS(lname, uname)				      \
static __always_inline unsigned long kvm_##lname##_read(struct kvm_vcpu *vcpu)\
{									      \
	return vcpu->arch.regs[VCPU_REGS_##uname];			      \
}									      \
static __always_inline void kvm_##lname##_write(struct kvm_vcpu *vcpu,	      \
						unsigned long val)	      \
{									      \
	vcpu->arch.regs[VCPU_REGS_##uname] = val;			      \
}
BUILD_KVM_GPR_ACCESSORS(rax, RAX)
BUILD_KVM_GPR_ACCESSORS(rbx, RBX)
BUILD_KVM_GPR_ACCESSORS(rcx, RCX)
BUILD_KVM_GPR_ACCESSORS(rdx, RDX)
BUILD_KVM_GPR_ACCESSORS(rbp, RBP)
BUILD_KVM_GPR_ACCESSORS(rsi, RSI)
BUILD_KVM_GPR_ACCESSORS(rdi, RDI)
#ifdef CONFIG_X86_64
BUILD_KVM_GPR_ACCESSORS(r8,  R8)
BUILD_KVM_GPR_ACCESSORS(r9,  R9)
BUILD_KVM_GPR_ACCESSORS(r10, R10)
BUILD_KVM_GPR_ACCESSORS(r11, R11)
BUILD_KVM_GPR_ACCESSORS(r12, R12)
BUILD_KVM_GPR_ACCESSORS(r13, R13)
BUILD_KVM_GPR_ACCESSORS(r14, R14)
BUILD_KVM_GPR_ACCESSORS(r15, R15)
#endif

static inline unsigned long kvm_register_read(struct kvm_vcpu *vcpu,
					      enum kvm_reg reg)
{
	if (!test_bit(reg, (unsigned long *)&vcpu->arch.regs_avail))
		kvm_x86_ops->cache_reg(vcpu, reg);

	return vcpu->arch.regs[reg];
}

static inline void kvm_register_write(struct kvm_vcpu *vcpu,
				      enum kvm_reg reg,
				      unsigned long val)
{
	vcpu->arch.regs[reg] = val;
	__set_bit(reg, (unsigned long *)&vcpu->arch.regs_dirty);
	__set_bit(reg, (unsigned long *)&vcpu->arch.regs_avail);
}

static inline unsigned long kvm_rip_read(struct kvm_vcpu *vcpu)
{
	return kvm_register_read(vcpu, VCPU_REGS_RIP);
}

static inline void kvm_rip_write(struct kvm_vcpu *vcpu, unsigned long val)
{
	kvm_register_write(vcpu, VCPU_REGS_RIP, val);
}

static inline unsigned long kvm_rsp_read(struct kvm_vcpu *vcpu)
{
	return kvm_register_read(vcpu, VCPU_REGS_RSP);
}

static inline void kvm_rsp_write(struct kvm_vcpu *vcpu, unsigned long val)
{
	kvm_register_write(vcpu, VCPU_REGS_RSP, val);
}

static inline u64 kvm_pdptr_read(struct kvm_vcpu *vcpu, int index)
{
	might_sleep();  /* on svm */

	if (!test_bit(VCPU_EXREG_PDPTR,
		      (unsigned long *)&vcpu->arch.regs_avail))
		kvm_x86_ops->cache_reg(vcpu, (enum kvm_reg)VCPU_EXREG_PDPTR);

	return vcpu->arch.walk_mmu->pdptrs[index];
}

static inline ulong kvm_read_cr0_bits(struct kvm_vcpu *vcpu, ulong mask)
{
	ulong tmask = mask & KVM_POSSIBLE_CR0_GUEST_BITS;
	if (tmask & vcpu->arch.cr0_guest_owned_bits)
		kvm_x86_ops->decache_cr0_guest_bits(vcpu);
	return vcpu->arch.cr0 & mask;
}

static inline ulong kvm_read_cr0(struct kvm_vcpu *vcpu)
{
	return kvm_read_cr0_bits(vcpu, ~0UL);
}

static inline ulong kvm_read_cr4_bits(struct kvm_vcpu *vcpu, ulong mask)
{
	ulong tmask = mask & KVM_POSSIBLE_CR4_GUEST_BITS;
	if (tmask & vcpu->arch.cr4_guest_owned_bits)
		kvm_x86_ops->decache_cr4_guest_bits(vcpu);
	return vcpu->arch.cr4 & mask;
}

static inline ulong kvm_read_cr3(struct kvm_vcpu *vcpu)
{
	if (!test_bit(VCPU_EXREG_CR3, (ulong *)&vcpu->arch.regs_avail))
		kvm_x86_ops->decache_cr3(vcpu);
	return vcpu->arch.cr3;
}

static inline ulong kvm_read_cr4(struct kvm_vcpu *vcpu)
{
	return kvm_read_cr4_bits(vcpu, ~0UL);
}

static inline u64 kvm_read_edx_eax(struct kvm_vcpu *vcpu)
{
	return (kvm_rax_read(vcpu) & -1u)
		| ((u64)(kvm_rdx_read(vcpu) & -1u) << 32);
}

static inline void enter_guest_mode(struct kvm_vcpu *vcpu)
{
	vcpu->arch.hflags |= HF_GUEST_MASK;
}

static inline void leave_guest_mode(struct kvm_vcpu *vcpu)
{
	vcpu->arch.hflags &= ~HF_GUEST_MASK;

	if (vcpu->arch.load_eoi_exitmap_pending) {
		vcpu->arch.load_eoi_exitmap_pending = false;
		kvm_make_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu);
	}
}

static inline bool is_guest_mode(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.hflags & HF_GUEST_MASK;
}

static inline bool is_smm(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.hflags & HF_SMM_MASK;
}

#endif
