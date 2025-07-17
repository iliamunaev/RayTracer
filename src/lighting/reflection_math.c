#include "minirt.h"

/**
 * @brief Computes the normal vector on a cylinder at a given point 
 * in world space. Handles side surface and end caps separately based 
 * on the point's position.
 *
 * @param normal pointer to the resulting normal vector (output)
 * @param object pointer to the cylinder primitive
 * @param world_point point of intersection in world coordinates
 */
void	get_cylinder_normal_at(t_tuple *normal, t_primitive *object,
		t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	float	distance;

	mult_matrix_by_tuple(&object_point, object->inv_matrix, world_point);
	distance = object_point.x * object_point.x + object_point.z
		* object_point.z;
	if (distance < 1 && object_point.y >= object->cylinder_max - EPSILON)
		create_vector(&object_normal, 0, 1, 0);
	else if (distance < 1 && object_point.y <= object->cylinder_min + EPSILON)
		create_vector(&object_normal, 0, -1, 0);
	else
		create_vector(&object_normal, object_point.x, 0, object_point.z);
	mult_matrix_by_tuple(normal, object->tran_matrix, object_normal);
	normal->w = 0;
	normalize_vector(normal);
}

/**
 * @brief Computes the normal vector on a sphere at a given point 
 * in world space. Converts the world point to object space, then 
 * computes the normal.
 *
 * @param normal pointer to the resulting normal vector (output)
 * @param object pointer to the sphere primitive
 * @param world_point point of intersection in world coordinates
 */
void	get_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	zero_point;

	mult_matrix_by_tuple(&object_point, object->inv_matrix, world_point);
	create_point(&zero_point, 0, 0, 0);
	sub_tuples(&object_normal, object_point, zero_point);
	mult_matrix_by_tuple(normal, object->tran_matrix, object_normal);
	normal->w = 0;
	normalize_vector(normal);
}

/**
 * @brief Calculates the reflected vector given an incoming
 * vector and surface normal.
 *
 * @param reflected pointer to the resulting reflected vector (output)
 * @param vector_in incoming vector (e.g. ray direction)
 * @param normal normal vector at the point of reflection
 */
void	reflect_vec(t_tuple *reflected, t_tuple vector_in, t_tuple normal)
{
	t_tuple	scaled_normal;
	float	dot;

	dot = dot_product(vector_in, normal);
	create_vector(&scaled_normal, normal.x, normal.y, normal.z);
	mult_tuple(&scaled_normal, 2 * dot);
	sub_tuples(reflected, vector_in, scaled_normal);
}
