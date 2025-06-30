#include "minirt.h"

void	render(t_rt *rt)
{
	int		x;
	int		y;
	t_tuple color;
    t_comps comps;
    t_ray	ray;

	y = 0;	
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
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

// void render(t_rt *rt)
// {
// 	int		x, y;
// 	t_tuple	color;
// 	t_comps comps;
// 	t_ray	ray;
// 	uint32_t width = rt->scene->width;
// 	uint32_t height = rt->scene->height;

// 	uint32_t *pixels = (uint32_t *)rt->scene->pixels;

// 	for (y = 0; y < (int)height; y++)
// 	{
// 		for (x = 0; x < (int)width; x++)
// 		{
// 			ray_for_pixel(&ray, &rt->cam, x, y);
// 			color_at(&comps, &color, rt, &ray);

// 			if (ray.is_hit == true)
// 				pixels[y * width + x] = float_to_hex(color);
// 			else
// 				pixels[y * width + x] = 0x58c0dcFF;
// 		}
// 	}
// }


/*
// test
void render(t_rt *rt)
{
    uint32_t *pixels = (uint32_t *)rt->scene->pixels;
    uint32_t width = rt->scene->width;
    uint32_t height = rt->scene->height;
    for (uint32_t y = 0; y < height; y++)
        for (uint32_t x = 0; x < width; x++)
            pixels[y * width + x] = 0xFF00FFFF; // Cyan, full alpha
}
*/