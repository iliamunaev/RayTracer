#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/

typedef struct s_amb_light
{
	char	id;
	float	ratio;
	t_tuple	color;
}	t_amb_light;


typedef struct s_cam
{
    char    id;
    t_tuple    coordinates;
    t_tuple    norm_vector;
    float		fov;
}   t_cam;

typedef struct s_light
{
    char	id;
	t_tuple	coordinates;
    float	brightness;
    t_tuple	color;
}   t_light;

typedef struct s_sphere
{
    char    id;
    t_tuple    coordinates;
    float   diameter;
    t_tuple	color;
}   t_sphere;

typedef struct s_plane_tmp
{
    char    id;
    t_tuple    coordinates;
    t_tuple    norm_vector;
    t_tuple    color;
}   t_plane_tmp;

typedef struct s_cylinder_tmp
{
    char    id;
    t_tuple    coordinates;
    t_tuple    norm_vector;
    float    diameter;
    float    height;
    t_tuple    color;
}   t_cylinder_tmp;

typedef struct s_primitive
{
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
}   t_primitive;

void    create_sphere(t_primitive *sphere, t_tuple position);
uint8_t generate_id();


# endif // PRIMITIVES_H
