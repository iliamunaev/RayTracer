#include "minirt.h"

// void	parse_ambient(t_rt *rt, t_token *token)
// {
// 	rt->amb.brightness = ft_strtof(token->token[1]);
// 	parse_rgb(&rt->amb.color, token->token[2]);
// 	create_color(&rt->amb.amb_component, rt->amb.color.r, rt->amb.color.g, rt->amb.color.b);
// 	mult_tuple(&rt->amb.amb_component, rt->amb.brightness);
// 	create_identity_matrix_4x4(&rt->amb.matrix);  
// }

// void	parse_camera(t_rt *rt, t_token *token)
// {
// 	t_tuple	up;
// 	t_tuple	to;

// 	create_vector(&up, 0, 1, 0);  
// 	parse_coordinates(&rt->cam.position, token->token[1]);	
// 	parse_coordinates(&rt->cam.norm_vector, token->token[2]);
// 	normalize_vector(&rt->cam.norm_vector);
// 	add_tuples(&to, rt->cam.position, rt->cam.norm_vector);
// 	rt->cam.fov = ft_strtof(token->token[3]);
// 	rt->cam.pix_size = get_pixel_size(rt);
// 	rt->cam.half_width = get_half_width(rt);
// 	rt->cam.half_height = get_half_height(rt);
// 	rt->cam.half_view = get_half_view(rt);
// 	transform_cam_view(rt, rt->cam.position, to, up);	
// }

// void	parse_light(t_rt *rt, t_token *token)
// {
// 	parse_coordinates(&rt->light.position, token->token[1]);
// 	rt->light.brightness = ft_strtof(token->token[2]);
// 	parse_rgb(&rt->light.color, token->token[3]);
// 	create_color(&rt->light.color_component, rt->light.color.r, rt->light.color.g, rt->light.color.b);
// 	mult_tuple(&rt->light.color_component, rt->light.brightness);
// 	create_identity_matrix_4x4(&rt->light.matrix);	
// }

// void parse_sphere(t_rt *rt, t_token *token, int j)
// {
//	 t_primitive *p = &rt->primitives_list[j];

//	 /* basic attributes */
//	 p->id	   = generate_id();
//	 p->type	 = SPHERE;
//	 parse_coordinates(&p->position, token->token[1]);   /* world-space centre */
//	 p->diameter = ft_strtof(token->token[2]);
//	 parse_rgb(&p->color, token->token[3]);

//	 /* scale = radius */
//	 float radius = p->diameter / 2.0f;
//	 t_tuple scale_vec = { radius, radius, radius, 0.0f };

//	 /* build matrices */
//	 t_matrix scale_m, trans_m;
//	 scale(&scale_m,	 scale_vec);		/*  S  */
//	 translate(&trans_m, p->position);	  /*  T  */

//	 mult_matrices(&p->matrix, trans_m, scale_m);   /*  M = T * S  */
//	 invert_matrix(&p->inv_matrix, p->matrix);
//	 transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);


//	 /* keep the real world position (DO NOT reset to 0,0,0 !) */
//	 /*  p->position now holds centre in world space for later transforms  */

//	 /* ---- debug (optional) ----
//	 printf("Parsed sphere  id=%d  diam=%.2f  pos=(%.2f,%.2f,%.2f)\n",
//			p->id, p->diameter, p->position.x, p->position.y, p->position.z);
//	 print_matrix(p->matrix);
//	 */
// }


// void	parse_sphere(t_rt *rt, t_token *token, int j)
// {
// 	t_primitive	*p;
// 	t_tuple		scale_factor;
// 	t_transform	transformer;
// 	float		radius;

// 	p = &rt->primitives_list[j];
// 	p->id = generate_id();
// 	p->type = SPHERE;
// 	parse_coordinates(&p->position, token->token[1]);
// 	p->diameter = ft_strtof(token->token[2]);
// 	parse_rgb(&p->color, token->token[3]);
// 	create_identity_matrix_4x4(&p->matrix);
// 	create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
// 	radius = p->diameter / 2.0f;
// 	create_point(&transformer.scale, radius, radius, radius);
// 	mult_tuple(&transformer.rotate, 0);
// 	transform(&p->matrix, transformer);
// 	invert_matrix(&p->inv_matrix, p->matrix);
// 	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
// }

// void	parse_plane(t_rt *rt, t_token *token, int j)
// {
// 	t_primitive	*p;
// 	t_transform	transformer;

// 	p = &rt->primitives_list[j];
// 	p->id = generate_id();
// 	p->type = PLANE;
// 	parse_coordinates(&p->position, token->token[1]);
// 	parse_coordinates(&p->norm_vector, token->token[2]);
// 	parse_rgb(&p->color, token->token[3]);
// 	create_identity_matrix_4x4(&p->matrix);
// 	create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
// 	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
// 	create_point(&transformer.scale, 1, 1, 1);
// 	transform(&p->matrix, transformer);
// 	invert_matrix(&p->inv_matrix, p->matrix);
// 	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
// }

// void	parse_cylinder(t_rt *rt, t_token *token, int j)
// {
// 	t_primitive	*p;
// 	t_transform	transformer;
// 	float		radius;

// 	p = &rt->primitives_list[j];
// 	p->id = generate_id();
// 	p->type = CYLINDER;
// 	parse_coordinates(&p->position, token->token[1]);
// 	parse_coordinates(&p->norm_vector, token->token[2]);
// 	p->diameter = ft_strtof(token->token[3]);
// 	radius = p->diameter / 2.0f;
// 	p->height = ft_strtof(token->token[4]);
// 	p->cylinder_min = 0 - p->height / 2;
// 	p->cylinder_max = 0 + p->height / 2;
// 	parse_rgb(&p->color, token->token[5]);
// 	create_identity_matrix_4x4(&p->matrix);
// 	create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
// 	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
// 	create_point(&transformer.scale, radius, radius, radius);
// 	transform(&p->matrix, transformer);
// 	invert_matrix(&p->inv_matrix, p->matrix);
// 	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
// }

void	fillup_world(t_rt *rt, t_token *token, int j)
{
	char *id;

	id = token->token[0];
	if (ft_strcmp(id, "A") == 0)
		parse_ambient(rt, token);
	else if (ft_strcmp(id, "C") == 0)
		parse_camera(rt, token);
	else if (ft_strcmp(id, "L") == 0)
		parse_light(rt, token);
	else if (ft_strcmp(id, "sp") == 0)
		parse_sphere(rt, token, j);
	else if (ft_strcmp(id, "pl") == 0)
		parse_plane(rt, token, j);
	else if (ft_strcmp(id, "cy") == 0)
		parse_cylinder(rt, token, j);
	else
		err("Error: Unknown identifier");
}


