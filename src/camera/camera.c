#include "minirt.h"

/**
 * @brief Check if a vector is a zero vector (all components are zero).
 *
 * @param v The vector to check.
 * @return true if x, y, and z components are all 0; false otherwise.
 */
static inline bool	is_zero_vector(t_tuple v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

/**
 * @brief Recalculate the camera's transformation and view parameters.
 *
 * This function:
 * - Computes the `to` point from camera position and forward vector.
 * - Calls `transform_cam_view()` to build the view transformation matrix.
 * - Inverts the camera matrix for ray generation.
 * - Sets default FOV if not specified.
 * - Computes view parameters like half-view, half-height, and pixel size.
 *
 * Used whenever the camera's position, orientation, or FOV changes.
 *
 * @param rt Pointer to the world context containing the camera.
 */
void	rebuild_camera(t_rt *rt)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	create_vector(&up, 0, 1, 0);
	if (is_zero_vector(rt->cam.norm_vector))
		create_vector(&rt->cam.norm_vector, 0, 1, 0);
	from = rt->cam.position;
	to.x = from.x + rt->cam.norm_vector.x;
	to.y = from.y + rt->cam.norm_vector.y;
	to.z = from.z + rt->cam.norm_vector.z;
	to.w = 1.0f;
	transform_cam_view(rt, from, to, up);
	if (rt->cam.fov == ZERO_CAM_FOV)
		rt->cam.fov = DEFAILT_CAM_FOV;
	rt->cam.half_view = get_half_view(rt);
	rt->cam.half_height = get_half_height(rt);
	rt->cam.pix_size = get_pixel_size(rt);
}
