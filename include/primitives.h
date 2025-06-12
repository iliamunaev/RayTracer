#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/


typedef struct s_primitive
{
    int id;
    t_tuple position;
}   t_primitive;

void    create_sphere(t_primitive *sphere, t_tuple position);
uint8_t generate_id();


# endif // PRIMITIVES_H