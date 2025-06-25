#include "minirt.h"

int main(void)
{
    t_tuple point = {2, 3, 4, 1};
    t_tuple vector = {1, 1, 0, 0};
    t_tuple position;
    t_ray ray;

    create_ray(&ray, point, vector);
    get_position(&position, &ray, -4);

    printf("\ray position(%f, %f,%f, %f) \n", position.x, position.y, position.z, position.w);
    //printf(" direction (%f, %f, %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
}