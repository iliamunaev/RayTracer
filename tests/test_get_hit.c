#include "minirt.h"


/* void get_hit(t_ray *ray)
{
    uint8_t i;
    t_intersec_point temp;

    i = 0;
    temp = ray->intersections.intersec_list[i];
    while(i < ray->intersections.counter - 1)
    {
        if(temp.value > ray->intersections.intersec_list[++i].value)
            temp = ray->intersections.intersec_list[i];
    }
} */

int main() {


    t_primitive sphere;
    t_tuple     sph_position = {0, 2, -9, 1};
    create_sphere(&sphere, sph_position);

    t_primitive sphere2;
    t_tuple     sph_position2 = {0, 0, -8, 1};
    create_sphere(&sphere2, sph_position2);

    t_primitive sphere3;
    t_tuple     sph_position3 = {0, 0, -7, 1};
    create_sphere(&sphere3, sph_position3);

    t_ray   ray;
    t_tuple     ray_position = {0, 0, -5, 1};
    t_tuple     ray_vector = {0, 0, 1, 0};
    create_ray(&ray, ray_position, ray_vector);

    t_rt minirt;

    minirt.mlx = NULL;
    minirt.obj_counted = 3;
    minirt.primitives_list[0] = sphere;
    minirt.primitives_list[1] = sphere2;
    minirt.primitives_list[2] = sphere3;

    get_ray_intersections(&ray, minirt);

    printf("counter = %i\n", ray.intersections.counter);

    
    printf("point1 = %f\n", ray.intersections.intersec_list[0].value);
    printf("point2 = %f\n", ray.intersections.intersec_list[1].value);
    printf("point3 = %f\n", ray.intersections.intersec_list[2].value);
    printf("point4 = %f\n", ray.intersections.intersec_list[3].value);
    printf("point5 = %f\n", ray.intersections.intersec_list[4].value);
    printf("point6 = %f\n", ray.intersections.intersec_list[5].value);


    get_hit(&ray);
    
    printf("min: %f\n", ray.hit.value);
    return 0;
}