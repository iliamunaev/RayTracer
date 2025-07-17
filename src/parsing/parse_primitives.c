#include "minirt.h"

/**
 * @brief Generates a unique object ID for a primitive.
 * Starts from 0 and increments on each call.
 *
 * @return uint8_t the next available ID
 */
static inline uint8_t	generate_id(void)
{
	static uint8_t	current_id;

	current_id = 0;
	return (current_id++);
}

/**
 * @brief Parses an optional bonus type (e.g., "gl" for glass, "ch" for checker)
 * from a token and assigns it to the given primitive.
 *
 * @param i index of the bonus token in the token list
 * @param token pointer to tokenized input
 * @param p pointer to the primitive being configured
 */
void	parse_bonus_type(int i, t_token *token, t_primitive *p)
{
	if (!ft_strcmp(token->token[i], "gl"))
		p->bonus_type = GLASS;
	else if (!ft_strcmp(token->token[i], "ch"))
		p->bonus_type = CHECKER;
	else
		p->bonus_type = DEFAULT;
}

/**
 * @brief Parses and initializes a sphere primitive, including its
 * position, size, color, transformations, and optional bonus type.
 *
 * @param rt pointer to the main scene struct
 * @param token parsed input tokens for the sphere
 * @param j index in the primitives list to populate
 */
void	parse_sphere(t_rt *rt, t_token *token, int j)
{
	t_primitive	*p;
	t_transform	transformer;

	p = &rt->primitives_list[j];
	p->id = generate_id();
	p->type = SPHERE;
	parse_coordinates(&p->position, token->token[1]);
	p->diameter = ft_strtof(token->token[2]);
	parse_rgb(&p->color, token->token[3]);
	parse_bonus_type(4, token, p);
	create_identity_matrix_4x4(&p->matrix);
	create_point(&transformer.translate, p->position.x, p->position.y,
		p->position.z);
	create_point(&transformer.scale, p->diameter / 2.0f, p->diameter / 2.0f,
		p->diameter / 2.0f);
	mult_tuple(&transformer.rotate, 0);
	transform(&p->matrix, transformer);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}

/**
 * @brief Parses and initializes a plane primitive, including its
 * position, normal vector, color, transformations, and optional bonus type.
 *
 * @param rt pointer to the main scene struct
 * @param token parsed input tokens for the plane
 * @param j index in the primitives list to populate
 */
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
	parse_bonus_type(4, token, p);
	create_identity_matrix_4x4(&p->matrix);
	create_point(&transformer.translate, p->position.x, p->position.y,
		p->position.z);
	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y,
		p->norm_vector.z);
	create_point(&transformer.scale, 1, 1, 1);
	transform(&p->matrix, transformer);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}

/**
 * @brief Parses and initializes a cylinder primitive, including its
 * position, orientation, size (diameter & height), color, and 
 * transformation matrices.
 *
 * @param rt pointer to the main scene struct
 * @param token parsed input tokens for the cylinder
 * @param j index in the primitives list to populate
 */
void	parse_cylinder(t_rt *rt, t_token *token, int j)
{
	t_primitive	*p;
	t_transform	tr;
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
	parse_bonus_type(6, token, p);
	create_identity_matrix_4x4(&p->matrix);
	create_point(&tr.translate, p->position.x, p->position.y, p->position.z);
	create_point(&tr.rotate, p->norm_vector.x, p->norm_vector.y,
		p->norm_vector.z);
	create_point(&tr.scale, radius, radius, radius);
	transform(&p->matrix, tr);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}
