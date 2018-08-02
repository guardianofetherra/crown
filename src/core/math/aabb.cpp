/*
 * Copyright (c) 2012-2018 Daniele Bartolini and individual contributors.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 */

#include "core/math/aabb.h"

namespace crown
{
namespace aabb
{
	void from_points(AABB& b, u32 num, u32 stride, const void* points)
	{
		const char* pts = (const char*)points;
		const f32* point = (f32*)pts;

		b.min.x = b.max.x = point[0];
		b.min.y = b.max.y = point[1];
		b.min.z = b.max.z = point[2];
		pts += stride;

		for (u32 i = 1; i < num; ++i, pts += stride)
		{
			point = (f32*)pts;

			b.min.x = fmin(b.min.x, point[0]);
			b.min.y = fmin(b.min.y, point[1]);
			b.min.z = fmin(b.min.z, point[2]);
			b.max.x = fmax(b.max.x, point[0]);
			b.max.y = fmax(b.max.y, point[1]);
			b.max.z = fmax(b.max.z, point[2]);
		}
	}

	void from_boxes(AABB& b, u32 num, const AABB* boxes)
	{
		for (u32 i = 0; i < num; ++i)
		{
			const AABB& bi = boxes[i];

			b.min.x = fmin(b.min.x, bi.min.x);
			b.min.y = fmin(b.min.y, bi.min.y);
			b.min.z = fmin(b.min.z, bi.min.z);
			b.max.x = fmax(b.max.x, bi.max.x);
			b.max.y = fmax(b.max.y, bi.max.y);
			b.max.z = fmax(b.max.z, bi.max.z);
		}
	}

} // namespace aabb

} // namespace crown
