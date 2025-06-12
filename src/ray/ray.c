#include "minirt.h"

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector)
{
    ray->origin = point;
    ray->direction = vector;
    ray->is_hit = false;
}

void    get_position(t_tuple *position, const t_ray ray, float time)
{
    position->x = ray.origin.x + ray.direction.x *time;
    position->y = ray.origin.y + ray.direction.y *time;
    position->z = ray.origin.z + ray.direction.z *time;
    position->w = ray.origin.w + ray.direction.w *time;
}


void    get_ray_intersections(t_ray *ray, t_rt minirt)
{
    uint8_t i;

    t_primitive curr_object;

    ray->intersections.counter = 0;

    i = 0;
    while(i < minirt.obj_counted)
    {
        curr_object = minirt.primitives_list[i];
        get_obj_intersec(ray, curr_object);
        i++;
    }    

}

void    get_obj_intersec(t_ray *ray, t_primitive object)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_tuple sphere_to_ray;


    a = dot_product(ray->direction, ray->direction);
    sub_tuples(&sphere_to_ray, ray->origin, object.position);
    b = 2 * dot_product(ray->direction, sphere_to_ray);
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
    int i;
    t_intersec_point temp;

    i = 0;
    temp = ray->intersections.intersec_list[i];
    i++;
    while(i < ray->intersections.counter)
    {
        if(temp.value > ray->intersections.intersec_list[i].value && ray->intersections.intersec_list[i].value >= 0)
            temp = ray->intersections.intersec_list[i];
        i++;
    }
    if (temp.value >= 0)
    {
        ray->hit = temp;
        ray->is_hit = true;
    }
    //ADDED CHECK FOR IF NOT HITTED, THEN ASSIGN ALL TO -1. NEEDS VERIFICATION
}

void	ray_transform(t_ray *ray, t_transform transformation)
{
    t_matrix matrix;

    transform(&matrix, transformation);

    print_matrix(matrix);
    
    mult_matrix_by_tuple(&ray->origin, matrix, ray->origin);
    mult_matrix_by_tuple(&ray->direction, matrix, ray->direction);
}
