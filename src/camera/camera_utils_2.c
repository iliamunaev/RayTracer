#include "minirt.h"

static inline float	calculate_pixel_size(float half_width)
{
	return ((half_width * 2.0f) / SCREEN_WIDTH);
}

float	get_pixel_size(t_rt *rt)
{
	float	half_width;

	half_width = get_half_width(rt);
	return (calculate_pixel_size(half_width));
}

static inline float	get_radians(float degrees)
{
	return (degrees * DEG_TO_RAD);
}

float	get_half_view(t_rt *rt)
{
	float	fov_rad;

	fov_rad = get_radians(rt->cam.fov);
	return (tanf(fov_rad / 2.0f));
}
