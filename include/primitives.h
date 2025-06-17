#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/


typedef struct s_primitive
{
    int         id;
    char        char_id; // aka "A" for amb_light or "C" for cam
    t_tuple     position;  // aka t_tuple coordinates
    t_tuple     norm_vector; //  for cam, plane, cylinder
	float       ratio;      // for amb_light
    float       brightness;  // for  light, 
    t_tuple     color;  
    float       diameter;  // for sphere, cylinder
    float       height;   // for cylinder
    float		fov;    // for cam 
    t_matrix    matrix;
}   t_primitive;

void    create_sphere(t_primitive *sphere, t_tuple position);
uint8_t generate_id();


# endif // PRIMITIVES_H