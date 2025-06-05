#include "minirt.h"

int	main(void)
{
    t_tuple vector = { -1, -2, -3};
    float m;

    m = magnitude_vector(vector);
    printf("magnitude = %f\n", m);
    return (0);
}