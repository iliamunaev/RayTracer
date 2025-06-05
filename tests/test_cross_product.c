#include "minirt.h"

int	main(void)
{
    t_tuple vector1 = { 1, 2, 3};
    t_tuple vector2 = { 2, 3, 4};
    t_tuple vector3;

    cross_product(&vector3, vector2, vector1);
    printf("x = %f\n", vector3.x);
    printf("y = %f\n", vector3.y);
    printf("z = %f\n", vector3.z);

    return (0);
}