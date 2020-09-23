#ifndef _LINUX_FUTEX_H
#define _LINUX_FUTEX_H

#include <uapi/linux/futex.h>

struct inode;
struct mm_struct;
struct task_struct;
union ktime;

long do_futex(u32 __user *uaddr, int op, u32 val, union ktime *timeout,
	      u32 __user *uaddr2, u32 val2, u32 val3);

extern int
handle_futex_death(u32 __user *uaddr, struct task_struct *curr, int pi);

/*
 * Futexes are matched on equal values of this key.
 * The key type depends on whether it's a shared or private mapping.
 * Don't rearrange members without looking at hash_futex().
 *
 * offset is aligned to a multiple of sizeof(u32) (== 4) by definition.
 * We use the two low order bits of offset to tell what is the kind of key :
 *  00 : Private process futex (PTHREAD_PROCESS_PRIVATE)
 *       (no reference on an inode or mm)
 *  01 : Shared futex (PTHREAD_PROCESS_SHARED)
 *	mapped on a file (reference on the underlying inode)
 *  10 : Shared futex (PTHREAD_PROCESS_SHARED)
 *       (but private mapping on an mm, and reference taken on it)
*/

#define FUT_OFF_INODE    1 /* We set bit 0 if key has a reference on inode */
#define FUT_OFF_MMSHARED 2 /* We set bit 1 if key has a reference on mm */

union futex_key {
	struct {
<<<<<<< HEAD
		u64 i_seq;
		unsigned long pgoff;
		unsigned int offset;
	} shared;
	struct {
		union {
			struct mm_struct *mm;
			u64 __tmp;
		};
		unsigned long address;
		unsigned int offset;
	} private;
	struct {
		u64 ptr;
		unsigned long word;
		unsigned int offset;
	} both;
};

#define FUTEX_KEY_INIT (union futex_key) { .both = { .ptr = 0ULL } }
=======
		unsigned long pgoff;
		struct inode *inode;
		int offset;
	} shared;
	struct {
		unsigned long address;
		struct mm_struct *mm;
		int offset;
	} private;
	struct {
		unsigned long word;
		void *ptr;
		int offset;
	} both;
};

#define FUTEX_KEY_INIT (union futex_key) { .both = { .ptr = NULL } }
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

#ifdef CONFIG_FUTEX
extern void exit_robust_list(struct task_struct *curr);
extern void exit_pi_state_list(struct task_struct *curr);
#ifdef CONFIG_HAVE_FUTEX_CMPXCHG
#define futex_cmpxchg_enabled 1
#else
extern int futex_cmpxchg_enabled;
#endif
#else
static inline void exit_robust_list(struct task_struct *curr)
{
}
static inline void exit_pi_state_list(struct task_struct *curr)
{
}
#endif
#endif
