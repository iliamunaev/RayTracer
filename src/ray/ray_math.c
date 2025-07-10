#include "minirt.h"

void	ray_transform(t_ray *ray, t_matrix matrix)
{
	mult_matrix_by_tuple(&ray->origin, matrix, ray->origin);
	mult_matrix_by_tuple(&ray->direction, matrix, ray->direction);
}

void	create_ray(t_ray *ray, const t_tuple point, const t_tuple vector)
{
	ray->origin = point;
	ray->direction = vector;
	ray->is_hit = false;
}

void	get_position(t_tuple *position, t_ray *ray, float time)
{
	position->x = ray->origin.x + ray->direction.x * time;
	position->y = ray->origin.y + ray->direction.y * time;
	position->z = ray->origin.z + ray->direction.z * time;
	position->w = ray->origin.w + ray->direction.w * time;
}
