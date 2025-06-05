#include "minirt.h"

int	main(void)
{
    t_tuple a = {1, 2, 3};
    t_tuple b = {2, 3, 4};


    float res = dot_product(a, b);

    printf("dot  product = %f\n", res);
    return (0);
}