#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/


typedef struct s_material
{
    t_tuple color;
    float   ambient;
    float   diffuse;
    float   specular;
    float   shininess; // between 10 and 200
}   t_material;

typedef struct s_primitive
{
    int         id;
    char        type[3];

    t_tuple    position;
    t_tuple    norm_vector;

    float       ratio;
    float       brightness;

    t_tuple     color;
    float       diameter;
    float       height;
    float       fov;
    t_material  material;

    t_matrix    matrix;
} t_primitive;


void    create_sphere(t_primitive *sphere, t_tuple position);
uint8_t generate_id();


# endif // PRIMITIVES_H
