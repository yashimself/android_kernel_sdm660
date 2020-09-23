#
# Makefile for the linux squashfs routines.
#

obj-$(CONFIG_SQUASHFS) += squashfs.o
squashfs-y += block.o cache.o dir.o export.o file.o fragment.o id.o inode.o
squashfs-y += namei.o super.o symlink.o decompressor.o
<<<<<<< HEAD
squashfs-y += file_direct.o page_actor.o
=======
squashfs-$(CONFIG_SQUASHFS_FILE_CACHE) += file_cache.o
squashfs-$(CONFIG_SQUASHFS_FILE_DIRECT) += file_direct.o page_actor.o
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
squashfs-$(CONFIG_SQUASHFS_DECOMP_SINGLE) += decompressor_single.o
squashfs-$(CONFIG_SQUASHFS_DECOMP_MULTI) += decompressor_multi.o
squashfs-$(CONFIG_SQUASHFS_DECOMP_MULTI_PERCPU) += decompressor_multi_percpu.o
squashfs-$(CONFIG_SQUASHFS_XATTR) += xattr.o xattr_id.o
squashfs-$(CONFIG_SQUASHFS_LZ4) += lz4_wrapper.o
squashfs-$(CONFIG_SQUASHFS_LZO) += lzo_wrapper.o
squashfs-$(CONFIG_SQUASHFS_XZ) += xz_wrapper.o
squashfs-$(CONFIG_SQUASHFS_ZLIB) += zlib_wrapper.o
