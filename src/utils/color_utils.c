#include "minirt.h"

void add_colors(t_tuple *c, const t_tuple a, const t_tuple b)
{
    c->r = a.r + b.r;
    c->g = a.g + b.g;
    c->b = a.b + b.b;
}

void sub_colors(t_tuple *c, const t_tuple a, const t_tuple b)
{
    c->r = a.r - b.r;
    c->g = a.g - b.g;
    c->b = a.b - b.b;
}

void mult_colors(t_tuple *tuple, const t_tuple a, const t_tuple b)
{
    tuple->r = a.r * b.r;
    tuple->g = a.g * b.g;
    tuple->b = a.b * b.b;
}