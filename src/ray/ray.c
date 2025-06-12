#include "minirt.h"

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector)
{
    ray->origin = point;
    ray->direction = vector;
}

void    get_position(t_tuple *position, const t_ray ray, float time)
{
    position->x = ray.origin.x + ray.direction.x *time;
    position->y = ray.origin.y + ray.direction.y *time;
    position->z = ray.origin.z + ray.direction.z *time;
    position->w = ray.origin.w + ray.direction.w *time;
}

void    get_obj_intersec(t_intersec *obj_intersec, t_primitive object, t_ray ray)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_tuple sphere_to_ray;

    obj_intersec->counter = 0;
    obj_intersec->object = object;
    
    a = dot_product(ray.direction, ray.direction);
    sub_tuples(&sphere_to_ray, ray.origin, object.position);
    b = 2 * dot_product(ray.direction, sphere_to_ray);
    c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
    discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
        return ;
    obj_intersec->point[0] = (float)((-b - sqrt (discriminant)) / (2 * a));
    obj_intersec->point[1] = (float)((-b + sqrt (discriminant)) / (2 * a));
    obj_intersec->counter = 2;
}