#ifndef PARSING_H
# define PARSING_H

#define MAX_ELEMENTS 32

typedef struct s_amb_light_tmp
{
    char    *id;
    char    *ratio;
    char    *color;
}   t_amb_light_tmp;

typedef struct s_cam_tmp
{
    char    *id;
    char    *coordinates;
    char    *norm_vector;
    char    *fov;
}   t_cam_tmp;

typedef struct s_light_tmp
{
    char    *id;
    char    *coordinates;
    char    *brightness;
    char    *color;
}   t_light_tmp;


typedef struct s_sphere_tmp
{
    char    *id;
    char    *coordinates;
    char    *diameter;
    char    *color;
}   t_sphere_tmp;

typedef struct s_plane_tmp
{
    char    *id;
    char    *coordinates;
    char    *norm_vector;
    char    *color;
}   t_plane_tmp;

typedef struct s_cylinder_tmp
{
    char    *id;
    char    *coordinates;
    char    *norm_vector;
    char    *diameter;
    char    *height;
    char    *color;
}   t_cylinder_tmp;

typedef struct s_pars
{
    t_primitive *element;
    int         count;
}   t_pars;

// parsing.c
int parse(char *map, t_rt *world);
t_pars *init_map_tmp(int num_el);

//parsing_utils.c
void free_map_tmp(t_pars *map_tmp);
uint8_t count_elements(const char *map);

// fillup_world.c
void fillup_world(t_rt *world, const t_pars *map_tmp);

// init_map.c
t_pars *init_map_tmp(int num_el);

// parse_elemet_1.c
void parse_sphere(t_primitive *prim, char **tokens);
void parse_plane(t_primitive *prim, char **tokens);
void parse_cylinder(t_primitive *prim, char **tokens);

// parse_elemet_2.c
void parse_light(t_primitive *prim, char **tokens);
void parse_camera(t_primitive *prim, char **tokens);
void parse_ambient(t_primitive *prim, char **tokens);



# endif // PARSING_H
