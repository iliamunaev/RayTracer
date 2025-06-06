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
    /* if (c->w < 0)
        err("Error: 'w' should not be less than 0. Tried to substract point from vector"); */
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

float    magnitude_vector(const t_tuple vector)
{
    float magnitude;

    magnitude = sqrt(pow(vector.x, 2) + pow(vector.y , 2) + pow(vector.z, 2));
    return (magnitude);
}

void    normalize_vector(t_tuple *vector)
{
    float m;

    m = magnitude_vector(*vector);
    vector->x /= m;
    vector->y /= m;
    vector->z /= m;
}

float   dot_product(const t_tuple a, const t_tuple b)
{
    float   product;

    product = a.x * b.x + a.y * b.y + a.z * b.z;
    return (product);
}

void cross_product(t_tuple *product, const t_tuple a, const t_tuple b)
{
    product->x = a.y * b.z - a.z * b.y;
    product->y = a.z * b.x - a.x * b.z;
    product->z = a.x * b.y - a.y * b.x;
}
