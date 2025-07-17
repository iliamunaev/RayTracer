#include "minirt.h"

/**
 * @brief Calculate the aspect ratio of the screen (width / height).
 *
 * @return The screen aspect ratio as a float.
 */
static inline float	calculate_aspect(t_rt *rt)
{
	return ((float)rt->scene->width / (float)rt->scene->height);
}

/**
 * @brief Calculate half of the camera's view width in world units.
 *
 * If the aspect ratio is greater than or equal to 1, the width equals half_view.
 * Otherwise, it scales down by the aspect ratio.
 *
 * @param aspect The screen aspect ratio.
 * @param half_view The tangent of half the field of view.
 * @return Half-width of the view.
 */
static inline float	calculate_half_width(float aspect, float half_view)
{
	if (aspect >= 1.0f)
		return (half_view);
	else
		return (half_view * aspect);
}

/**
 * @brief Calculate half of the camera's view height in world units.
 *
 * If the aspect ratio is greater than or equal to 1, the height scales down.
 * Otherwise, it equals half_view.
 *
 * @param aspect The screen aspect ratio.
 * @param half_view The tangent of half the field of view.
 * @return Half-height of the view.
 */
static inline float	calculate_half_height(float aspect, float half_view)
{
	if (aspect >= 1.0f)
		return (half_view / aspect);
	else
		return (half_view);
}

/**
 * @brief Get the half-height of the view frustum based on screen and FOV.
 *
 * This is derived from the vertical field of view and aspect ratio.
 *
 * @param rt Pointer to the scene or render context.
 * @return Half of the view height in world space.
 */
float	get_half_height(t_rt *rt)
{
	float	aspect;
	float	half_view;

	aspect = calculate_aspect(rt);
	half_view = get_half_view(rt);
	return (calculate_half_height(aspect, half_view));
}

/**
 * @brief Get the half-width of the view frustum based on screen and FOV.
 *
 * This is derived from the horizontal extent of the camera frustum.
 *
 * @param rt Pointer to the scene or render context.
 * @return Half of the view width in world space.
 */
float	get_half_width(t_rt *rt)
{
	float	aspect;
	float	half_view;

	aspect = calculate_aspect(rt);
	half_view = get_half_view(rt);
	return (calculate_half_width(aspect, half_view));
}
