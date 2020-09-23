<<<<<<< HEAD
/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
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
 */
#include "hab.h"
#include "hab_grantable.h"

#define MAX_LINE_SIZE 128

int hab_stat_init(struct hab_driver *driver)
{
	return hab_stat_init_sub(driver);
}

int hab_stat_deinit(struct hab_driver *driver)
{
	return hab_stat_deinit_sub(driver);
}

/*
 * If all goes well the return value is the formated print and concatenated
 * original dest string.
 */
static int hab_stat_buffer_print(char *dest,
		int dest_size, const char *fmt, ...)
{
<<<<<<< HEAD
	va_list args;
	char line[MAX_LINE_SIZE];
	int ret;
=======
	va_list args = {0};
	char line[MAX_LINE_SIZE] = {0};
	int ret = 0;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	va_start(args, fmt);
	ret = vsnprintf(line, sizeof(line), fmt, args);
	va_end(args);
	if (ret > 0)
<<<<<<< HEAD
		ret = strlcat(dest, line, dest_size);
=======
		ret = (int)strlcat(dest, line, dest_size);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	return ret;
}

int hab_stat_show_vchan(struct hab_driver *driver,
		char *buf, int size)
{
<<<<<<< HEAD
	int i, ret = 0;

	ret = strlcpy(buf, "", size);
	for (i = 0; i < driver->ndevices; i++) {
		struct hab_device *dev = &driver->devp[i];
		struct physical_channel *pchan;
		struct virtual_channel *vc;
=======
	int i = 0, ret = 0;

	ret = (int)strlcpy(buf, "", size);
	for (i = 0; i < driver->ndevices; i++) {
		struct hab_device *dev = &driver->devp[i];
		struct physical_channel *pchan = NULL;
		struct virtual_channel *vc = NULL;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

		spin_lock_bh(&dev->pchan_lock);
		list_for_each_entry(pchan, &dev->pchannels, node) {
			if (!pchan->vcnt)
				continue;

			ret = hab_stat_buffer_print(buf, size,
<<<<<<< HEAD
				"mmid %s role %d local %d remote %d vcnt %d:\n",
				pchan->name, pchan->is_be, pchan->vmid_local,
				pchan->vmid_remote, pchan->vcnt);
=======
				"nm %s r %d lc %d rm %d sq_t %d sq_r %d st 0x%x vn %d:\n",
				pchan->name, pchan->is_be, pchan->vmid_local,
				pchan->vmid_remote, pchan->sequence_tx,
				pchan->sequence_rx, pchan->status, pchan->vcnt);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

			read_lock(&pchan->vchans_lock);
			list_for_each_entry(vc, &pchan->vchannels, pnode) {
				ret = hab_stat_buffer_print(buf, size,
<<<<<<< HEAD
						 "%08X ", vc->id);
=======
					"%08X(%d:%d) ", vc->id,
					get_refcnt(vc->refcount),
					vc->otherend_closed);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
			}
			ret = hab_stat_buffer_print(buf, size, "\n");
			read_unlock(&pchan->vchans_lock);
		}
		spin_unlock_bh(&dev->pchan_lock);
	}

	return ret;
}

int hab_stat_show_ctx(struct hab_driver *driver,
		char *buf, int size)
{
	int ret = 0;
<<<<<<< HEAD
	struct uhab_context *ctx;

	ret = strlcpy(buf, "", size);
=======
	struct uhab_context *ctx = NULL;

	ret = (int)strlcpy(buf, "", size);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	spin_lock_bh(&hab_driver.drvlock);
	ret = hab_stat_buffer_print(buf, size,
					"Total contexts %d\n",
					driver->ctx_cnt);
	list_for_each_entry(ctx, &hab_driver.uctx_list, node) {
		ret = hab_stat_buffer_print(buf, size,
<<<<<<< HEAD
			"ctx %d K %d close %d vc %d exp %d imp %d open %d\n",
			ctx->owner, ctx->kernel, ctx->closing,
			ctx->vcnt, ctx->export_total,
			ctx->import_total, ctx->pending_cnt);
=======
		"ctx %d K %d close %d vc %d exp %d imp %d open %d ref %d\n",
			ctx->owner, ctx->kernel, ctx->closing,
			ctx->vcnt, ctx->export_total,
			ctx->import_total, ctx->pending_cnt,
			get_refcnt(ctx->refcount));
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	}
	spin_unlock_bh(&hab_driver.drvlock);

	return ret;
}

static int get_pft_tbl_total_size(struct compressed_pfns *pfn_table)
{
<<<<<<< HEAD
	int i, total_size = 0;
=======
	int i = 0, total_size = 0;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	for (i = 0; i < pfn_table->nregions; i++)
		total_size += pfn_table->region[i].size * PAGE_SIZE;

	return total_size;
}

static int print_ctx_total_expimp(struct uhab_context *ctx,
		char *buf, int size)
{
<<<<<<< HEAD
	struct compressed_pfns *pfn_table;
	int exp_total = 0, imp_total = 0;
	int exp_cnt = 0, imp_cnt = 0;
	struct export_desc *exp;

	read_lock(&ctx->exp_lock);
	list_for_each_entry(exp, &ctx->exp_whse, node) {
		pfn_table =	(struct compressed_pfns *)exp->payload;
		exp_total += get_pft_tbl_total_size(pfn_table);
		exp_cnt++;
	}
	read_unlock(&ctx->exp_lock);

	spin_lock_bh(&ctx->imp_lock);
	list_for_each_entry(exp, &ctx->imp_whse, node) {
		if (habmm_imp_hyp_map_check(ctx->import_ctx, exp)) {
			pfn_table =	(struct compressed_pfns *)exp->payload;
			imp_total += get_pft_tbl_total_size(pfn_table);
			imp_cnt++;
		}
	}
=======
	struct compressed_pfns *pfn_table = NULL;
	int exp_total = 0, imp_total = 0;
	int exp_cnt = 0, imp_cnt = 0;
	struct export_desc *exp = NULL;
	int exim_size = 0;

	read_lock(&ctx->exp_lock);
	hab_stat_buffer_print(buf, size, "export[expid:vcid:size]: ");
	list_for_each_entry(exp, &ctx->exp_whse, node) {
		pfn_table =	(struct compressed_pfns *)exp->payload;
		exim_size = get_pft_tbl_total_size(pfn_table);
		exp_total += exim_size;
		exp_cnt++;
		hab_stat_buffer_print(buf, size,
			"[%d:%x:%d] ", exp->export_id,
			exp->vcid_local, exim_size);
	}
	hab_stat_buffer_print(buf, size, "\n");
	read_unlock(&ctx->exp_lock);

	spin_lock_bh(&ctx->imp_lock);
	hab_stat_buffer_print(buf, size, "import[expid:vcid:size]: ");
	list_for_each_entry(exp, &ctx->imp_whse, node) {
		if (habmm_imp_hyp_map_check(ctx->import_ctx, exp)) {
			pfn_table =	(struct compressed_pfns *)exp->payload;
			exim_size = get_pft_tbl_total_size(pfn_table);
			imp_total += exim_size;
			imp_cnt++;
			hab_stat_buffer_print(buf, size,
				"[%d:%x:%d] ", exp->export_id,
				exp->vcid_local, exim_size);
		}
	}
	hab_stat_buffer_print(buf, size, "\n");
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	spin_unlock_bh(&ctx->imp_lock);

	if (exp_cnt || exp_total || imp_cnt || imp_total)
		return hab_stat_buffer_print(buf, size,
				"ctx %d exp %d size %d imp %d size %d\n",
				ctx->owner, exp_cnt, exp_total,
				imp_cnt, imp_total);
	else
		return 0;
}

int hab_stat_show_expimp(struct hab_driver *driver,
		int pid, char *buf, int size)
{
<<<<<<< HEAD
	struct uhab_context *ctx;
	int ret;

	ret = strlcpy(buf, "", size);
=======
	struct uhab_context *ctx = NULL;
	int ret = 0;

	(void)driver;
	ret = (int)strlcpy(buf, "", size);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	spin_lock_bh(&hab_driver.drvlock);
	list_for_each_entry(ctx, &hab_driver.uctx_list, node) {
		if (pid == ctx->owner)
			ret = print_ctx_total_expimp(ctx, buf, size);
	}
	spin_unlock_bh(&hab_driver.drvlock);

	return ret;
}
