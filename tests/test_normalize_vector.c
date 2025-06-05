#include "minirt.h"

int	main(void)
{
    t_tuple vector = {1, 2, 3};


    normalize_vector(&vector);

    printf("x = %f\n", vector.x);
    printf("y = %f\n", vector.y);
    printf("z= %f\n", vector.z);

    float m = magnitude_vector(vector);
    printf("magnitude = %f\n", m);
    return (0);
}