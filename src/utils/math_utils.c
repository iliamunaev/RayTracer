#include "minirt.h"


float   radians(float degrees)
{
    return degrees * (M_PI / 180);
}

bool   is_equal(float a, float b) // tested
{
    if (fabsf(a - b) < EPSILON)
        return (true);
    else
        return (false);
}

void add_tuples(t_tuple *c, const t_tuple a, const t_tuple b)
{
    c->x = a.x + b.x;
    c->y = a.y + b.y;
    c->z = a.z + b.z;
    c->w = a.w + b.w;
    if (c->w > 1)
        err("Error: 'w' should not be more than 1. Tried to add two points");
}

void sub_tuples(t_tuple *c, const t_tuple a, const t_tuple b)
{
    c->x = a.x - b.x;
    c->y = a.y - b.y;
    c->z = a.z - b.z;
    c->w = a.w - b.w;
    if (c->w < 0)
        err("Error: 'w' should not be less than 0. Tried to substract point from vector");
}

void negate_tuple(t_tuple *tuple)
{
    tuple->x *= -1;
    tuple->y *= -1;
    tuple->z *= -1;
    //do we need w = -w  ?
}

void mult_tuple(t_tuple *tuple, float scalar)
{
    tuple->x *= scalar;
    tuple->y *= scalar;
    tuple->z *= scalar;
}

void dev_tuple(t_tuple *tuple, float scalar)
{
    tuple->x /= scalar;
    tuple->y /= scalar;
    tuple->z /= scalar;
}