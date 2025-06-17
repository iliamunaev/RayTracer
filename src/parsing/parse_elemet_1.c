#include "minirt.h"
/*
    int         id;
    char        char_id;        // aka "A" for amb_light or "C" for cam
    t_tuple     position;       // aka t_tuple coordinates
    t_tuple     norm_vector;    //  for cam, plane, cylinder
	float       ratio;          // for amb_light
    float       brightness;     // for  light,
    t_tuple     color;
    float       diameter;       // for sphere, cylinder
    float       height;         // for cylinder
    float		fov;            // for cam
    t_matrix    matrix;
	*/
void parse_sphere(t_primitive *prim, char **tokens)
{
    prim->char_id = 's';
    prim->position = parse_tuple(tokens[1]);
    prim->diameter = ft_atof(tokens[2]);
    prim->color = parse_color(tokens[3]);
    create_identity_matrix_4x4(&prim->matrix);
}
void parse_plane(t_primitive *prim, char **tokens)
{
    create_identity_matrix_4x4(&prim->matrix);
}

void parse_cylinder(t_primitive *prim, char **tokens)
{
    create_identity_matrix_4x4(&prim->matrix);
}
