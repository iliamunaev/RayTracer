#include "minirt.h"

/* 
void find_dest(t_tuple *dest, t_tuple *point, t_tuple *vector)
{
    dest->x = point->x + vector->x;
    dest->y = point->y + vector->y;
    dest->z = point->z + vector->z;
    dest->w = point->w + vector->w;
    if (dest->w > 1)
        err("Error: 'w' should not be more than 1");
} */


int	main(void)
{
    t_tuple c;

    // t_tuple point = {1, 2, 3, 1};
    // t_tuple vector = {2, -2, 1, 0};

    //error not sum 2 points
    t_tuple a = {1, 2, 3, 1};
    t_tuple b = {2, -2, 1, 1};

    // t_tuple point = {-1, -1, -1, 1};
    // t_tuple vector = {-1, -1, -1, 0};

    sub_tuples(&c, a, b);

    printf("dest x = %f\n", c.x);
    printf("dest y = %f\n", c.y);
    printf("dest z = %f\n", c.z);
    printf("dest w = %i\n", c.w);


    return (0);
}