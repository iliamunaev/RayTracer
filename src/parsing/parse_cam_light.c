#include "minirt.h"

/**
 * @brief Parses the ambient light settings from the token 
 * array and stores them in the scene.
 *
 * Sets the ambient light brightness, color, calculates 
 * the ambient component color,
 * and initializes its transformation matrix to identity.
 *
 * @param rt Pointer to the scene structure.
 * @param token Token array containing the ambient light data.
 */
void	parse_ambient(t_rt *rt, t_token *token)
{
	rt->amb.brightness = ft_strtof(token->token[1]);
	parse_rgb(&rt->amb.color, token->token[2]);
	create_color(&rt->amb.amb_component, rt->amb.color.r, rt->amb.color.g,
		rt->amb.color.b);
	mult_tuple(&rt->amb.amb_component, rt->amb.brightness);
	create_identity_matrix_4x4(&rt->amb.matrix);
}

/**
 * @brief Parses camera data from tokens and initializes the camera in the scene.
 *
 * Sets the position, normalized direction, and field of view (FOV).
 * Calculates camera pixel size, screen half dimensions, and view.
 * Initializes the camera transformation matrix based on its view direction.
 *
 * @param rt Pointer to the scene structure.
 * @param token Token array containing the camera data.
 */
void	parse_camera(t_rt *rt, t_token *token)
{
	t_tuple	up;
	t_tuple	to;

	create_vector(&up, 0, 1, 0);
	parse_coordinates(&rt->cam.position, token->token[1]);
	parse_coordinates(&rt->cam.norm_vector, token->token[2]);
	normalize_vector(&rt->cam.norm_vector);
	add_tuples(&to, rt->cam.position, rt->cam.norm_vector);
	rt->cam.fov = ft_strtof(token->token[3]);
	rt->cam.pix_size = get_pixel_size(rt);
	rt->cam.half_width = get_half_width(rt);
	rt->cam.half_height = get_half_height(rt);
	rt->cam.half_view = get_half_view(rt);
	transform_cam_view(rt, rt->cam.position, to, up);
}

/**
 * @brief Parses the light source information from tokens and 
 * sets it in the scene.
 *
 * Sets the light's position, brightness, and color. Computes the final color
 * component based on brightness and initializes the transformation matrix.
 *
 * @param rt Pointer to the scene structure.
 * @param token Token array containing the light data.
 */
void	parse_light(t_rt *rt, t_token *token)
{
	parse_coordinates(&rt->lights[rt->lightcount].position, token->token[1]);
	rt->lights[rt->lightcount].brightness = ft_strtof(token->token[2]);
	parse_rgb(&rt->lights[rt->lightcount].color, token->token[3]);
	create_color(&rt->lights[rt->lightcount].color_component, rt->lights[rt->lightcount].color.r,
		rt->lights[rt->lightcount].color.g, rt->lights[rt->lightcount].color.b);
	mult_tuple(&rt->lights[rt->lightcount].color_component, rt->lights[rt->lightcount].brightness);
	create_identity_matrix_4x4(&rt->lights[rt->lightcount].matrix);
	rt->lightcount++;
}
