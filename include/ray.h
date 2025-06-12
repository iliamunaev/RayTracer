#ifndef RAY_H
# define RAY_H

# include "primitives.h"

# define MAX_INTERSECTIONS 128

/*------FORWARD DECLARATIONS-----------------------------------------*/

typedef struct s_rt t_rt;
// typedef struct s_primitive t_primitive;


typedef struct s_intersec_point
{   
    float   value;
    t_primitive object;
}   t_intersec_point;


typedef struct s_intersec
{
    t_intersec_point    intersec_list[MAX_INTERSECTIONS];
    uint8_t             counter;
}   t_intersec;

typedef struct s_ray
{
    t_tuple origin;
    t_tuple direction;
    t_intersec intersections;
    t_intersec_point    hit;
    bool                is_hit;
    
}   t_ray;

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector);
void    get_position(t_tuple *position, const t_ray ray, float time);
void    get_obj_intersec(t_ray *ray, t_primitive object);
void    get_ray_intersections(t_ray *ray, t_rt minirt);
void    get_hit(t_ray *ray);
void	ray_transform(t_ray *ray, t_matrix matrix);


# endif // RAY_H