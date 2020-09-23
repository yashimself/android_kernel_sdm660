#ifndef _ARM_LIBFDT_ENV_H
#define _ARM_LIBFDT_ENV_H

<<<<<<< HEAD
#include <linux/limits.h>
=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
#include <linux/types.h>
#include <linux/string.h>
#include <asm/byteorder.h>

<<<<<<< HEAD
#define INT32_MAX	S32_MAX
#define UINT32_MAX	U32_MAX
=======
#define INT_MAX			((int)(~0U>>1))
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

typedef __be16 fdt16_t;
typedef __be32 fdt32_t;
typedef __be64 fdt64_t;

#define fdt16_to_cpu(x)		be16_to_cpu(x)
#define cpu_to_fdt16(x)		cpu_to_be16(x)
#define fdt32_to_cpu(x)		be32_to_cpu(x)
#define cpu_to_fdt32(x)		cpu_to_be32(x)
#define fdt64_to_cpu(x)		be64_to_cpu(x)
#define cpu_to_fdt64(x)		cpu_to_be64(x)

#endif
