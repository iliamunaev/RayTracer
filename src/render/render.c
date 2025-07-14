#include "minirt.h"

void	ray_for_pixel(t_ray *ray, t_cam *cam, float px, float py)
{
	t_tuple	pixel_point;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	pixel_point.x = cam->half_view - ((px + 0.5f) * cam->pix_size);
	pixel_point.y = cam->half_height - ((py + 0.5f) * cam->pix_size);
	pixel_point.z = -1.0f;
	pixel_point.w = 1.0f;
	mult_matrix_by_tuple(&pixel, cam->matrix, pixel_point);
	create_point(&origin, 0, 0, 0);
	mult_matrix_by_tuple(&origin, cam->matrix, origin);
	sub_tuples(&direction, pixel, origin);
	normalize_vector(&direction);
	ray->origin = origin;
	ray->direction = direction;
}

void	put_pixel(size_t idx, uint8_t *pixels, t_tuple color)
{
	uint32_t	packed_color;

	packed_color = float_to_hex(color);
	pixels[idx + BLUE] = (packed_color >> 24) & 0xFF;
	pixels[idx + GREEN] = (packed_color >> 16) & 0xFF;
	pixels[idx + RED] = (packed_color >> 8) & 0xFF;
	pixels[idx + ALPHA] = packed_color & 0xFF;
}

void	render(t_rt *rt)
{
	uint32_t	x;
	uint32_t	y;
	t_tuple		color;
	t_ray		ray;
	size_t		idx;

	y = 0;
	while (y < rt->scene->height)
	{
		x = 0;
		while (x < rt->scene->width)
		{
			ray_for_pixel(&ray, &rt->cam, x, y);
			color_at(&color, rt, &ray, 6);
			if (ray.is_hit == false)
				create_color(&color, 0, 0, 0);
			idx = (y * rt->scene->width + x) * BPP;
			put_pixel(idx, rt->scene->pixels, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(rt->mlx, rt->scene, 0, 0);
}
