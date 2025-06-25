#include "minirt.h"

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector)
{
    ray->origin = point;
    ray->direction = vector;
    ray->is_hit = false;
}

void    get_position(t_tuple *position, t_ray *ray, float time)
{
    position->x = ray->origin.x + ray->direction.x *time;
    position->y = ray->origin.y + ray->direction.y *time;
    position->z = ray->origin.z + ray->direction.z *time;
    position->w = ray->origin.w + ray->direction.w *time;
}

void    sort_intersec_list(t_intersec_point *intersec_list, int count)
{
    uint8_t i;
    int8_t j;
    t_intersec_point key;

    i = 1;
    while (i < count)
    {
        key = intersec_list[i];
        j = i - 1;
        while( j >= 0 && intersec_list[j].value > key.value)
        {
            intersec_list[j + 1] = intersec_list [j];
            j--;
        }
        intersec_list[j + 1] = key;
        i++;
    }
}

void    get_ray_intersections(t_ray *ray, t_rt *minirt)
{
    uint8_t i;


    ray->intersections.counter = 0;
    i = 0;
    while(i < minirt->obj_counted)
    {   
        get_obj_intersec(ray, &minirt->primitives_list[i]);
        i++;
    }    

    sort_intersec_list(ray->intersections.intersec_list, ray->intersections.counter);
}

void    get_obj_intersec(t_ray *ray, t_primitive *object)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_tuple sphere_to_ray;
    t_ray   inv_ray;
    t_matrix inv_matrix;
    
    create_ray(&inv_ray, ray->origin, ray->direction);
    invert_matrix(&inv_matrix, object->matrix);
    ray_transform(&inv_ray, inv_matrix);
    a = dot_product(inv_ray.direction, inv_ray.direction);
    sub_tuples(&sphere_to_ray, inv_ray.origin, object->position);
    b = 2 * dot_product(inv_ray.direction, sphere_to_ray);
    c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
    discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
        return ;

    ray->intersections.intersec_list[ray->intersections.counter].object = object;

    ray->intersections.intersec_list[ray->intersections.counter].value = (float)((-b - sqrt (discriminant)) / (2 * a));
    ray->intersections.counter++;

    ray->intersections.intersec_list[ray->intersections.counter].object = object;
    ray->intersections.intersec_list[ray->intersections.counter].value = (float)((-b + sqrt (discriminant)) / (2 * a));
    ray->intersections.counter++;

}

void get_hit(t_ray *ray)
{
    uint8_t i = 0;

    ray->is_hit = false;
    ray->hit.value = -1.0f;

    while (i < ray->intersections.counter)
    {
        if (ray->intersections.intersec_list[i].value >= 0)
        {
            ray->hit = ray->intersections.intersec_list[i];
            ray->is_hit = true;
            return;
        }
        i++;
    }
}

void	ray_transform(t_ray *ray, t_matrix matrix)
{
    mult_matrix_by_tuple(&ray->origin, matrix, ray->origin);
    mult_matrix_by_tuple(&ray->direction, matrix, ray->direction);
}
