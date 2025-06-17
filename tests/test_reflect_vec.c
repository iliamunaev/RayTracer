#include "minirt.h"

int main(void)
{
    /* t_tuple vector = {1, -1, 0};
    t_tuple normal = {0, 1, 0}; */
    t_tuple vector = {0, -1, 0};
    t_tuple normal = {sqrtf(2)/2, sqrtf(2)/2, 0};
    t_tuple reflected;

    reflect_vec(&reflected, vector, normal);
    printf("ref vector = x: %f, y: %f, z: %f\n", reflected.x, reflected.y, reflected.z);
}