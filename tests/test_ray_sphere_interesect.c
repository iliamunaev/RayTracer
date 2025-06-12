#include "minirt.h"

int main(void)
{
    t_primitive sphere;
    t_tuple     sph_position = {0, 0, 0, 1};
    create_sphere(&sphere, sph_position);

    t_ray   ray;
    t_tuple     ray_position = {0, 2, -5, 1};
    t_tuple     ray_vector = {0, 0, 1, 0};
    create_ray(&ray, ray_position, ray_vector);

    t_intersec  obj_intersec;
    get_obj_intersec(&obj_intersec, sphere, ray);

    printf("point1 = %f\n", obj_intersec.point[0]);
    printf("point2 = %f\n", obj_intersec.point[1]);
    printf("counter = %i\n", obj_intersec.counter);
}