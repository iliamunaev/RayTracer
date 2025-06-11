#include "minirt.h"

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector)
{
    ray->origin = point;
    ray->direction = vector;
}

void    get_position(t_tuple *position, const t_ray ray, float t)
{
    position->x = ray.origin.x + ray.direction.x *t;
    position->y = ray.origin.y + ray.direction.y *t;
    position->z = ray.origin.z + ray.direction.z *t;
    position->w = ray.origin.w + ray.direction.w *t;
}