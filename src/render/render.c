#include "minirt.h"

/* static inline void ray_for_pixel(&ray, &rt->cam, x, y)
static inline void color_at;
 */
//ALL THE VERY HEAVY FUNCTIONS WE COULD PUT AS STATIC INLINE FUNCTIONS TO INCREASE PERFORMANCE
static inline  void ray_for_pixel(t_ray *ray, t_cam *cam, float px, float py)
{
    float xoffset;
    float yoffset;
    float world_x;
    float world_y;
    
    xoffset = (px + 0.5) * cam->pix_size;
    yoffset = (py + 0.5) * cam->pix_size;
    
    world_x = cam->half_view - xoffset;
    world_y = cam->half_height - yoffset;
    
    t_tuple pixel_point = {world_x, world_y, -1.0f, 1.0f,};

    t_tuple pixel;
    mult_matrix_by_tuple(&pixel, cam->matrix, pixel_point);

    t_tuple origin;
    t_tuple point = {0, 0, 0, 1.0f,};    
    mult_matrix_by_tuple(&origin, cam->matrix, point);

    t_tuple direction;
    sub_tuples(&direction, pixel, origin);

    normalize_vector(&direction);

    ray->origin = origin;
    ray->direction = direction;
}

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
}

