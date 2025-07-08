#include "minirt.h"

void	handle_mouse_move(double x, double y, void *param)
{
	t_rt	*world;

	world = (t_rt *)param;
	world->mouse_x = x;
	world->mouse_y = y;
}

static bool	is_left_mouse_click(mouse_key_t button, action_t action)
{
	return (action == MLX_PRESS && button == MLX_MOUSE_BUTTON_LEFT);
}

static void	select_hit_object(t_rt *world, t_ray *ray)
{
	int	i;

	i = 0;
	world->selected_primitive_index = -1;
	while (i < world->obj_counted)
	{
		if (&world->primitives_list[i] == ray->hit.object)
		{
			world->selected_primitive_index = i;
			break ;
		}
		i++;
	}
}

void	handle_mouse_click(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param)
{
	t_rt	*world;
	t_ray	ray;

	world = (t_rt *)param;
	(void)mods;
	if (!is_left_mouse_click(button, action))
		return ;
	ray_for_pixel(&ray, &world->cam, world->mouse_x, world->mouse_y);
	get_ray_intersections(&ray, world);
	get_hit(&ray);
	if (ray.is_hit)
		select_hit_object(world, &ray);
}
