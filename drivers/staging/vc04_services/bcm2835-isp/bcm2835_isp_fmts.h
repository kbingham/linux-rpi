/* SPDX-License-Identifier: GPL-2.0 */

#ifndef BCM2835_ISP_FMTS
#define BCM2835_ISP_FMTS

#define V4L2_META_FMT_STATS v4l2_fourcc('S', 'T', 'A', 'T')
#define MMAL_ENCODING_BRCM_STATS MMAL_FOURCC('S', 'T', 'A', 'T')

struct bcm2835_isp_fmt {
	u32 fourcc;
	int depth;
	int bytesperline_align;
	u32 flags;
	u32 mmal_fmt;
	int size_multiplier_x2;
	bool is_bayer;
};

struct bcm2835_isp_fmt_list {
	struct bcm2835_isp_fmt *list;
	unsigned int num_entries;
};

static const struct bcm2835_isp_fmt supported_formats[] = {
	{
		/* YUV formats */
		.fourcc		    = V4L2_PIX_FMT_YUV420,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	     = MMAL_ENCODING_I420,
		.size_multiplier_x2 = 3,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_YVU420,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_YV12,
		.size_multiplier_x2 = 3,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_NV12,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_NV12,
		.size_multiplier_x2 = 3,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_NV21,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_NV21,
		.size_multiplier_x2 = 3,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_RGB565,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_RGB16,
		.size_multiplier_x2 = 2,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_YUYV,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_YUYV,
		.size_multiplier_x2 = 2,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_UYVY,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_UYVY,
		.size_multiplier_x2 = 2,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_YVYU,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_YVYU,
		.size_multiplier_x2 = 2,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_VYUY,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_VYUY,
		.size_multiplier_x2 = 2,
	},
	{
		/* RGB formats */
		.fourcc		    = V4L2_PIX_FMT_RGB24,
		.depth		    = 24,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_RGB24,
		.size_multiplier_x2 = 2,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_BGR24,
		.depth		    = 24,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BGR24,
		.size_multiplier_x2 = 2,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_BGR32,
		.depth		    = 32,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BGRA,
		.size_multiplier_x2 = 2,
	},
	{
		/* Bayer formats */
		/* 8 bit */
		.fourcc		    = V4L2_PIX_FMT_SRGGB8,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SRGGB8,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SBGGR8,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SBGGR8,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGRBG8,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGRBG8,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGBRG8,
		.depth		    = 8,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGBRG8,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		/* 10 bit */
		.fourcc		    = V4L2_PIX_FMT_SRGGB10P,
		.depth		    = 10,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SRGGB10P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SBGGR10P,
		.depth		    = 10,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SBGGR10P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGRBG10P,
		.depth		    = 10,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGRBG10P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGBRG10P,
		.depth		    = 10,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGBRG10P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		/* 12 bit */
		.fourcc		    = V4L2_PIX_FMT_SRGGB12P,
		.depth		    = 12,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SRGGB12P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SBGGR12P,
		.depth		    = 12,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SBGGR12P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGRBG12P,
		.depth		    = 12,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGRBG12P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGBRG12P,
		.depth		    = 12,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGBRG12P,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		/* 16 bit */
		.fourcc		    = V4L2_PIX_FMT_SRGGB16,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SRGGB16,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SBGGR16,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SBGGR16,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGRBG16,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGRBG16,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_PIX_FMT_SGBRG16,
		.depth		    = 16,
		.bytesperline_align = 32,
		.flags		    = 0,
		.mmal_fmt	    = MMAL_ENCODING_BAYER_SGBRG16,
		.size_multiplier_x2 = 2,
		.is_bayer	    = true,
	},
	{
		.fourcc		    = V4L2_META_FMT_STATS,
		.mmal_fmt	    = MMAL_ENCODING_BRCM_STATS,
		/* The rest are not valid fields for stats. */
	}
};

#endif
