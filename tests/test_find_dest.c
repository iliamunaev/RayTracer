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
    t_tuple dest;

    // t_tuple point = {1, 2, 3, 1};
    // t_tuple vector = {2, -2, 1, 0};

    //error not sum 2 points
    t_tuple point = {1, 2, 3, 1};
    t_tuple vector = {2, -2, 1, 0};

    // t_tuple point = {-1, -1, -1, 1};
    // t_tuple vector = {-1, -1, -1, 0};

    add_tuples(&dest, point, vector);

    printf("dest x = %f\n", dest.x);
    printf("dest y = %f\n", dest.y);
    printf("dest z = %f\n", dest.z);
    printf("dest w = %i\n", dest.w);


    return (0);
}