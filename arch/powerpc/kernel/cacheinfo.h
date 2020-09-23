#ifndef _PPC_CACHEINFO_H
#define _PPC_CACHEINFO_H

/* These are just hooks for sysfs.c to use. */
extern void cacheinfo_cpu_online(unsigned int cpu_id);
extern void cacheinfo_cpu_offline(unsigned int cpu_id);

<<<<<<< HEAD
/* Allow migration/suspend to tear down and rebuild the hierarchy. */
extern void cacheinfo_teardown(void);
extern void cacheinfo_rebuild(void);

=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
#endif /* _PPC_CACHEINFO_H */
