#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/

typedef struct s_primitive
{
    int         id;
    char        type;

    t_tuple    position;
    t_tuple    norm_vector;

    float       ratio;
    float       brightness;

    t_tuple     color;
    float       diameter;
    float       height;
    float       fov;

    t_matrix    matrix;
} t_primitive;


void    create_sphere(t_primitive *sphere, t_tuple position);
uint8_t generate_id();


# endif // PRIMITIVES_H
