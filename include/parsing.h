#ifndef PARSING_H
# define PARSING_H

#define MAX_NUM_TOKENS 6
#define MAX_TOKEN_LENGTH 32

// typedef struct s_amb_light_tmp
// {
//     char    *id;
//     char    *ratio;
//     char    *color;
// }   t_amb_light_tmp;

// typedef struct s_cam_tmp
// {
//     char    *id;
//     char    *coordinates;
//     char    *norm_vector;
//     char    *fov;
// }   t_cam_tmp;

// typedef struct s_light_tmp
// {
//     char    *id;
//     char    *coordinates;
//     char    *brightness;
//     char    *color;
// }   t_light_tmp;


// typedef struct s_sphere_tmp
// {
//     char    *id;
//     char    *coordinates;
//     char    *diameter;
//     char    *color;
// }   t_sphere_tmp;

// typedef struct s_plane_tmp
// {
//     char    *id;
//     char    *coordinates;
//     char    *norm_vector;
//     char    *color;
// }   t_plane_tmp;

// typedef struct s_cylinder_tmp
// {
//     char    *id;
//     char    *coordinates;
//     char    *norm_vector;
//     char    *diameter;
//     char    *height;
//     char    *color;
// }   t_cylinder_tmp;

typedef struct s_pars
{
    t_primitive *element;
    int         count;
}   t_pars;

typedef struct s_token
{
    char token[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];
} t_token;

// parsing.c
int parse(const char *map_file, t_rt *world);
void fillup_world(t_rt *world, const t_token *token, int i);

// //parsing_utils.c
void parse_rgb(t_tuple *color, const char *str);


# endif // PARSING_H
