#include "minirt.h"

float   get_radians(float degrees)
{
    return (degrees * DEG_TO_RAD);
}

bool    is_equal(float a, float b)
{
    return (fabsf(a - b) < EPSILON);
}

void add_tuples(t_tuple *c, const t_tuple a, const t_tuple b)
{
    c->x = a.x + b.x;
    c->y = a.y + b.y;
    c->z = a.z + b.z;
    c->w = a.w + b.w;
    if (c->w > 1)
        c->w = 1;
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


float magnitude_vector(const t_tuple v)
{
    return (sqrtf(dot_product(v, v)));
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

float ft_strtof(const char *start)
{
    float result = 0.0f, fraction = 0.0f, divider = 10.0f;
    int dot_seen = 0, sign = 1;

    // Skip leading spaces
    while (*start == ' ') start++;

    // Handle sign
    if (*start == '-') {
        sign = -1;
        start++;
    }

    while (*start)
    {
        if (*start == '.')
        {
            if (dot_seen)
                break;
            dot_seen = 1;
            start++;
            continue;
        }
        if (*start >= '0' && *start <= '9')
        {
            if (!dot_seen)
                result = result * 10.0f + (*start - '0');
            else
            {
                fraction += (*start - '0') / divider;
                divider *= 10.0f;
            }
        }
        else
            break;
        start++;
    }
    return (sign * (result + fraction));
}
