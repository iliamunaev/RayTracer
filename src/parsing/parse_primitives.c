#include "minirt.h"

void	parse_sphere(t_rt *rt, t_token *token, int j)
{
	t_primitive	*p;
	t_tuple		scale_factor;
	t_transform	transformer;
	float		radius;

	p = &rt->primitives_list[j];
	p->id = generate_id();
	p->type = SPHERE;
	parse_coordinates(&p->position, token->token[1]);
	p->diameter = ft_strtof(token->token[2]);
	parse_rgb(&p->color, token->token[3]);
	create_identity_matrix_4x4(&p->matrix);
	create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
	radius = p->diameter / 2.0f;
	create_point(&transformer.scale, radius, radius, radius);
	mult_tuple(&transformer.rotate, 0);
	transform(&p->matrix, transformer);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}

void	parse_plane(t_rt *rt, t_token *token, int j)
{
	t_primitive	*p;
	t_transform	transformer;

	p = &rt->primitives_list[j];
	p->id = generate_id();
	p->type = PLANE;
	parse_coordinates(&p->position, token->token[1]);
	parse_coordinates(&p->norm_vector, token->token[2]);
	parse_rgb(&p->color, token->token[3]);
	create_identity_matrix_4x4(&p->matrix);
	create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
	create_point(&transformer.scale, 1, 1, 1);
	transform(&p->matrix, transformer);
	p->position.x = 0.0f;
	p->position.y = 0.0f;
	p->position.z = 0.0f;
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}

void	parse_cylinder(t_rt *rt, t_token *token, int j)
{
	t_primitive	*p;
	t_transform	transformer;
	float		radius;

	p = &rt->primitives_list[j];
	p->id = generate_id();
	p->type = CYLINDER;
	parse_coordinates(&p->position, token->token[1]);
	parse_coordinates(&p->norm_vector, token->token[2]);
	p->diameter = ft_strtof(token->token[3]);
	radius = p->diameter / 2.0f;
	p->height = ft_strtof(token->token[4]);
	p->cylinder_min = 0 - p->height / 2;
	p->cylinder_max = 0 + p->height / 2;
	parse_rgb(&p->color, token->token[5]);
	create_identity_matrix_4x4(&p->matrix);
	create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
	create_point(&transformer.scale, radius, radius, radius);
	transform(&p->matrix, transformer);
	p->position.x = 0.0f;
	p->position.y = 0.0f;
	p->position.z = 0.0f;
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}
