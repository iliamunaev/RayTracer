#include "minirt.h"

void    local_normal_at(t_tuple *normal_vec, t_primitive plane, t_tuple point)
{

}

void intersect_plane(t_ray *ray, t_primitive *plane)
{
    t_ray inv_ray;
    float t;

    create_ray(&inv_ray, ray->origin, ray->direction);
    ray_transform(&inv_ray, plane->inv_matrix);

    if (fabsf(inv_ray.direction.y) < EPSILON)
        return;

    t = -inv_ray.origin.y / inv_ray.direction.y;
    ray->intersections.intersec_list[ray->intersections.counter].object = plane;
    ray->intersections.intersec_list[ray->intersections.counter].value = t;
    ray->intersections.counter++;
}