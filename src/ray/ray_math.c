#include "minirt.h"

/**
 * @brief Transforms a ray by applying a matrix to its origin and direction.
 * Typically used to convert the ray to object space.
 *
 * @param ray pointer to the ray to be transformed (modified in-place)
 * @param matrix the transformation matrix to apply
 */
void	ray_transform(t_ray *ray, t_matrix matrix)
{
	mult_matrix_by_tuple(&ray->origin, matrix, ray->origin);
	mult_matrix_by_tuple(&ray->direction, matrix, ray->direction);
}

/**
 * @brief Initializes a ray with a given origin point and direction vector.
 * Also resets the hit status.
 *
 * @param ray pointer to the ray to initialize
 * @param point the origin of the ray
 * @param vector the direction of the ray
 */
void	create_ray(t_ray *ray, const t_tuple point, const t_tuple vector)
{
	ray->origin = point;
	ray->direction = vector;
	ray->is_hit = false;
}

/**
 * @brief Computes a point along a ray at a given time (distance).
 *
 * @param position output tuple storing the computed position
 * @param ray pointer to the ray
 * @param time scalar value representing how far along the ray to compute
 */
void	get_position(t_tuple *position, t_ray *ray, float time)
{
	position->x = ray->origin.x + ray->direction.x * time;
	position->y = ray->origin.y + ray->direction.y * time;
	position->z = ray->origin.z + ray->direction.z * time;
	position->w = ray->origin.w + ray->direction.w * time;
}
