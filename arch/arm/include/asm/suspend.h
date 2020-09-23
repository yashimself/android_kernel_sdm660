#ifndef __ASM_ARM_SUSPEND_H
#define __ASM_ARM_SUSPEND_H

struct sleep_save_sp {
	u32 *save_ptr_stash;
	u32 save_ptr_stash_phys;
};

extern void cpu_resume(void);
<<<<<<< HEAD
extern void cpu_resume_no_hyp(void);
=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
extern void cpu_resume_arm(void);
extern int cpu_suspend(unsigned long, int (*)(unsigned long));

#endif
