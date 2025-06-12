#ifndef RAY_H
# define RAY_H

# include "primitives.h"

/*------FORWARD DECLARATIONS-----------------------------------------*/

// typedef struct s_tuple t_tuple;
// typedef struct s_primitive t_primitive;

typedef struct s_ray
{
    t_tuple origin;
    t_tuple direction;
}   t_ray;

typedef struct s_intersec
{
    float point[2];
    uint8_t counter;
    t_primitive object;
}   t_intersec;

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector);
void    get_position(t_tuple *position, const t_ray ray, float time);
void    get_obj_intersec(t_intersec *obj_intersec, t_primitive object, t_ray ray);


# endif // RAY_H