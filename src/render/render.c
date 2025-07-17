#include "minirt.h"

/**
 * @brief Constructs a ray that originates from the camera and 
 * passes through a pixel.
 *
 * Transforms the pixel coordinates into world space and calculates
 * the direction vector from the camera origin to the pixel location.
 *
 * @param ray Pointer to the resulting ray.
 * @param cam Pointer to the camera.
 * @param px X coordinate of the pixel.
 * @param py Y coordinate of the pixel.
 */
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
	mult_matrix_by_tuple(&pixel, cam->inv_matrix, pixel_point);
	create_point(&origin, 0, 0, 0);
	mult_matrix_by_tuple(&origin, cam->inv_matrix, origin);
	sub_tuples(&direction, pixel, origin);
	normalize_vector(&direction);
	ray->origin = origin;
	ray->direction = direction;
}

/**
 * @brief Converts a color to 32-bit packed format and stores it in 
 * the pixel buffer.
 *
 * Assumes the color is in float format (0.0–1.0) and converts it to 
 * 8-bit per channel. Writes the color at the specified index in the buffer
 * using the order: BGRA.
 *
 * @param idx Index in the buffer where the pixel starts.
 * @param pixels Pointer to the pixel buffer.
 * @param color The color to store.
 */
void	put_pixel(size_t idx, uint8_t *pixels, t_tuple color)
{
	uint32_t	packed_color;

	packed_color = float_to_hex(color);
	pixels[idx + BLUE] = (packed_color >> 24) & 0xFF;
	pixels[idx + GREEN] = (packed_color >> 16) & 0xFF;
	pixels[idx + RED] = (packed_color >> 8) & 0xFF;
	pixels[idx + ALPHA] = packed_color & 0xFF;
}

/**
 * @brief Renders the scene from the camera’s perspective by tracing 
 * rays per pixel.
 *
 * For each pixel on the screen, generates a ray through the scene, 
 * computes the color, and stores it in the image buffer. Then displays the 
 * final image in the window.
 *
 * @param rt Pointer to the main rendering context (scene, camera, objects).
 */
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
