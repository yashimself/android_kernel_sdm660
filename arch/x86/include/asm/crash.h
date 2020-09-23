#ifndef _ASM_X86_CRASH_H
#define _ASM_X86_CRASH_H

<<<<<<< HEAD
struct kimage;

=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
int crash_load_segments(struct kimage *image);
int crash_copy_backup_region(struct kimage *image);
int crash_setup_memmap_entries(struct kimage *image,
		struct boot_params *params);

#endif /* _ASM_X86_CRASH_H */
