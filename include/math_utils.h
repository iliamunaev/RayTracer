#ifndef MATH_UTILS_H
# define MATH_UTILS_H

#ifndef M_PI
# define M_PI 3.14159265358979323846
# endif // M_PI

#define EPSILON 0.00001


// # include "minirt.h"
/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_primitive t_primitive;
typedef struct s_light t_light;
typedef struct s_ray t_ray;


typedef struct s_tuple
{
    union
    {
        float   x;
        float   r;
    };
    union
    {
        float   y;
        float   g;
    };
    union
    {
        float   z;
        float   b;
    };
    union
    {
        float w;
        float a;
    };
}   t_tuple;

// typedef struct s_vector {
//     float x, y, z, w;
// } t_vector;

// typedef struct s_color {
//     float r;
//     float g;
//     float b;
//     float a;
// } t_color;

float   get_radians(float degrees);
bool    is_equal(float a, float b);
void add_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void sub_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void negate_tuple(t_tuple *tuple);
void mult_tuple(t_tuple *tuple, float scalar);
float    magnitude_vector(const t_tuple vector);
void    normalize_vector(t_tuple *vector);
float   dot_product(const t_tuple a, const t_tuple b);
void cross_product(t_tuple *product, const t_tuple a, const t_tuple b);
float ft_strtof(const char *start);

// reflection -> needs to go somewhere else
void    get_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point);
void    reflect_vec(t_tuple *reflected, t_tuple vector_in, t_tuple normal);
void    lighting(t_tuple *color, t_primitive *object, t_light *light, t_ray ray);
// void    create_material(t_primitive *object, t_tuple color);
void    create_point_light(t_primitive *light, t_tuple position, float brighness, t_tuple color);

# endif // MATH_UTILS_H
