#include "minirt.h"

void	parse_ambient(t_rt *rt, t_token *token)
{
	rt->amb.brightness = ft_strtof(token->token[1]);
	parse_rgb(&rt->amb.color, token->token[2]);
	create_color(&rt->amb.amb_component, rt->amb.color.r, rt->amb.color.g, rt->amb.color.b);
	mult_tuple(&rt->amb.amb_component, rt->amb.brightness);
	create_identity_matrix_4x4(&rt->amb.matrix);
}

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

void	parse_light(t_rt *rt, t_token *token)
{
	parse_coordinates(&rt->light.position, token->token[1]);
	rt->light.brightness = ft_strtof(token->token[2]);
	parse_rgb(&rt->light.color, token->token[3]);
	create_color(&rt->light.color_component, rt->light.color.r, rt->light.color.g, rt->light.color.b);
	mult_tuple(&rt->light.color_component, rt->light.brightness);
	create_identity_matrix_4x4(&rt->light.matrix);
}
