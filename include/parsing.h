#ifndef PARSING_H
# define PARSING_H


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
    t_amb_light_tmp *s_amb_light;
    t_cam_tmp       *cam;
    t_light_tmp     *light;
    t_sphere_tmp    *sphere;
    t_plane_tmp     *plane;
    t_cylinder_tmp  *cylinder;    
}   t_pars;


int parse(char *map, t_rt *world);
void    init_map_tmp(t_pars *map_tmp);





# endif // PARSING_H