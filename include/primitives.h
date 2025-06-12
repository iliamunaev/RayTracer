#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/

typedef struct s_tuple t_tuple;
typedef struct s_ray t_ray;

typedef struct s_sphere
{
    uint8_t id;
}   t_sphere;

void    create_sphere(t_sphere *sphere);
uint8_t generate_id();


# endif // PRIMITIVES_H