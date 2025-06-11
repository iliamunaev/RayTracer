#ifndef RAY_H
# define RAY_H

/*------FORWARD DECLARATIONS-----------------------------------------*/

typedef struct s_tuple t_tuple;
typedef struct s_ray t_ray;

void    create_ray(t_ray *ray, const t_tuple point, const t_tuple vector);
void    get_position(t_tuple *position, const t_ray ray, float t);


# endif // RAY_H