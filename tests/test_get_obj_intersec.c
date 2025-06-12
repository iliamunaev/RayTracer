#include "minirt.h"

int main(void)
{
    t_primitive sphere;
    t_tuple     sph_position = {0, 2, 0, 1};
    create_sphere(&sphere, sph_position);

    t_primitive sphere2;
    t_tuple     sph_position2 = {0, 0, 0, 1};
    create_sphere(&sphere2, sph_position2);

    t_primitive sphere3;
    t_tuple     sph_position3 = {0, 1, 0, 1};
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


    printf("point1 = %f\n", ray.intersections.intersec_list[0].value);
    printf("point2 = %f\n", ray.intersections.intersec_list[1].value);
    printf("point3 = %f\n", ray.intersections.intersec_list[2].value);
    printf("point4 = %f\n", ray.intersections.intersec_list[3].value);

    printf("counter = %i\n", ray.intersections.counter);

}