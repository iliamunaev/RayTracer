#include "minirt.h"
/*
typedef struct s_amb
{
    float       brightness;
    t_tuple     color; 
    t_matrix    matrix;
}   t_amb;
   */
void parse_ambient(t_rt *rt, t_token *token)
{

    rt->amb.brightness = ft_strtof(token->token[1]);
    parse_rgb(&rt->amb.color, token->token[2]);
    create_identity_matrix_4x4(&rt->amb.matrix);  
}

/*
typedef struct s_cam
{
    t_tuple     position;
    t_tuple     norm_vector;
    float       fov;
    t_matrix    matrix;
}   t_cam;
*/
void parse_camera(t_rt *rt, t_token *token)
{
    t_tuple up = {0, 1, 0, 0};
    t_tuple to;

  
    parse_coordinates(&rt->cam.position, token->token[1]);    
    parse_coordinates(&rt->cam.norm_vector, token->token[2]);

    normalize_vector(&rt->cam.norm_vector);
    add_tuples(&to, rt->cam.position, rt->cam.norm_vector);

    rt->cam.fov = ft_strtof(token->token[3]);
    rt->cam.pix_size = get_pixel_size(rt);
    rt->cam.half_width = get_half_width(rt);
    rt->cam.half_height = get_half_height(rt);
    rt->cam.half_view = get_half_view(rt);
    
    transform_cam_view(rt, rt->cam.position, to, up);
}

/*
typedef struct s_light
{
    t_tuple     position;
    float       brightness;
    t_tuple     color; 
    t_matrix    matrix;
}   t_light;
*/
void parse_light(t_rt *rt, t_token *token)
{

    parse_coordinates(&rt->light.position, token->token[1]);
    rt->light.brightness = ft_strtof(token->token[2]);
    parse_rgb(&rt->light.color, token->token[3]);
    create_identity_matrix_4x4(&rt->light.matrix);    
}

void parse_sphere(t_rt *rt, t_token *token, int j)
{
    t_primitive *p;

    p = &rt->primitives_list[j];
    p->id = generate_id();
    p->type[0] = 's';
    p->type[1] = 'p';
    p->type[2] = '\0';
    parse_coordinates(&p->position, token->token[1]);
    p->diameter = ft_strtof(token->token[2]);
    parse_rgb(&p->color, token->token[3]);
    create_identity_matrix_4x4(&p->matrix);

}

void parse_plane(t_rt *rt, t_token *token, int j)
{
    t_primitive *p;

    p = &rt->primitives_list[j];
    p->id = generate_id();
    p->type[0] = 'p';
    p->type[1] = 'l';
    p->type[2] = '\0';
    parse_coordinates(&p->position, token->token[1]);
    parse_coordinates(&p->norm_vector, token->token[2]);
    parse_rgb(&p->color, token->token[3]);
    create_identity_matrix_4x4(&p->matrix);    
}

void parse_cylinder(t_rt *rt, t_token *token, int j)
{
    t_primitive *p;

    p = &rt->primitives_list[j];
    p->id = generate_id();
    p->type[0] = 'c';
    p->type[1] = 'y';
    p->type[2] = '\0';
    parse_coordinates(&p->position, token->token[1]);
    parse_coordinates(&p->norm_vector, token->token[2]);
    p->diameter = ft_strtof(token->token[3]);
    p->height = ft_strtof(token->token[4]);
    parse_rgb(&p->color, token->token[5]);
    create_identity_matrix_4x4(&p->matrix);    
}

void fillup_world(t_rt *rt, t_token *token, int j)
{
    char *id = token->token[0];

    if (ft_strcmp(id, "A") == 0)
        parse_ambient(rt, token);
    else if (ft_strcmp(id, "C") == 0)
        parse_camera(rt, token);
    else if (ft_strcmp(id, "L") == 0)
        parse_light(rt, token);
    else if (ft_strcmp(id, "sp") == 0)
        parse_sphere(rt, token, j);
    else if (ft_strcmp(id, "pl") == 0)
        parse_plane(rt, token, j);
    else if (ft_strcmp(id, "cy") == 0)
        parse_cylinder(rt, token, j);
    else
        err("Unknown identifier");
}


