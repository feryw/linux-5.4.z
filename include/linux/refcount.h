/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_REFCOUNT_H
#define _LINUX_REFCOUNT_H

#include <linux/atomic.h>
#include <linux/compiler.h>
#include <linux/limits.h>
#include <linux/spinlock_types.h>

struct mutex;

/**
 * struct refcount_t - variant of atomic_t specialized for reference counts
 * @refs: atomic_t counter field
 *
 * The counter saturates at REFCOUNT_SATURATED and will not move once
 * there. This avoids wrapping the counter and causing 'spurious'
 * use-after-free bugs.
 */
typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;

#define REFCOUNT_INIT(n)	{ .refs = ATOMIC_INIT(n), }

/**
 * refcount_set - set a refcount's value
 * @r: the refcount
 * @n: value to which the refcount will be set
 */
static inline void refcount_set(refcount_t *r, int n)
{
	atomic_set(&r->refs, n);
}

/**
 * refcount_read - get a refcount's value
 * @r: the refcount
 *
 * Return: the refcount's value
 */
static inline unsigned int refcount_read(const refcount_t *r)
{
	return atomic_read(&r->refs);
}

#ifdef CONFIG_REFCOUNT_FULL
#include <linux/bug.h>

#define REFCOUNT_MAX		INT_MAX
#define REFCOUNT_SATURATED	(INT_MIN / 2)

/*
 * Variant of atomic_t specialized for reference counts.
 *
 * The interface matches the atomic_t interface (to aid in porting) but only
 * provides the few functions one should use for reference counting.
 *
 * Saturation semantics
 * ====================
 *
 * refcount_t differs from atomic_t in that the counter saturates at
 * REFCOUNT_SATURATED and will not move once there. This avoids wrapping the
 * counter and causing 'spurious' use-after-free issues. In order to avoid the
 * cost associated with introducing cmpxchg() loops into all of the saturating
 * operations, we temporarily allow the counter to take on an unchecked value
 * and then explicitly set it to REFCOUNT_SATURATED on detecting that underflow
 * or overflow has occurred. Although this is racy when multiple threads
 * access the refcount concurrently, by placing REFCOUNT_SATURATED roughly
 * equidistant from 0 and INT_MAX we minimise the scope for error:
 *
 * 	                           INT_MAX     REFCOUNT_SATURATED   UINT_MAX
 *   0                          (0x7fff_ffff)    (0xc000_0000)    (0xffff_ffff)
 *   +--------------------------------+----------------+----------------+
 *                                     <---------- bad value! ---------->
 *
 * (in a signed view of the world, the "bad value" range corresponds to
 * a negative counter value).
 *
 * As an example, consider a refcount_inc() operation that causes the counter
 * to overflow:
 *
 * 	int old = atomic_fetch_add_relaxed(r);
 *	// old is INT_MAX, refcount now INT_MIN (0x8000_0000)
 *	if (old < 0)
 *		atomic_set(r, REFCOUNT_SATURATED);
 *
 * If another thread also performs a refcount_inc() operation between the two
 * atomic operations, then the count will continue to edge closer to 0. If it
 * reaches a value of 1 before /any/ of the threads reset it to the saturated
 * value, then a concurrent refcount_dec_and_test() may erroneously free the
 * underlying object. Given the precise timing details involved with the
 * round-robin scheduling of each thread manipulating the refcount and the need
 * to hit the race multiple times in succession, there doesn't appear to be a
 * practical avenue of attack even if using refcount_add() operations with
 * larger increments.
 *
 * Memory ordering
 * ===============
 *
 * Memory ordering rules are slightly relaxed wrt regular atomic_t functions
 * and provide only what is strictly required for refcounts.
 *
 * The increments are fully relaxed; these will not provide ordering. The
 * rationale is that whatever is used to obtain the object we're increasing the
 * reference count on will provide the ordering. For locked data structures,
 * its the lock acquire, for RCU/lockless data structures its the dependent
 * load.
 *
 * Do note that inc_not_zero() provides a control dependency which will order
 * future stores against the inc, this ensures we'll never modify the object
 * if we did not in fact acquire a reference.
 *
 * The decrements will provide release order, such that all the prior loads and
 * stores will be issued before, it also provides a control dependency, which
 * will order us against the subsequent free().
 *
 * The control dependency is against the load of the cmpxchg (ll/sc) that
 * succeeded. This means the stores aren't fully ordered, but this is fine
 * because the 1->0 transition indicates no concurrency.
 *
 * Note that the allocator is responsible for ordering things between free()
 * and alloc().
 *
 * The decrements dec_and_test() and sub_and_test() also provide acquire
 * ordering on success.
 *
 */

/**
 * refcount_add_not_zero - add a value to a refcount unless it is 0
 * @i: the value to add to the refcount
 * @r: the refcount
 *
 * Will saturate at REFCOUNT_SATURATED and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It does provide a control dependency
 * and thereby orders future stores. See the comment on top.
 *
 * Use of this function is not recommended for the normal reference counting
 * use case in which references are taken and released one at a time.  In these
 * cases, refcount_inc(), or one of its variants, should instead be used to
 * increment a reference count.
 *
 * Return: false if the passed refcount is 0, true otherwise
 */
static inline __must_check bool refcount_add_not_zero(int i, refcount_t *r)
{
	int old = refcount_read(r);

	do {
		if (!old)
			break;
	} while (!atomic_try_cmpxchg_relaxed(&r->refs, &old, old + i));

	if (unlikely(old < 0 || old + i < 0)) {
		refcount_set(r, REFCOUNT_SATURATED);
		WARN_ONCE(1, "refcount_t: saturated; leaking memory.\n");
	}

	return old;
}

/**
 * refcount_add - add a value to a refcount
 * @i: the value to add to the refcount
 * @r: the refcount
 *
 * Similar to atomic_add(), but will saturate at REFCOUNT_SATURATED and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It does provide a control dependency
 * and thereby orders future stores. See the comment on top.
 *
 * Use of this function is not recommended for the normal reference counting
 * use case in which references are taken and released one at a time.  In these
 * cases, refcount_inc(), or one of its variants, should instead be used to
 * increment a reference count.
 */
static inline void refcount_add(int i, refcount_t *r)
{
	int old = atomic_fetch_add_relaxed(i, &r->refs);

	WARN_ONCE(!old, "refcount_t: addition on 0; use-after-free.\n");
	if (unlikely(old <= 0 || old + i <= 0)) {
		refcount_set(r, REFCOUNT_SATURATED);
		WARN_ONCE(old, "refcount_t: saturated; leaking memory.\n");
	}
}

/**
 * refcount_inc_not_zero - increment a refcount unless it is 0
 * @r: the refcount to increment
 *
 * Similar to atomic_inc_not_zero(), but will saturate at REFCOUNT_SATURATED
 * and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It does provide a control dependency
 * and thereby orders future stores. See the comment on top.
 *
 * Return: true if the increment was successful, false otherwise
 */
static inline __must_check bool refcount_inc_not_zero(refcount_t *r)
{
	return refcount_add_not_zero(1, r);
}

/**
 * refcount_inc - increment a refcount
 * @r: the refcount to increment
 *
 * Similar to atomic_inc(), but will saturate at REFCOUNT_SATURATED and WARN.
 *
 * Provides no memory ordering, it is assumed the caller already has a
 * reference on the object.
 *
 * Will WARN if the refcount is 0, as this represents a possible use-after-free
 * condition.
 */
static inline void refcount_inc(refcount_t *r)
{
	refcount_add(1, r);
}

/**
 * refcount_sub_and_test - subtract from a refcount and test if it is 0
 * @i: amount to subtract from the refcount
 * @r: the refcount
 *
 * Similar to atomic_dec_and_test(), but it will WARN, return false and
 * ultimately leak on underflow and will fail to decrement when saturated
 * at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are done
 * before, and provides an acquire ordering on success such that free()
 * must come after.
 *
 * Use of this function is not recommended for the normal reference counting
 * use case in which references are taken and released one at a time.  In these
 * cases, refcount_dec(), or one of its variants, should instead be used to
 * decrement a reference count.
 *
 * Return: true if the resulting refcount is 0, false otherwise
 */
static inline __must_check bool refcount_sub_and_test(int i, refcount_t *r)
{
	int old = atomic_fetch_sub_release(i, &r->refs);

	if (old == i) {
		smp_acquire__after_ctrl_dep();
		return true;
	}

	if (unlikely(old < 0 || old - i < 0)) {
		refcount_set(r, REFCOUNT_SATURATED);
		WARN_ONCE(1, "refcount_t: underflow; use-after-free.\n");
	}

	return false;
}

/**
 * refcount_dec_and_test - decrement a refcount and test if it is 0
 * @r: the refcount
 *
 * Similar to atomic_dec_and_test(), it will WARN on underflow and fail to
 * decrement when saturated at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are done
 * before, and provides an acquire ordering on success such that free()
 * must come after.
 *
 * Return: true if the resulting refcount is 0, false otherwise
 */
static inline __must_check bool refcount_dec_and_test(refcount_t *r)
{
	return refcount_sub_and_test(1, r);
}

/**
 * refcount_dec - decrement a refcount
 * @r: the refcount
 *
 * Similar to atomic_dec(), it will WARN on underflow and fail to decrement
 * when saturated at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are done
 * before.
 */
static inline void refcount_dec(refcount_t *r)
{
	int old = atomic_fetch_sub_release(1, &r->refs);

	if (unlikely(old <= 1)) {
		refcount_set(r, REFCOUNT_SATURATED);
		WARN_ONCE(1, "refcount_t: decrement hit 0; leaking memory.\n");
	}
}
#else /* CONFIG_REFCOUNT_FULL */

#define REFCOUNT_MAX		INT_MAX
#define REFCOUNT_SATURATED	(INT_MIN / 2)

# ifdef CONFIG_ARCH_HAS_REFCOUNT
#  include <asm/refcount.h>
# else
static inline __must_check bool refcount_add_not_zero(int i, refcount_t *r)
{
	return atomic_add_unless(&r->refs, i, 0);
}

static inline void refcount_add(int i, refcount_t *r)
{
	atomic_add(i, &r->refs);
}

static inline __must_check bool refcount_inc_not_zero(refcount_t *r)
{
	return atomic_add_unless(&r->refs, 1, 0);
}

static inline void refcount_inc(refcount_t *r)
{
	atomic_inc(&r->refs);
}

static inline __must_check bool refcount_sub_and_test(int i, refcount_t *r)
{
	return atomic_sub_and_test(i, &r->refs);
}

static inline __must_check bool refcount_dec_and_test(refcount_t *r)
{
	return atomic_dec_and_test(&r->refs);
}

static inline void refcount_dec(refcount_t *r)
{
	atomic_dec(&r->refs);
}
# endif /* !CONFIG_ARCH_HAS_REFCOUNT */
#endif /* !CONFIG_REFCOUNT_FULL */

extern __must_check bool refcount_dec_if_one(refcount_t *r);
extern __must_check bool refcount_dec_not_one(refcount_t *r);
extern __must_check bool refcount_dec_and_mutex_lock(refcount_t *r, struct mutex *lock);
extern __must_check bool refcount_dec_and_lock(refcount_t *r, spinlock_t *lock);
extern __must_check bool refcount_dec_and_lock_irqsave(refcount_t *r,
						       spinlock_t *lock,
						       unsigned long *flags);
#endif /* _LINUX_REFCOUNT_H */
