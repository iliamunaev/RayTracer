#include "minirt.h"



void render(t_rt *rt)
{
    int			x;
    int			y;
    t_tuple		color;
    t_comps		comps;
    t_ray		ray;
    uint8_t		*pixels;
    uint32_t	packed_color;
    size_t		idx;

	pixels = rt->scene->pixels;
    y = 0;
    while (y < rt->scene->height)
    {
        x = 0;
        while (x < rt->scene->width)
        {
            ray_for_pixel(&ray, &rt->cam, x, y);
            color_at(&comps, &color, rt, &ray);

            if (ray.is_hit == true)
                packed_color = float_to_hex(color);
            else
                packed_color = 0x58c0dc;

            idx = (y * rt->scene->width + x) * BPP;
			pixels[idx + BLUE] = (packed_color >>  24) & 0xFF;
			pixels[idx + GREEN] = (packed_color >> 16) & 0xFF;
			pixels[idx + RED] = (packed_color >> 8) & 0xFF;
			pixels[idx + ALPHA] =  packed_color        & 0xFF;
            x++;
        }
        y++;
    }
    mlx_image_to_window(rt->mlx, rt->scene, 0, 0);
	fprintf(stderr, "\n********SUCCESS mlx_new_image()**********\n\n");
}

