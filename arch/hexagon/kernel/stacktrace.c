/*
 * Stacktrace support for Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <linux/sched.h>
#include <linux/stacktrace.h>
#include <linux/thread_info.h>
#include <linux/module.h>

<<<<<<< HEAD
=======
register unsigned long current_frame_pointer asm("r30");

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
struct stackframe {
	unsigned long fp;
	unsigned long rets;
};

/*
 * Save stack-backtrace addresses into a stack_trace buffer.
 */
void save_stack_trace(struct stack_trace *trace)
{
	unsigned long low, high;
	unsigned long fp;
	struct stackframe *frame;
	int skip = trace->skip;

	low = (unsigned long)task_stack_page(current);
	high = low + THREAD_SIZE;
<<<<<<< HEAD
	fp = (unsigned long)__builtin_frame_address(0);
=======
	fp = current_frame_pointer;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	while (fp >= low && fp <= (high - sizeof(*frame))) {
		frame = (struct stackframe *)fp;

		if (skip) {
			skip--;
		} else {
			trace->entries[trace->nr_entries++] = frame->rets;
			if (trace->nr_entries >= trace->max_entries)
				break;
		}

		/*
		 * The next frame must be at a higher address than the
		 * current frame.
		 */
		low = fp + sizeof(*frame);
		fp = frame->fp;
	}
}
EXPORT_SYMBOL_GPL(save_stack_trace);
