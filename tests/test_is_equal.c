// #include "minirt.h"
# include <stdbool.h>
# include <stdio.h>
# include <math.h>

#define EPSILON 0.00001


bool   is_equal(float a, float b)
{
    if (fabsf(a - b) < EPSILON)
        return (true);
    else
        return (false);
}

int	main(void)
{

    float a = -;
    float b = 2;

    float c = 0.1;
    float d = 0.2;


    float e = 0.001;
    float f = 0.001;


    float g = 0.000001;
    float h = 0.000002;


    int r_1 = is_equal(a, b); // false
    int r_2 = is_equal(c, d); // false
    int r_3 = is_equal(e, f); // true
    int r_4 = is_equal(g, h); // true

    printf("%i\n", r_1);
    printf("%i\n", r_2);
    printf("%i\n", r_3);
    printf("%i\n", r_4);;



    return (0);
}