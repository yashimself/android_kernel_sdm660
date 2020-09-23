#
<<<<<<< HEAD
# Headers that are optional in usr/include/asm/
#
opt-header += kvm.h
opt-header += kvm_para.h
opt-header += a.out.h

#
# Headers that are mandatory in usr/include/asm/
#
header-y += auxvec.h
header-y += bitsperlong.h
header-y += byteorder.h
header-y += errno.h
header-y += fcntl.h
header-y += ioctl.h
header-y += ioctls.h
header-y += ipcbuf.h
header-y += mman.h
header-y += msgbuf.h
header-y += param.h
header-y += poll.h
header-y += posix_types.h
header-y += ptrace.h
header-y += resource.h
header-y += sembuf.h
header-y += setup.h
header-y += shmbuf.h
header-y += sigcontext.h
header-y += siginfo.h
header-y += signal.h
header-y += socket.h
header-y += sockios.h
header-y += stat.h
header-y += statfs.h
header-y += swab.h
header-y += termbits.h
header-y += termios.h
header-y += types.h
header-y += unistd.h

header-y += $(foreach hdr,$(opt-header), \
	      $(if \
		$(wildcard \
			$(srctree)/arch/$(SRCARCH)/include/uapi/asm/$(hdr) \
			$(srctree)/arch/$(SRCARCH)/include/asm/$(hdr) \
		), \
		$(hdr) \
		))
=======
# Headers that are mandatory in usr/include/asm/
#
mandatory-y += auxvec.h
mandatory-y += bitsperlong.h
mandatory-y += byteorder.h
mandatory-y += errno.h
mandatory-y += fcntl.h
mandatory-y += ioctl.h
mandatory-y += ioctls.h
mandatory-y += ipcbuf.h
mandatory-y += mman.h
mandatory-y += msgbuf.h
mandatory-y += param.h
mandatory-y += poll.h
mandatory-y += posix_types.h
mandatory-y += ptrace.h
mandatory-y += resource.h
mandatory-y += sembuf.h
mandatory-y += setup.h
mandatory-y += shmbuf.h
mandatory-y += sigcontext.h
mandatory-y += siginfo.h
mandatory-y += signal.h
mandatory-y += socket.h
mandatory-y += sockios.h
mandatory-y += stat.h
mandatory-y += statfs.h
mandatory-y += swab.h
mandatory-y += termbits.h
mandatory-y += termios.h
mandatory-y += types.h
mandatory-y += unistd.h
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
