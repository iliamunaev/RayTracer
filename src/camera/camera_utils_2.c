#include "minirt.h"

/**
 * @brief Calculate the pixel size in world units.
 *
 * Computes the size of a single pixel by dividing the total view width by
 * the screen width in pixels.
 *
 * @param half_width Half of the view width in world space.
 * @return Size of a single pixel in world units.
 */
static inline float	calculate_pixel_size(float half_width, t_rt *rt)
{
	return ((half_width * 2.0f) / rt->scene->width);
}

/**
 * @brief Get the pixel size in world units for the current camera configuration.
 *
 * Uses the half-width of the camera view to calculate pixel resolution.
 *
 * @param rt Pointer to the scene or rendering context.
 * @return Size of a single pixel in world space.
 */
float	get_pixel_size(t_rt *rt)
{
	float	half_width;

	half_width = get_half_width(rt);
	return (calculate_pixel_size(half_width, rt));
}

/**
 * @brief Convert degrees to radians.
 *
 * Used to convert FOV or angles for trigonometric functions.
 *
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
static inline float	get_radians(float degrees)
{
	return (degrees * DEG_TO_RAD);
}

/**
 * @brief Calculate half of the view frustum's angle (in tangent space).
 *
 * Converts FOV from degrees to radians and returns tan(fov / 2),
 * which is used to compute view width and height.
 *
 * @param rt Pointer to the scene or rendering context.
 * @return The tangent of half the FOV in radians.
 */
float	get_half_view(t_rt *rt)
{
	float	fov_rad;

	fov_rad = get_radians(rt->cam.fov);
	return (tanf(fov_rad / 2.0f));
}
