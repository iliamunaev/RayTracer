#include "minirt.h"

static inline float	calculate_aspect(void)
{
	return ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);
}

static inline float	calculate_half_width(float aspect, float half_view)
{
	if (aspect >= 1.0f)
		return (half_view);
	else
		return (half_view * aspect);
}

static inline float	calculate_half_height(float aspect, float half_view)
{
	if (aspect >= 1.0f)
		return (half_view / aspect);
	else
		return (half_view);
}

float	get_half_height(t_rt *rt)
{
	float	aspect;
	float	half_view;

	aspect = calculate_aspect();
	half_view = get_half_view(rt);
	return (calculate_half_height(aspect, half_view));
}

float	get_half_width(t_rt *rt)
{
	float	aspect;
	float	half_view;

	aspect = calculate_aspect();
	half_view = get_half_view(rt);
	return (calculate_half_width(aspect, half_view));
}
