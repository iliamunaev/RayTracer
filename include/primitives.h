#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_rt t_rt;


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
    t_tuple     position;
    t_tuple     norm_vector;
    float       diameter;
    float       height;
    t_tuple     color;
    t_material  material;
    t_matrix    matrix;
} t_primitive;


typedef struct s_amb
{
    float       brightness;
    t_tuple     color;
    t_tuple     amb_component;
    t_matrix    matrix;
}   t_amb;

typedef struct s_cam
{
    t_tuple     position;
    t_tuple     norm_vector;
    float       fov;
    float       pix_size;
    float       half_width;
    float       half_height;
    float       half_view;
    t_matrix    matrix;
    t_matrix    inv_matrix;
}   t_cam;

typedef struct s_light
{
    t_tuple     position;
    float       brightness;
    t_tuple     color;
    t_tuple     color_component;
    t_matrix    matrix;
}   t_light;


void    create_sphere(t_primitive *sphere, t_tuple position);
uint8_t generate_id();

// primitive_utils.c
t_primitive *find_primitive(t_rt *world, char *type);

//transform_cam_view.c
void transform_cam_view(t_rt *rt, t_tuple from, t_tuple to, t_tuple up);

//camera.c
float get_pixel_size(t_rt *rt);
float get_half_height(t_rt *rt);
float get_half_width(t_rt *rt);
float get_half_view(t_rt *rt);
void ray_for_pixel(t_ray *ray, t_cam *cam, float px, float py);

# endif // PRIMITIVES_H
