#ifndef MATH_UTILS_H
# define MATH_UTILS_H

#ifndef M_PI
# define M_PI 3.14159265358979323846
# endif // M_PI

#define EPSILON 0.00001


/*------FORWARD DECLARATIONS-----------------------------------------*/

typedef struct s_tuple t_tuple;


float   radians(float degrees);
bool    is_equal(float a, float b);
void add_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void sub_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void negate_tuple(t_tuple *tuple);
void mult_tuple(t_tuple *tuple, float scalar);
float    magnitude_vector(const t_tuple vector);
void    normalize_vector(t_tuple *vector);
float   dot_product(const t_tuple a, const t_tuple b);
void cross_product(t_tuple *product, const t_tuple a, const t_tuple b);

# endif // MATH_UTILS_H
