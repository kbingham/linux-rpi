// SPDX-License-Identifier: GPL-2.0

#include <drm/drm_atomic_state_helper.h>
#include <drm/drm_atomic_uapi.h>
#include <drm/drm_fourcc.h>
#include <drm/drm_framebuffer.h>
#include <drm/drm_mode.h>
#include <drm/drm_modeset_helper_vtables.h>
#include <drm/drm_plane.h>

#include "../../drm_crtc_internal.h"

#include <kunit/test.h>

#include "vc4_mock.h"

int vc4_plane_atomic_check(struct drm_plane *plane,
			   struct drm_atomic_state *state);

static const struct drm_plane_helper_funcs vc4_dummy_plane_helper_funcs = {
	.atomic_check = vc4_plane_atomic_check,
};

void vc4_plane_reset(struct drm_plane *plane);
void vc4_plane_destroy_state(struct drm_plane *plane,
			     struct drm_plane_state *state);
struct drm_plane_state *vc4_plane_duplicate_state(struct drm_plane *plane);

static const struct drm_plane_funcs vc4_dummy_plane_funcs = {
	.atomic_destroy_state	= vc4_plane_destroy_state,
	.atomic_duplicate_state	= vc4_plane_duplicate_state,
	.reset			= vc4_plane_reset,
};

static const uint32_t vc4_dummy_plane_formats[] = {
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
};

struct vc4_dummy_plane *vc4_dummy_plane(struct kunit *test,
					struct drm_device *drm,
					enum drm_plane_type type)
{
	struct vc4_dummy_plane *dummy_plane;
	struct drm_plane *plane;

	dummy_plane = drmm_universal_plane_alloc(drm,
						 struct vc4_dummy_plane, plane.base,
						 0,
						 &vc4_dummy_plane_funcs,
						 vc4_dummy_plane_formats,
						 ARRAY_SIZE(vc4_dummy_plane_formats),
						 NULL,
						 DRM_PLANE_TYPE_PRIMARY,
						 NULL);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, dummy_plane);

	plane = &dummy_plane->plane.base;
	drm_plane_helper_add(plane, &vc4_dummy_plane_helper_funcs);

	return dummy_plane;
}

struct drm_plane *
vc4_mock_atomic_add_plane(struct kunit *test,
			  struct drm_atomic_state *state,
			  struct drm_crtc *crtc)
{
	struct drm_plane_state *plane_state;
	struct drm_plane *plane;
	int ret;

	plane = vc4_mock_find_plane_for_crtc(test, crtc);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, plane);

	plane_state = drm_atomic_get_plane_state(state, plane);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, plane_state);

	ret = drm_atomic_set_crtc_for_plane(plane_state, crtc);
	KUNIT_EXPECT_EQ(test, ret, 0);

	return plane;
}

static struct drm_gem_object *gem;

struct drm_framebuffer *
vc4_mock_atomic_plane_add_fb(struct kunit *test,
			     struct drm_atomic_state *state,
			     struct drm_plane *plane,
			     struct drm_file *file,
			     struct drm_mode_fb_cmd2 *cmd)
{
	const struct drm_format_info *info;
	struct drm_mode_create_dumb dumb_args = { };
	struct drm_mode_fb_cmd fb_req = { };
	struct drm_gem_object *obj;
	struct drm_device *drm = state->dev;
	struct drm_plane_state *plane_state;
	struct drm_framebuffer *fb;
	int ret;

	info = drm_format_info(cmd->pixel_format);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, info);

	dumb_args.width = cmd->width;
	dumb_args.height = cmd->height;
	dumb_args.bpp = drm_format_info_bpp(info, 0);

	ret = drm_mode_create_dumb(drm, &dumb_args, file);
	KUNIT_ASSERT_EQ(test, ret, 0);

	obj = drm_gem_object_lookup(file, dumb_args.handle);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, obj);

	gem = obj;

	fb_req.bpp = drm_format_info_bpp(info, 0);
	fb_req.depth = info->depth;
	fb_req.width = cmd->width;
	fb_req.height = cmd->height;
	fb_req.handle = dumb_args.handle;
	fb_req.pitch = dumb_args.pitch;

	ret = drm_mode_addfb(drm, &fb_req, file);
	KUNIT_ASSERT_EQ(test, ret, 0);

	pr_crit("%s +%d %px\n", __func__, __LINE__, fb_req.fb_id);

	fb = drm_framebuffer_lookup(drm, file, fb_req.fb_id);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, info);

	plane_state = drm_atomic_get_plane_state(state, plane);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, plane_state);

	drm_atomic_set_fb_for_plane(plane_state, fb);

	drm_framebuffer_get(fb);

	return fb;
}

void vc4_mock_atomic_plane_rm_fb(struct kunit *test)
{
	drm_gem_object_put(gem);
	gem = NULL;
}
