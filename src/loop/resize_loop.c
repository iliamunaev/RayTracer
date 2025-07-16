#include "minirt.h"

void	check_redraw(void *param)
{
	t_rt	*world;
	double	now;
	double	elapsed;

	world = (t_rt *)param;
	if (world->needs_resize_render)
	{
		now = mlx_get_time();
		elapsed = now - world->last_resize_time;
		if (elapsed > 0.5)
		{
			rebuild_camera(world);
			render(world);
			world->needs_resize_render = 0;
		}
	}
}

void	resize_screen(int32_t width, int32_t height, void *param)
{
	t_rt	*world;

	world = (t_rt *)param;
	mlx_resize_image(world->scene, width, height);
	world->last_resize_time = mlx_get_time();
	world->needs_resize_render = 1;
}
