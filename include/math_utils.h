#ifndef MATH_UTILS_H
# define MATH_UTILS_H

// #ifndef M_PI
// # define M_PI 3.14159265358979323846
// # endif // M_PI



#define EPSILON 0.00002
#define DEG_TO_RAD 0.01745329252f


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


// float   get_radians(float degrees);
bool    is_equal(float a, float b);
void add_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void sub_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void negate_tuple(t_tuple *tuple);
void mult_tuple(t_tuple *tuple, float scalar);
float    magnitude_vector(const t_tuple vector);
void    normalize_vector(t_tuple *vector);
float   dot_product(const t_tuple a, const t_tuple b);
void    cross_product(t_tuple *product, const t_tuple a, const t_tuple b);
float   ft_strtof(const char *start);



# endif // MATH_UTILS_H
