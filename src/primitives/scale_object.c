#include "minirt.h"

/**
 * @brief Scales the currently selected object in the scene by a given factor.
 * Only applies to non-plane objects. Updates all related 
 * transformation matrices.
 *
 * @param world pointer to the main scene context
 * @param factor scaling multiplier (e.g. 1.1 to enlarge, 0.9 to shrink)
 */
void	scale_object(t_rt *world, float factor)
{
	t_tuple		scale_vec;
	float		radius;
	t_transform	transformer;
	t_primitive	*p;
	int			idx;

	idx = world->selected_primitive_index;
	p = &world->primitives_list[idx];
	if (idx < 0 || idx >= world->obj_counted)
		return ;
	if (p->type == PLANE)
		return ;
	p->diameter = p->diameter * factor;
	radius = p->diameter / 2.0f;
	create_vector(&scale_vec, radius, radius, radius);
	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y,
		p->norm_vector.z);
	create_point(&transformer.scale, radius, radius, radius);
	create_point(&transformer.translate, p->position.x, p->position.y,
		p->position.z);
	transform(&p->matrix, transformer);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}

/**
 * @brief Translates (moves) the currently selected object in the scene
 * by the specified offset along each axis.
 * Updates the object's transformation matrices accordingly.
 *
 * @param world pointer to the main scene context
 * @param factor_x translation along the X axis
 * @param factor_y translation along the Y axis
 * @param factor_z translation along the Z axis
 */
void	translate_object(t_rt *world, float factor_x, float factor_y,
		float factor_z)
{
	t_primitive	*p;
	int			idx;
	t_transform	transformer;
	float		radius;

	idx = world->selected_primitive_index;
	if (idx < 0 || idx >= world->obj_counted)
		return ;
	p = &world->primitives_list[idx];
	p->position.x = p->position.x + factor_x;
	p->position.y = p->position.y + factor_y;
	p->position.z = p->position.z + factor_z;
	radius = p->diameter / 2.0f;
	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y,
		p->norm_vector.z);
	create_point(&transformer.scale, radius, radius, radius);
	create_point(&transformer.translate, p->position.x, p->position.y,
		p->position.z);
	transform(&p->matrix, transformer);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}

/**
 * @brief Rotates the currently selected object by modifying its normal vector.
 * Skips rotation for spheres. Updates transformation matrices after rotation.
 *
 * @param world pointer to the main scene context
 * @param factor_x rotation offset along the X axis
 * @param factor_y rotation offset along the Y axis
 * @param factor_z rotation offset along the Z axis
 */
void	rotate_object(t_rt *world, float factor_x, float factor_y,
		float factor_z)
{
	t_primitive	*p;
	int			idx;
	float		radius;
	t_transform	transformer;

	idx = world->selected_primitive_index;
	p = &world->primitives_list[idx];
	if (idx < 0 || idx >= world->obj_counted)
		return ;
	if (p->type == SPHERE)
		return ;
	p->norm_vector.x = p->norm_vector.x + factor_x;
	p->norm_vector.y = p->norm_vector.y + factor_y;
	p->norm_vector.z = p->norm_vector.z + factor_z;
	normalize_vector(&p->norm_vector);
	radius = p->diameter / 2.0f;
	create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y,
		p->norm_vector.z);
	create_point(&transformer.scale, radius, radius, radius);
	create_point(&transformer.translate, p->position.x, p->position.y,
		p->position.z);
	transform(&p->matrix, transformer);
	invert_matrix(&p->inv_matrix, p->matrix);
	transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}
