/*
<<<<<<< HEAD
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
=======
 * Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
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
#include <linux/of_address.h>
#include <linux/debugfs.h>
#include <linux/memblock.h>
<<<<<<< HEAD
=======
#include <soc/qcom/early_domain.h>
#include <linux/suspend.h>
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

#include "msm_drv.h"
#include "msm_mmu.h"
#include "sde_kms.h"
#include "sde_hw_mdss.h"
#include "sde_hw_util.h"
#include "sde_hw_intf.h"
#include "sde_hw_catalog.h"
#include "sde_rm.h"
#include "dsi_display.h"
#include "sde_hdmi.h"
#include "sde_crtc.h"
<<<<<<< HEAD
=======
#include "sde_plane.h"
#include "sde_shd.h"
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

#define MDP_SSPP_TOP0_OFF		0x1000
#define DISP_INTF_SEL			0x004
#define SPLIT_DISPLAY_EN		0x2F4

/* scratch registers */
#define SCRATCH_REGISTER_0		0x014
#define SCRATCH_REGISTER_1		0x018
#define SCRATCH_REGISTER_2		0x01C

#define SDE_LK_RUNNING_VALUE		0xC001CAFE
#define SDE_LK_STOP_SPLASH_VALUE	0xDEADDEAD
#define SDE_LK_EXIT_VALUE		0xDEADBEEF
<<<<<<< HEAD
=======
#define SDE_LK_INTERMEDIATE_STOP	0xBEEFBEEF
#define SDE_LK_KERNEL_SPLASH_TALK_LOOP	20
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

#define INTF_HDMI_SEL                  (BIT(25) | BIT(24))
#define INTF_DSI0_SEL                  BIT(8)
#define INTF_DSI1_SEL                  BIT(16)

static DEFINE_MUTEX(sde_splash_lock);

<<<<<<< HEAD
=======
static struct splash_pipe_caps splash_pipe_cap[MAX_BLOCKS] = {
	{SSPP_VIG0, BIT(0), 0x7 << 0, BIT(0)},
	{SSPP_VIG1, BIT(1), 0x7 << 3, BIT(2)},
	{SSPP_VIG2, BIT(2), 0x7 << 6, BIT(4)},
	{SSPP_VIG3, BIT(18), 0x7 << 26, BIT(6)},
	{SSPP_RGB0, BIT(3), 0x7 << 9, BIT(8)},
	{SSPP_RGB1, BIT(4), 0x7 << 12, BIT(10)},
	{SSPP_RGB2, BIT(5), 0x7 << 15, BIT(12)},
	{SSPP_RGB3, BIT(19), 0x7 << 29, BIT(14)},
	{SSPP_DMA0, BIT(11), 0x7 << 18, BIT(16)},
	{SSPP_DMA1, BIT(12), 0x7 << 21, BIT(18)},
	{SSPP_CURSOR0, 0, 0, 0},
	{SSPP_CURSOR1, 0, 0, 0},
};

static inline uint32_t _sde_splash_get_pipe_arrary_index(enum sde_sspp pipe)
{
	uint32_t i = 0, index = MAX_BLOCKS;

	for (i = 0; i < MAX_BLOCKS; i++) {
		if (pipe == splash_pipe_cap[i].pipe) {
			index = i;
			break;
		}
	}

	return index;
}

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
/*
 * In order to free reseved memory from bootup, and we are not
 * able to call the __init free functions, so we need to free
 * this memory by ourselves using the free_reserved_page() function.
 */
static void _sde_splash_free_bootup_memory_to_system(phys_addr_t phys,
						size_t size)
{
	unsigned long pfn_start, pfn_end, pfn_idx;

	memblock_free(phys, size);

	pfn_start = phys >> PAGE_SHIFT;
	pfn_end = (phys + size) >> PAGE_SHIFT;

	for (pfn_idx = pfn_start; pfn_idx < pfn_end; pfn_idx++)
		free_reserved_page(pfn_to_page(pfn_idx));
}

<<<<<<< HEAD
static int _sde_splash_parse_dt_get_lk_pool_node(struct drm_device *dev,
					struct sde_splash_info *sinfo)
{
	struct device_node *parent, *node;
	struct resource r;
	int ret = 0;

	if (!sinfo)
		return -EINVAL;

	parent = of_find_node_by_path("/reserved-memory");
	if (!parent)
		return -EINVAL;

	node = of_find_node_by_name(parent, "lk_pool");
	if (!node) {
		SDE_ERROR("mem reservation for lk_pool is not presented\n");
		ret = -EINVAL;
		goto parent_node_err;
	}

	/* find the mode */
	if (of_address_to_resource(node, 0, &r)) {
		ret = -EINVAL;
		goto child_node_err;
	}

	sinfo->lk_pool_paddr = (dma_addr_t)r.start;
	sinfo->lk_pool_size = r.end - r.start;

	DRM_INFO("lk_pool: addr:%pK, size:%pK\n",
			(void *)sinfo->lk_pool_paddr,
			(void *)sinfo->lk_pool_size);

child_node_err:
	of_node_put(node);

parent_node_err:
	of_node_put(parent);

	return ret;
}

=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
static int _sde_splash_parse_dt_get_display_node(struct drm_device *dev,
					struct sde_splash_info *sinfo)
{
	unsigned long size = 0;
	dma_addr_t start;
	struct device_node *node;
	int ret = 0, i = 0, len = 0;

	/* get reserved memory for display module */
	if (of_get_property(dev->dev->of_node, "contiguous-region", &len))
		sinfo->splash_mem_num = len / sizeof(u32);
	else
		sinfo->splash_mem_num = 0;

	sinfo->splash_mem_paddr =
			kmalloc(sizeof(phys_addr_t) * sinfo->splash_mem_num,
				GFP_KERNEL);
	if (!sinfo->splash_mem_paddr) {
		SDE_ERROR("alloc splash_mem_paddr failed\n");
		return -ENOMEM;
	}

	sinfo->splash_mem_size =
			kmalloc(sizeof(size_t) * sinfo->splash_mem_num,
				GFP_KERNEL);
	if (!sinfo->splash_mem_size) {
		SDE_ERROR("alloc splash_mem_size failed\n");
		goto error;
	}

	sinfo->obj = kmalloc(sizeof(struct drm_gem_object *) *
				sinfo->splash_mem_num, GFP_KERNEL);
	if (!sinfo->obj) {
		SDE_ERROR("construct splash gem objects failed\n");
		goto error;
	}

	for (i = 0; i < sinfo->splash_mem_num; i++) {
		node = of_parse_phandle(dev->dev->of_node,
					"contiguous-region", i);

		if (node) {
			struct resource r;

			ret = of_address_to_resource(node, 0, &r);
			if (ret)
				return ret;

			size = r.end - r.start;
			start = (dma_addr_t)r.start;

			sinfo->splash_mem_paddr[i] = start;
			sinfo->splash_mem_size[i] = size;

			DRM_INFO("blk: %d, addr:%pK, size:%pK\n",
				i, (void *)sinfo->splash_mem_paddr[i],
				(void *)sinfo->splash_mem_size[i]);

			of_node_put(node);
		}
	}

	return ret;

error:
	kfree(sinfo->splash_mem_paddr);
	sinfo->splash_mem_paddr = NULL;

	kfree(sinfo->splash_mem_size);
	sinfo->splash_mem_size = NULL;

	return -ENOMEM;
}

<<<<<<< HEAD
static bool _sde_splash_lk_check(struct sde_hw_intr *intr)
{
	return (SDE_LK_RUNNING_VALUE == SDE_REG_READ(&intr->hw,
			SCRATCH_REGISTER_1)) ? true : false;
=======
static bool _sde_splash_lk_check(void)
{
	return get_early_service_status(EARLY_DISPLAY);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
}

/**
 * _sde_splash_notify_lk_stop_splash.
 *
 * Function to stop early splash in LK.
 */
<<<<<<< HEAD
static inline void _sde_splash_notify_lk_stop_splash(struct sde_hw_intr *intr)
{
	/* write splash stop signal to scratch register*/
	SDE_REG_WRITE(&intr->hw, SCRATCH_REGISTER_1, SDE_LK_STOP_SPLASH_VALUE);
=======
static inline void _sde_splash_notify_lk_stop_splash(void)
{
	int i = 0;
	int32_t *scratch_pad = NULL;

	/* request Lk to stop splash */
	request_early_service_shutdown(EARLY_DISPLAY);

	/*
	 * Before next proceeding, kernel needs to check bootloader's
	 * intermediate status to ensure LK's concurrent flush is done.
	 */
	while (i++ < SDE_LK_KERNEL_SPLASH_TALK_LOOP) {

		scratch_pad =
			(int32_t *)get_service_shared_mem_start(EARLY_DISPLAY);

		if (scratch_pad) {
			if ((*scratch_pad != SDE_LK_INTERMEDIATE_STOP) &&
				(_sde_splash_lk_check())) {
				DRM_INFO("wait for LK's intermediate ack\n");
				msleep(20);
			} else {
				SDE_DEBUG("received LK intermediate ack\n");
				break;
			}
		}
	}

	if (i == SDE_LK_KERNEL_SPLASH_TALK_LOOP)
		SDE_ERROR("Loop talk for LK and Kernel failed\n");
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
}

static int _sde_splash_gem_new(struct drm_device *dev,
				struct sde_splash_info *sinfo)
{
	int i, ret;

	for (i = 0; i < sinfo->splash_mem_num; i++) {
		sinfo->obj[i] = msm_gem_new(dev,
				sinfo->splash_mem_size[i], MSM_BO_UNCACHED);

		if (IS_ERR(sinfo->obj[i])) {
			ret = PTR_ERR(sinfo->obj[i]);
			SDE_ERROR("failed to allocate gem, ret=%d\n", ret);
			goto error;
		}
	}

	return 0;

error:
	for (i = 0; i < sinfo->splash_mem_num; i++) {
		if (sinfo->obj[i])
			msm_gem_free_object(sinfo->obj[i]);
		sinfo->obj[i] = NULL;
	}

	return ret;
}

static int _sde_splash_get_pages(struct drm_gem_object *obj, phys_addr_t phys)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct page **p;
	dma_addr_t paddr;
	int npages = obj->size >> PAGE_SHIFT;
	int i;

	p = drm_malloc_ab(npages, sizeof(struct page *));
	if (!p)
		return -ENOMEM;

	paddr = phys;

	for (i = 0; i < npages; i++) {
		p[i] = phys_to_page(paddr);
		paddr += PAGE_SIZE;
	}

	msm_obj->sgt = drm_prime_pages_to_sg(p, npages);
	if (IS_ERR(msm_obj->sgt)) {
		SDE_ERROR("failed to allocate sgt\n");
		return -ENOMEM;
	}

	msm_obj->pages = p;

	return 0;
}

static void _sde_splash_destroy_gem_object(struct msm_gem_object *msm_obj)
{
	if (msm_obj->pages) {
		sg_free_table(msm_obj->sgt);
		kfree(msm_obj->sgt);
		drm_free_large(msm_obj->pages);
		msm_obj->pages = NULL;
	}
}

static void _sde_splash_destroy_splash_node(struct sde_splash_info *sinfo)
{
	kfree(sinfo->splash_mem_paddr);
	sinfo->splash_mem_paddr = NULL;

	kfree(sinfo->splash_mem_size);
	sinfo->splash_mem_size = NULL;
}

static void _sde_splash_update_display_splash_status(struct sde_kms *sde_kms)
{
	struct dsi_display *dsi_display;
	struct sde_hdmi *sde_hdmi;
	int i = 0;

	for (i = 0; i < sde_kms->dsi_display_count; i++) {
		dsi_display = (struct dsi_display *)sde_kms->dsi_displays[i];

		dsi_display->cont_splash_enabled = false;
	}

	for (i = 0; i < sde_kms->hdmi_display_count; i++) {
		sde_hdmi = (struct sde_hdmi *)sde_kms->hdmi_displays[i];

		sde_hdmi->cont_splash_enabled = false;
	}
}

static void _sde_splash_sent_pipe_update_uevent(struct sde_kms *sde_kms)
{
	char *event_string;
	char *envp[2];
	struct drm_device *dev;
	struct device *kdev;
	int i =  0;

	if (!sde_kms || !sde_kms->dev) {
		DRM_ERROR("invalid input\n");
		return;
	}

	dev = sde_kms->dev;
	kdev = dev->primary->kdev;

	event_string = kzalloc(SZ_4K, GFP_KERNEL);
	if (!event_string) {
		SDE_ERROR("failed to allocate event string\n");
		return;
	}

	for (i = 0; i < MAX_BLOCKS; i++) {
<<<<<<< HEAD
		if (sde_kms->splash_info.reserved_pipe_info[i] != 0xFFFFFFFF)
			snprintf(event_string, SZ_4K, "pipe%d avialable",
				sde_kms->splash_info.reserved_pipe_info[i]);
=======
		if (sde_kms->splash_info.reserved_pipe_info[i].pipe_id !=
								0xFFFFFFFF)
			snprintf(event_string, SZ_4K, "pipe%d avialable",
			sde_kms->splash_info.reserved_pipe_info[i].pipe_id);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	}

	DRM_INFO("generating pipe update event[%s]", event_string);

	envp[0] = event_string;
	envp[1] = NULL;

	kobject_uevent_env(&kdev->kobj, KOBJ_CHANGE, envp);

	kfree(event_string);
}

static void _sde_splash_get_connector_ref_cnt(struct sde_splash_info *sinfo,
					u32 *hdmi_cnt, u32 *dsi_cnt)
{
	mutex_lock(&sde_splash_lock);
	*hdmi_cnt = sinfo->hdmi_connector_cnt;
	*dsi_cnt = sinfo->dsi_connector_cnt;
	mutex_unlock(&sde_splash_lock);
}

static int _sde_splash_free_module_resource(struct msm_mmu *mmu,
				struct sde_splash_info *sinfo)
{
	int i = 0;
	struct msm_gem_object *msm_obj;

	for (i = 0; i < sinfo->splash_mem_num; i++) {
		msm_obj = to_msm_bo(sinfo->obj[i]);

		if (!msm_obj)
			return -EINVAL;

<<<<<<< HEAD
		if (mmu->funcs && mmu->funcs->unmap)
=======
		if (mmu->funcs && mmu->funcs->early_splash_unmap)
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
			mmu->funcs->early_splash_unmap(mmu,
				sinfo->splash_mem_paddr[i], msm_obj->sgt);

		_sde_splash_free_bootup_memory_to_system(
						sinfo->splash_mem_paddr[i],
						sinfo->splash_mem_size[i]);

		_sde_splash_destroy_gem_object(msm_obj);
	}

	return 0;
}

static bool _sde_splash_validate_commit(struct sde_kms *sde_kms,
					struct drm_atomic_state *state)
{
	int i, nplanes;
	struct drm_plane *plane;
	struct drm_device *dev = sde_kms->dev;

	nplanes = dev->mode_config.num_total_plane;

	for (i = 0; i < nplanes; i++) {
		plane = state->planes[i];

		/*
		 * As plane state has been swapped, we need to check
		 * fb in state->planes, not fb in state->plane_state.
		 */
		if (plane && plane->fb)
			return true;
	}

	return false;
}

<<<<<<< HEAD
=======
static void _sde_splash_update_property(struct sde_kms *sde_kms)
{
	struct drm_device *dev = sde_kms->dev;
	struct drm_crtc *crtc;
	struct drm_plane *plane;
	struct sde_mdss_cfg *catalog = sde_kms->catalog;

	/*
	 * Update plane availability property
	 * after splash handoff is done.
	 */
	drm_for_each_plane(plane, dev) {
		sde_plane_update_blob_property(plane,
					"plane_unavailability=", 0);
	}

	/* update crtc blend stage property */
	drm_for_each_crtc(crtc, dev)
		sde_crtc_update_blob_property(crtc, "max_blendstages=",
					catalog->max_mixer_blendstages);
}

static void
_sde_splash_release_early_splash_layer(struct sde_splash_info *splash_info)
{
	int i = 0;
	uint32_t index;

	for (i = 0; i < MAX_BLOCKS; i++) {
		if (splash_info->reserved_pipe_info[i].early_release) {
			index = _sde_splash_get_pipe_arrary_index(
				splash_info->reserved_pipe_info[i].pipe_id);
			if (index < MAX_BLOCKS) {
				/*
				 * Clear flush bits, mixer mask and extension
				 * mask of released pipes.
				 */
				splash_info->flush_bits &=
					~splash_pipe_cap[index].flush_bit;
				splash_info->mixer_mask &=
					~splash_pipe_cap[index].mixer_mask;
				splash_info->mixer_ext_mask &=
					~splash_pipe_cap[index].mixer_ext_mask;
			}

			splash_info->reserved_pipe_info[i].pipe_id =
								0xFFFFFFFF;
			splash_info->reserved_pipe_info[i].early_release =
								false;
		}
	}
}

static bool _sde_splash_check_splash(int connector_type,
				void *display,
				bool connector_is_shared)
{
	struct dsi_display *dsi_display;
	struct sde_hdmi *sde_hdmi;
	struct shd_display *shd_display;
	bool splash_on = false;

	switch (connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		if (connector_is_shared) {
			shd_display = (struct shd_display *)display;
			splash_on = shd_display->cont_splash_enabled;
		} else {
			sde_hdmi = (struct sde_hdmi *)display;
			splash_on = sde_hdmi->cont_splash_enabled;
		}
		break;
	case DRM_MODE_CONNECTOR_DSI:
		if (connector_is_shared) {
			shd_display = (struct shd_display *)display;
			splash_on = shd_display->cont_splash_enabled;
		} else {
			dsi_display = (struct dsi_display *)display;
			splash_on = dsi_display->cont_splash_enabled;
		}
		break;
	default:
		SDE_ERROR("%s:invalid connector_type %d\n",
		__func__, connector_type);
	}

	return splash_on;
}

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
__ref int sde_splash_init(struct sde_power_handle *phandle, struct msm_kms *kms)
{
	struct sde_kms *sde_kms;
	struct sde_splash_info *sinfo;
	int ret = 0;
	int i = 0;

	if (!phandle || !kms) {
		SDE_ERROR("invalid phandle/kms\n");
		return -EINVAL;
	}

	sde_kms = to_sde_kms(kms);
	sinfo = &sde_kms->splash_info;

	sinfo->dsi_connector_cnt = 0;
	sinfo->hdmi_connector_cnt = 0;

	/* Vote data bus after splash is enabled in bootloader */
	sde_power_data_bus_bandwidth_ctrl(phandle,
		sde_kms->core_client, true);

	for (i = 0; i < sinfo->splash_mem_num; i++) {
		if (!memblock_is_reserved(sinfo->splash_mem_paddr[i])) {
			SDE_ERROR("LK's splash memory is not reserved\n");

			/* withdraw the vote when failed. */
			sde_power_data_bus_bandwidth_ctrl(phandle,
					sde_kms->core_client, false);

			return -EINVAL;
		}
	}

	ret = sde_rm_read_resource_for_splash(&sde_kms->rm,
					(void *)sinfo, sde_kms->catalog);

	return ret;
}

void sde_splash_destroy(struct sde_splash_info *sinfo,
			struct sde_power_handle *phandle,
			struct sde_power_client *pclient)
{
	struct msm_gem_object *msm_obj;
	int i = 0;

	if (!sinfo || !phandle || !pclient) {
		SDE_ERROR("invalid sde_kms/phandle/pclient\n");
		return;
	}

	for (i = 0; i < sinfo->splash_mem_num; i++) {
		msm_obj = to_msm_bo(sinfo->obj[i]);

		if (msm_obj)
			_sde_splash_destroy_gem_object(msm_obj);
	}

	sde_power_data_bus_bandwidth_ctrl(phandle, pclient, false);

	_sde_splash_destroy_splash_node(sinfo);
}

/*
 * sde_splash_parse_memory_dt.
 * In the function, it will parse and reserve two kinds of memory node.
 * First is to get the reserved memory for display buffers.
 * Second is to get the memory node which LK's heap memory is running on.
 */
int sde_splash_parse_memory_dt(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct sde_kms *sde_kms;
	struct sde_splash_info *sinfo;

	if (!priv || !priv->kms) {
		SDE_ERROR("Invalid kms\n");
		return -EINVAL;
	}

	sde_kms = to_sde_kms(priv->kms);
	sinfo = &sde_kms->splash_info;

	if (_sde_splash_parse_dt_get_display_node(dev, sinfo)) {
		SDE_ERROR("get display node failed\n");
		return -EINVAL;
	}
<<<<<<< HEAD

	if (_sde_splash_parse_dt_get_lk_pool_node(dev, sinfo)) {
		SDE_ERROR("get LK pool node failed\n");
		return -EINVAL;
	}

=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	return 0;
}

static inline u32 _sde_splash_parse_sspp_id(struct sde_mdss_cfg *cfg,
					const char *name)
{
	int i;

	for (i = 0; i < cfg->sspp_count; i++) {
		if (!strcmp(cfg->sspp[i].name, name))
			return cfg->sspp[i].id;
	}

	return 0;
}

<<<<<<< HEAD
int sde_splash_parse_reserved_plane_dt(struct sde_splash_info *splash_info,
=======
int sde_splash_parse_reserved_plane_dt(struct drm_device *dev,
				struct sde_splash_info *splash_info,
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
				struct sde_mdss_cfg *cfg)
{
	struct device_node *parent, *node;
	struct property *prop;
	const char *cname;
	int ret = 0, i = 0;
<<<<<<< HEAD
=======
	uint32_t index;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	if (!splash_info || !cfg)
		return -EINVAL;

<<<<<<< HEAD
	parent = of_find_node_by_path("/qcom,sde-reserved-plane");
	if (!parent)
		return -EINVAL;

	for (i = 0; i < MAX_BLOCKS; i++)
		splash_info->reserved_pipe_info[i] = 0xFFFFFFFF;
=======
	parent = of_get_child_by_name(dev->dev->of_node,
			"qcom,sde-reserved-plane");
	if (!parent)
		return -EINVAL;

	for (i = 0; i < MAX_BLOCKS; i++) {
		splash_info->reserved_pipe_info[i].pipe_id = 0xFFFFFFFF;
		splash_info->reserved_pipe_info[i].early_release = false;
	}

	/* Reset flush bits and mixer mask of reserved planes */
	splash_info->flush_bits = 0;
	splash_info->mixer_mask = 0;
	splash_info->mixer_ext_mask = 0;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218

	i = 0;
	for_each_child_of_node(parent, node) {
		if (i >= MAX_BLOCKS) {
			SDE_ERROR("num of nodes(%d) is bigger than max(%d)\n",
				i, MAX_BLOCKS);
			ret = -EINVAL;
			goto parent_node_err;
		}

		of_property_for_each_string(node, "qcom,plane-name",
					prop, cname)
<<<<<<< HEAD
		splash_info->reserved_pipe_info[i] =
					_sde_splash_parse_sspp_id(cfg, cname);
=======
			splash_info->reserved_pipe_info[i].pipe_id =
					_sde_splash_parse_sspp_id(cfg, cname);

		splash_info->reserved_pipe_info[i].early_release =
			of_property_read_bool(node, "qcom,pipe-early-release");

		index = _sde_splash_get_pipe_arrary_index(
				splash_info->reserved_pipe_info[i].pipe_id);

		if (index < MAX_BLOCKS) {
			splash_info->flush_bits |=
					splash_pipe_cap[index].flush_bit;
			splash_info->mixer_mask |=
					splash_pipe_cap[index].mixer_mask;
			splash_info->mixer_ext_mask |=
					splash_pipe_cap[index].mixer_ext_mask;
		}

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		i++;
	}

parent_node_err:
	of_node_put(parent);

	return ret;
}

bool sde_splash_query_plane_is_reserved(struct sde_splash_info *sinfo,
					uint32_t pipe)
{
	int i = 0;

	if (!sinfo)
		return false;

	/* early return if no splash is enabled */
	if (!sinfo->handoff)
		return false;

	for (i = 0; i < MAX_BLOCKS; i++) {
<<<<<<< HEAD
		if (sinfo->reserved_pipe_info[i] == pipe)
=======
		if (!sinfo->reserved_pipe_info[i].early_release &&
			(sinfo->reserved_pipe_info[i].pipe_id == pipe))
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
			return true;
	}

	return false;
}

int sde_splash_get_handoff_status(struct msm_kms *kms)
{
	uint32_t intf_sel = 0;
	uint32_t split_display = 0;
	uint32_t num_of_display_on = 0;
	uint32_t i = 0;
	struct sde_kms *sde_kms = to_sde_kms(kms);
	struct sde_rm *rm;
	struct sde_hw_blk_reg_map *c;
	struct sde_splash_info *sinfo;
	struct sde_mdss_cfg *catalog;

	sinfo = &sde_kms->splash_info;
	if (!sinfo) {
		SDE_ERROR("%s(%d): invalid splash info\n",
				__func__, __LINE__);
		return -EINVAL;
	}

	rm = &sde_kms->rm;

	if (!rm || !rm->hw_mdp) {
		SDE_ERROR("invalid rm.\n");
		return -EINVAL;
	}

	c = &rm->hw_mdp->hw;
	if (c) {
		intf_sel = SDE_REG_READ(c, DISP_INTF_SEL);
		split_display = SDE_REG_READ(c, SPLIT_DISPLAY_EN);
	}

	catalog = sde_kms->catalog;

	if (intf_sel != 0) {
		for (i = 0; i < catalog->intf_count; i++)
			if ((intf_sel >> i*8) & 0x000000FF)
				num_of_display_on++;

		/*
		 * For split display enabled - DSI0, DSI1 interfaces are
		 * considered as single display. So decrement
		 * 'num_of_display_on' by 1
		 */
		if (split_display) {
			num_of_display_on--;
			sinfo->split_is_enabled = true;
		}
	}

	if (num_of_display_on) {
		sinfo->handoff = true;
		sinfo->display_splash_enabled = true;
		sinfo->lk_is_exited = false;
		sinfo->intf_sel_status = intf_sel;
	} else {
		sinfo->handoff = false;
		sinfo->display_splash_enabled = false;
		sinfo->lk_is_exited = true;
	}

	return 0;
}

int sde_splash_smmu_map(struct drm_device *dev, struct msm_mmu *mmu,
				struct sde_splash_info *sinfo)
{
	struct msm_gem_object *msm_obj;
	int i = 0, ret = 0;

	if (!mmu || !sinfo)
		return -EINVAL;

	/* first is to construct drm_gem_objects for splash memory */
	if (_sde_splash_gem_new(dev, sinfo))
		return -ENOMEM;

	/* second is to contruct sgt table for calling smmu map */
	for (i = 0; i < sinfo->splash_mem_num; i++) {
		if (_sde_splash_get_pages(sinfo->obj[i],
				sinfo->splash_mem_paddr[i]))
			return -ENOMEM;
	}

	for (i = 0; i < sinfo->splash_mem_num; i++) {
		msm_obj = to_msm_bo(sinfo->obj[i]);

<<<<<<< HEAD
		if (mmu->funcs && mmu->funcs->map) {
=======
		if (mmu->funcs && mmu->funcs->early_splash_map) {
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
			ret = mmu->funcs->early_splash_map(mmu,
				sinfo->splash_mem_paddr[i], msm_obj->sgt,
				IOMMU_READ | IOMMU_NOEXEC);

			if (!ret) {
				SDE_ERROR("Map blk %d @%pK failed.\n",
					i, (void *)sinfo->splash_mem_paddr[i]);
				return ret;
			}
		}
	}

	return ret ? 0 : -ENOMEM;
}

static bool _sde_splash_get_panel_intf_status(struct sde_splash_info *sinfo,
			const char *display_name, int connector_type)
{
	bool ret = false;
	int intf_status = 0;

	if (sinfo && sinfo->handoff) {
		if (connector_type == DRM_MODE_CONNECTOR_DSI) {
			if (!strcmp(display_name, "dsi_adv_7533_1")) {
				if (sinfo->intf_sel_status & INTF_DSI0_SEL)
					ret = true;
			} else if (!strcmp(display_name, "dsi_adv_7533_2")) {
				if (sinfo->intf_sel_status & INTF_DSI1_SEL)
					ret = true;
			} else
				DRM_INFO("wrong display name %s\n",
						display_name);
		} else if (connector_type == DRM_MODE_CONNECTOR_HDMIA) {
			intf_status = sinfo->intf_sel_status & INTF_HDMI_SEL;
				ret = (intf_status == INTF_HDMI_SEL);
		}
	}

	return ret;
}

int sde_splash_setup_display_resource(struct sde_splash_info *sinfo,
<<<<<<< HEAD
					void *disp, int connector_type)
{
=======
					void *disp, int connector_type,
					bool display_is_shared)
{
	struct dsi_display *dsi_display;
	struct sde_hdmi *sde_hdmi;
	struct shd_display *shd_display;
	bool splash_is_on;

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	if (!sinfo || !disp)
		return -EINVAL;

	/* early return if splash is not enabled in bootloader */
	if (!sinfo->handoff)
		return 0;

	if (connector_type == DRM_MODE_CONNECTOR_DSI) {
<<<<<<< HEAD
		struct dsi_display *display = (struct dsi_display *)disp;

		display->cont_splash_enabled =
			_sde_splash_get_panel_intf_status(sinfo,
					display->name,
					connector_type);

		DRM_INFO("DSI splash %s\n",
		display->cont_splash_enabled ? "enabled" : "disabled");

		if (display->cont_splash_enabled) {
			if (dsi_dsiplay_setup_splash_resource(display))
				return -EINVAL;
		}
	} else if (connector_type == DRM_MODE_CONNECTOR_HDMIA) {
		struct sde_hdmi *sde_hdmi = (struct sde_hdmi *)disp;

		sde_hdmi->cont_splash_enabled =
			_sde_splash_get_panel_intf_status(sinfo,
					NULL, connector_type);

		DRM_INFO("HDMI splash %s\n",
		sde_hdmi->cont_splash_enabled ? "enabled" : "disabled");
=======
		if (display_is_shared) {
			shd_display = (struct shd_display *)disp;
			shd_display->cont_splash_enabled =
				_sde_splash_get_panel_intf_status(sinfo,
					shd_display->name, connector_type);
			splash_is_on = shd_display->cont_splash_enabled;
		} else {
			dsi_display = (struct dsi_display *)disp;
			dsi_display->cont_splash_enabled =
				_sde_splash_get_panel_intf_status(sinfo,
					dsi_display->name,
					connector_type);
			splash_is_on = dsi_display->cont_splash_enabled;

			if (dsi_display->cont_splash_enabled) {
				if (dsi_dsiplay_setup_splash_resource(
							dsi_display))
					return -EINVAL;
			}
		}

		DRM_INFO("DSI %s splash %s\n",
			display_is_shared ? "shared" : "normal",
			splash_is_on ? "enabled" : "disabled");
	} else if (connector_type == DRM_MODE_CONNECTOR_HDMIA) {
		if (display_is_shared) {
			shd_display = (struct shd_display *)disp;
			shd_display->cont_splash_enabled =
				_sde_splash_get_panel_intf_status(sinfo,
					NULL, connector_type);
			splash_is_on = shd_display->cont_splash_enabled;
		} else {
			sde_hdmi = (struct sde_hdmi *)disp;
			sde_hdmi->cont_splash_enabled =
				_sde_splash_get_panel_intf_status(sinfo,
					NULL, connector_type);
			splash_is_on = sde_hdmi->cont_splash_enabled;
		}

		DRM_INFO("HDMI %s splash %s\n",
			display_is_shared ? "shared" : "normal",
			splash_is_on ? "enabled" : "disabled");
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	}

	return 0;
}

void sde_splash_setup_connector_count(struct sde_splash_info *sinfo,
<<<<<<< HEAD
					int connector_type)
{
	switch (connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		sinfo->hdmi_connector_cnt++;
		break;
	case DRM_MODE_CONNECTOR_DSI:
		sinfo->dsi_connector_cnt++;
		break;
	default:
		SDE_ERROR("invalid connector_type %d\n", connector_type);
	}
}

=======
					int connector_type,
					void *display,
					bool connector_is_shared)
{
	bool splash_on = false;

	if (!sinfo || !display)
		return;

	splash_on = _sde_splash_check_splash(connector_type,
				display, connector_is_shared);

	switch (connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		if (splash_on)
			sinfo->hdmi_connector_cnt++;
		break;
	case DRM_MODE_CONNECTOR_DSI:
		if (splash_on)
			sinfo->dsi_connector_cnt++;
		break;
	default:
		SDE_ERROR("%s:invalid connector_type %d\n",
			__func__, connector_type);
	}
}

void sde_splash_decrease_connector_cnt(struct drm_device *dev,
			int connector_type, bool splash_on)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct sde_kms *sde_kms;
	struct sde_splash_info *sinfo;

	if (!priv || !priv->kms) {
		SDE_ERROR("Invalid kms\n");
		return;
	}

	sde_kms = to_sde_kms(priv->kms);
	sinfo = &sde_kms->splash_info;

	if (!sinfo->handoff || !splash_on)
		return;

	switch (connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		sinfo->hdmi_connector_cnt--;
		break;
	case DRM_MODE_CONNECTOR_DSI:
		sinfo->dsi_connector_cnt--;
		break;
	default:
		SDE_ERROR("%s: invalid connector_type %d\n",
			__func__, connector_type);
	}
}

void sde_splash_get_mixer_mask(struct sde_splash_info *sinfo,
		bool *splash_on, u32 *mixercfg, u32 *mixercfg_ext)
{
	mutex_lock(&sde_splash_lock);
	*splash_on = sinfo->handoff;
	*mixercfg = sinfo->mixer_mask;
	*mixercfg_ext = sinfo->mixer_ext_mask;
	mutex_unlock(&sde_splash_lock);
}

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
bool sde_splash_get_lk_complete_status(struct msm_kms *kms)
{
	struct sde_kms *sde_kms = to_sde_kms(kms);
	struct sde_hw_intr *intr;

	if (!sde_kms || !sde_kms->hw_intr) {
		SDE_ERROR("invalid kms\n");
		return false;
	}

	intr = sde_kms->hw_intr;

	if (sde_kms->splash_info.handoff &&
		!sde_kms->splash_info.display_splash_enabled &&
<<<<<<< HEAD
		SDE_LK_EXIT_VALUE == SDE_REG_READ(&intr->hw,
					SCRATCH_REGISTER_1)) {
		SDE_DEBUG("LK totoally exits\n");
=======
		!sde_kms->splash_info.early_display_enabled &&
		!_sde_splash_lk_check()) {
		SDE_DEBUG("LK totally exits\n");
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		return true;
	}

	return false;
}

int sde_splash_free_resource(struct msm_kms *kms,
			struct sde_power_handle *phandle,
<<<<<<< HEAD
			int connector_type, void *display)
=======
			int connector_type, void *display,
			bool connector_is_shared)
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
{
	struct sde_kms *sde_kms;
	struct sde_splash_info *sinfo;
	struct msm_mmu *mmu;
<<<<<<< HEAD
	struct dsi_display *dsi_display = display;
	int ret = 0;
	int hdmi_conn_count = 0;
	int dsi_conn_count = 0;
	static const char *last_commit_display_type = "unknown";

	if (!phandle || !kms) {
		SDE_ERROR("invalid phandle/kms.\n");
=======
	struct dsi_display *dsi_display;
	struct sde_hdmi *hdmi_display;
	struct shd_display *shd_display;
	const char *disp_type;
	int ret = 0;
	int hdmi_conn_count = 0;
	int dsi_conn_count = 0;
	static const char *dsi_old_disp_type = "unknown";
	static const char *hdmi_old_disp_type = "unknown";

	if (!phandle || !kms || !display) {
		SDE_ERROR("invalid phandle/kms/display\n");
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		return -EINVAL;
	}

	sde_kms = to_sde_kms(kms);
	sinfo = &sde_kms->splash_info;
	if (!sinfo) {
		SDE_ERROR("%s(%d): invalid splash info\n", __func__, __LINE__);
		return -EINVAL;
	}

<<<<<<< HEAD
	/* Get connector number where the early splash in on. */
=======
	/* Get ref count of connector who has early splash. */
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	_sde_splash_get_connector_ref_cnt(sinfo, &hdmi_conn_count,
						&dsi_conn_count);

	mutex_lock(&sde_splash_lock);
	if (!sinfo->handoff) {
		mutex_unlock(&sde_splash_lock);
		return 0;
	}

	/*
	 * Start to free all LK's resource till user commit happens
	 * on each display which early splash is enabled on.
	 */
	if (hdmi_conn_count == 0 && dsi_conn_count == 0) {
		mmu = sde_kms->aspace[0]->mmu;
		if (!mmu) {
			mutex_unlock(&sde_splash_lock);
			return -EINVAL;
		}

		/* free HDMI's, DSI's and early camera's reserved memory */
		_sde_splash_free_module_resource(mmu, sinfo);

		_sde_splash_destroy_splash_node(sinfo);

<<<<<<< HEAD
		/* free lk_pool heap memory */
		_sde_splash_free_bootup_memory_to_system(sinfo->lk_pool_paddr,
						sinfo->lk_pool_size);

=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		/* withdraw data bus vote */
		sde_power_data_bus_bandwidth_ctrl(phandle,
					sde_kms->core_client, false);

		/*
		 * Turn off MDP core power to keep power on/off operations
		 * be matched, as MDP core power is enabled already when
		 * early splash is enabled.
		 */
		sde_power_resource_enable(phandle,
					sde_kms->core_client, false);

<<<<<<< HEAD
=======
		/* update impacted crtc and plane property by splash */
		_sde_splash_update_property(sde_kms);

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		/* send uevent to notify user to recycle resource */
		_sde_splash_sent_pipe_update_uevent(sde_kms);

		/* set display's splash status to false after handoff is done */
		_sde_splash_update_display_splash_status(sde_kms);

<<<<<<< HEAD
=======
		/* Reset flush_bits and mixer mask */
		sinfo->flush_bits = 0;
		sinfo->mixer_mask = 0;
		sinfo->mixer_ext_mask = 0;

>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		/* Finally mark handoff flag to false to say
		 * handoff is complete.
		 */
		sinfo->handoff = false;

		DRM_INFO("HDMI and DSI resource handoff is completed\n");
		mutex_unlock(&sde_splash_lock);
		return 0;
	}

	/*
	 * Ensure user commit happens on different connectors
	 * who has splash.
	 */
	switch (connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
<<<<<<< HEAD
		if (sinfo->hdmi_connector_cnt == 1)
			sinfo->hdmi_connector_cnt--;
		break;
	case DRM_MODE_CONNECTOR_DSI:
		if (strcmp(dsi_display->display_type, "unknown") &&
			strcmp(last_commit_display_type,
				dsi_display->display_type)) {
			if (sinfo->dsi_connector_cnt >= 1)
				sinfo->dsi_connector_cnt--;

			last_commit_display_type = dsi_display->display_type;
=======
		if (connector_is_shared) {
			shd_display = (struct shd_display *)display;
			disp_type = shd_display->display_type;
		} else {
			hdmi_display = (struct sde_hdmi *)display;
			disp_type = hdmi_display->display_type;
		}

		if (strcmp(disp_type, "unknown") &&
			strcmp(hdmi_old_disp_type, disp_type)) {
			if (sinfo->hdmi_connector_cnt >= 1)
				sinfo->hdmi_connector_cnt--;

			hdmi_old_disp_type = disp_type;
		}
		break;
	case DRM_MODE_CONNECTOR_DSI:
		if (connector_is_shared) {
			shd_display = (struct shd_display *)display;
			disp_type = shd_display->display_type;
		} else {
			dsi_display = (struct dsi_display *)display;
			disp_type = dsi_display->display_type;
		}

		if (strcmp(disp_type, "unknown") &&
			strcmp(dsi_old_disp_type, disp_type)) {
			if (sinfo->dsi_connector_cnt >= 1)
				sinfo->dsi_connector_cnt--;

			dsi_old_disp_type = disp_type;
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		}
		break;
	default:
		ret = -EINVAL;
		SDE_ERROR("%s: invalid connector_type %d\n",
					__func__, connector_type);
	}

	mutex_unlock(&sde_splash_lock);
	return ret;
}

/*
 * Below function will detach all the pipes of the mixer
 */
static int _sde_splash_clear_mixer_blendstage(struct msm_kms *kms,
				struct drm_atomic_state *state)
{
	struct drm_crtc *crtc;
	struct sde_crtc *sde_crtc;
	struct sde_crtc_mixer *mixer;
	int i;
	struct sde_splash_info *sinfo;
	struct sde_kms *sde_kms = to_sde_kms(kms);

	sinfo = &sde_kms->splash_info;

	if (!sinfo) {
		SDE_ERROR("%s(%d): invalid splash info\n", __func__, __LINE__);
		return -EINVAL;
	}

	for (i = 0; i < state->dev->mode_config.num_crtc; i++) {
		crtc = state->crtcs[i];
		if (!crtc) {
			SDE_ERROR("CRTC is NULL");
			continue;
		}
		sde_crtc = to_sde_crtc(crtc);
		if (!sde_crtc) {
			SDE_ERROR("SDE CRTC is NULL");
			return -EINVAL;
		}
		mixer = sde_crtc->mixers;
		if (!mixer) {
			SDE_ERROR("Mixer is NULL");
			return -EINVAL;
		}
		for (i = 0; i < sde_crtc->num_mixers; i++) {
			if (mixer[i].hw_ctl->ops.clear_all_blendstages)
				mixer[i].hw_ctl->ops.clear_all_blendstages(
						mixer[i].hw_ctl,
						sinfo->handoff,
<<<<<<< HEAD
						sinfo->reserved_pipe_info,
						MAX_BLOCKS);
=======
						sinfo->mixer_mask,
						sinfo->mixer_ext_mask);
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
		}
	}
	return 0;
}

/*
 * Below function will notify LK to stop display splash.
 */
int sde_splash_lk_stop_splash(struct msm_kms *kms,
				struct drm_atomic_state *state)
{
	int error = 0;
	struct sde_splash_info *sinfo;
	struct sde_kms *sde_kms = to_sde_kms(kms);

	sinfo = &sde_kms->splash_info;

<<<<<<< HEAD
	if (!sinfo) {
		SDE_ERROR("%s(%d): invalid splash info\n", __func__, __LINE__);
		return -EINVAL;
	}

=======
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	/* Monitor LK's status and tell it to exit. */
	mutex_lock(&sde_splash_lock);
	if (_sde_splash_validate_commit(sde_kms, state) &&
			sinfo->display_splash_enabled) {
<<<<<<< HEAD
		if (_sde_splash_lk_check(sde_kms->hw_intr))
			_sde_splash_notify_lk_stop_splash(sde_kms->hw_intr);

		sinfo->display_splash_enabled = false;

		error = _sde_splash_clear_mixer_blendstage(kms, state);
=======
		/* release splash RGB layer */
		_sde_splash_release_early_splash_layer(sinfo);

		if (_sde_splash_lk_check()) {
			_sde_splash_notify_lk_stop_splash();
			error = _sde_splash_clear_mixer_blendstage(kms, state);
		}

		if (get_hibernation_status() == true) {
			sinfo->display_splash_enabled = false;
		} else {
			/* preserve the display_splash_enabled state for
			 * case when system is restoring from hibernation
			 * image and splash is enabled.
			 */
			sinfo->display_splash_enabled = true;
		}
>>>>>>> f18bfabb5e9ca3c4033c0de4dd4fd4c94a97c218
	}
	mutex_unlock(&sde_splash_lock);

	return error;
}
