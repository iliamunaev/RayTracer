#include "minirt.h"

int main(void)
{
    t_tuple point = {1, 2, 3, 1};
    t_tuple vector = {4, 5, 6, 0};
    t_ray ray;

    create_ray(&ray, point, vector);
    printf("\ray origin(%f, %f,%f) \n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf(" direction (%f, %f, %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
}