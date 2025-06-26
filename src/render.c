#include "minirt.h"

void	render(t_rt *rt)
{
	int		x;
	int		y;
	t_tuple color;
    t_comps comps;
    t_ray	ray;

	y = 0;	
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (x < SCREEN_HEIGHT)
		{
			ray_for_pixel(&ray, &rt->cam, x, y);			
			color_at(&comps, &color, rt, &ray);			
			if (ray.is_hit == true)
				mlx_put_pixel(rt->scene, x, y, float_to_hex(color));
			else
				mlx_put_pixel(rt->scene, x, y, 0x58c0dc);
			x++;
		}
		y++;
	}
}