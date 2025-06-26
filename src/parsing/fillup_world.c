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
    create_color(&rt->amb.amb_component, rt->amb.color.r, rt->amb.color.g, rt->amb.color.b);
    mult_tuple(&rt->amb.amb_component, rt->amb.brightness);
    printf("r = %f, g= %f, b = %f\n", rt->amb.amb_component.r, rt->amb.amb_component.g, rt->amb.amb_component.b);
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
    parse_coordinates(&rt->cam.position, token->token[1]);
    parse_coordinates(&rt->cam.norm_vector, token->token[2]);
    rt->cam.fov = ft_strtof(token->token[3]);
    create_identity_matrix_4x4(&rt->cam.matrix);
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
    t_tuple scale_factor;
    t_matrix scale_m;
    t_matrix translate_m;

    p = &rt->primitives_list[j];
    p->id = generate_id();
    p->type[0] = 's';
    p->type[1] = 'p';
    p->type[2] = '\0';
    parse_coordinates(&p->position, token->token[1]);
    p->diameter = ft_strtof(token->token[2]);
    parse_rgb(&p->color, token->token[3]);
    create_identity_matrix_4x4(&p->matrix);
    create_point(&scale_factor, p->diameter ,p->diameter ,p->diameter);
    scale(&scale_m, scale_factor);
    mult_matrices(&p->matrix, scale_m, p->matrix);
    translate(&translate_m, p->position);
    mult_matrices(&p->matrix, translate_m, p->matrix);
    p->position.x = 0.0f;
    p->position.y = 0.0f;
    p->position.z = 0.0f;
    //something is wrong here still
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


