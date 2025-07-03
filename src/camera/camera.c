#include "minirt.h"

static inline bool	is_zero_vector(t_tuple v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

void	rebuild_camera(t_rt *rt)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	create_vector(&up, 0, 1, 0);
	if (is_zero_vector(rt->cam.norm_vector))
	{
		rt->cam.norm_vector = (t_tuple){0, 0, 1, 0};
	}
	from = rt->cam.position;
	to.x = rt->cam.position.x + rt->cam.norm_vector.x;
	to.y = rt->cam.position.y + rt->cam.norm_vector.y;
	to.z = rt->cam.position.z + rt->cam.norm_vector.z;
	to.w = 1.0f;
	transform_cam_view(rt, from, to, up);
	invert_matrix(&rt->cam.inv_matrix, rt->cam.matrix);
	if (rt->cam.fov == 0.0f)
		rt->cam.fov = 70.0f;
	rt->cam.half_view = get_half_view(rt);
	rt->cam.half_height = get_half_height(rt);
	rt->cam.pix_size = get_pixel_size(rt);
}
