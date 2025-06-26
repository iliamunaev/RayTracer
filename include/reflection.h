#ifndef REFLECTION_H
# define REFLECTION_H

// # include "minirt.h"
/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_primitive t_primitive;
typedef struct s_light t_light;
typedef struct s_ray t_ray;

typedef struct s_comps
{
    t_primitive *object;
    float       value;
    t_tuple     position;
    t_tuple     over_pos;
    t_tuple     v_eye;
    t_tuple     v_normal;
    bool        inside;
}   t_comps;

void    get_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point);
void    reflect_vec(t_tuple *reflected, t_tuple vector_in, t_tuple normal);
void    lighting(t_tuple *color, t_primitive *object, t_light light, t_tuple point, t_tuple v_eye, t_tuple v_normal, bool in_shadow, t_amb amb);
bool    check_shadow(t_rt *world, t_tuple point);
void    precompute_values(t_comps *comps, t_ray *ray);
void    color_at(t_comps *comps, t_tuple *color, t_rt *world, t_ray *ray);
// void    create_material(t_primitive *object, t_tuple color);
//void    create_point_light(t_primitive *light, t_tuple position, float brighness, t_tuple color);

#endif