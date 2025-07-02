#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_rt t_rt;
typedef struct s_ray t_ray;

typedef enum e_type
{
    SPHERE,
    PLANE,
    CYLINDER
}   t_type;

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
    // char        type[3];
    t_type      type;
    t_tuple     position;
    t_tuple     norm_vector;
    t_tuple     color;
    float     cylinder_min;
    float     cylinder_max;
    float       diameter;
    float       height;
    t_material  material;
    t_matrix    matrix;
    t_matrix    inv_matrix;
    t_matrix    tran_matrix;
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
t_primitive *find_primitive(t_rt *world, t_type type);

//transform_cam_view.c
void transform_cam_view(t_rt *rt, t_tuple from, t_tuple to, t_tuple up);
void rebuild_camera(t_rt *rt);

//camera.c
float get_pixel_size(t_rt *rt);
float get_half_height(t_rt *rt);
float get_half_width(t_rt *rt);
float get_half_view(t_rt *rt);
void ray_for_pixel(t_ray *ray, t_cam *cam, float px, float py);

//primitive_intersections.c
void intersect_plane(t_ray *ray, t_primitive *plane);
void intersect_cylinder(t_ray *ray, t_primitive *cylinder);

# endif // PRIMITIVES_H
