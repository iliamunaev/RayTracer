#include "minirt.h"


void intersect_plane(t_ray *ray, t_primitive *plane)
{
    t_ray inv_ray;
    float t;

    create_ray(&inv_ray, ray->origin, ray->direction);
    ray_transform(&inv_ray, plane->inv_matrix);

    if (fabsf(inv_ray.direction.y) < EPSILON)
        return;

    t = -inv_ray.origin.y / inv_ray.direction.y;
    if (t < EPSILON)
        return;
    ray->intersections.intersec_list[ray->intersections.counter].object = plane;
    ray->intersections.intersec_list[ray->intersections.counter].value = t;
    ray->intersections.counter++;
}


void    intersect_caps(t_ray *ray, t_primitive *cylinder)
{
    t_ray   inv_ray;
    float   t;
    float   check;

    create_ray(&inv_ray, ray->origin, ray->direction);
    ray_transform(&inv_ray, cylinder->inv_matrix);
    if(fabsf(inv_ray.direction.y) < EPSILON)
        return ;
    t = (cylinder->cylinder_min - inv_ray.origin.y) / inv_ray.direction.y;
    check = (pow((inv_ray.origin.x + t * inv_ray.direction.x), 2) + pow((inv_ray.origin.z + t * inv_ray.direction.z), 2));
    if (check <= 1)
    {
        ray->intersections.intersec_list[ray->intersections.counter].object = cylinder;
        ray->intersections.intersec_list[ray->intersections.counter].value = t;
        ray->intersections.counter++;
    }
    t = (cylinder->cylinder_max - inv_ray.origin.y) / inv_ray.direction.y;
    check = (pow((inv_ray.origin.x + t * inv_ray.direction.x), 2) + pow((inv_ray.origin.z + t * inv_ray.direction.z), 2));
    if (check <= 1)
    {
        ray->intersections.intersec_list[ray->intersections.counter].object = cylinder;
        ray->intersections.intersec_list[ray->intersections.counter].value = t;
        ray->intersections.counter++;
    }
}

void    intersect_cylinder(t_ray *ray, t_primitive *cylinder)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_ray   inv_ray;
    float   t0;
    float   t1;
    float   y0;
    float   y1;
    
    create_ray(&inv_ray, ray->origin, ray->direction);
    ray_transform(&inv_ray, cylinder->inv_matrix);
    a = inv_ray.direction.x * inv_ray.direction.x + inv_ray.direction.z * inv_ray.direction.z;
    if (a < EPSILON)
        return ;
    b = 2 * inv_ray.origin.x * inv_ray.direction.x + 2 * inv_ray.origin.z * inv_ray.direction.z;
    c = inv_ray.origin.x * inv_ray.origin.x + inv_ray.origin.z * inv_ray.origin.z - 1;
    discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
        return ;
    t0 = (float)((-b - sqrt (discriminant)) / (2 * a));
    y0 = inv_ray.origin.y + t0 * inv_ray.direction.y;

    if (cylinder->cylinder_min < y0 && y0 < cylinder->cylinder_max)
    {
        ray->intersections.intersec_list[ray->intersections.counter].object = cylinder;
        ray->intersections.intersec_list[ray->intersections.counter].value = t0;
        ray->intersections.counter++;
    }

    t1 = (float)((-b + sqrt (discriminant)) / (2 * a));
    y1 = inv_ray.origin.y + t1 * inv_ray.direction.y;

    if (cylinder->cylinder_min < y1 && y1 < cylinder->cylinder_max)
    {
        ray->intersections.intersec_list[ray->intersections.counter].object = cylinder;
        ray->intersections.intersec_list[ray->intersections.counter].value = t1;
        ray->intersections.counter++; 
    }

    // ray->intersections.intersec_list[ray->intersections.counter].object = cylinder;
    // ray->intersections.intersec_list[ray->intersections.counter].value = (float)((-b - sqrt (discriminant)) / (2 * a));
    // ray->intersections.counter++;
    // ray->intersections.intersec_list[ray->intersections.counter].object = cylinder;
    // ray->intersections.intersec_list[ray->intersections.counter].value = (float)((-b + sqrt (discriminant)) / (2 * a));
    // ray->intersections.counter++;

}
