#include "minirt.h"

void parse_ambient(t_rt *world, t_token *token, int i)
{
    t_primitive *p;

    p = &world->primitives_list[i];
    p->id = generate_id();
    p->type[0] = 'A';
    p->type[1] = '\0';
    p->type[2] = '\0';
    p->ratio = ft_strtof(token->token[1]);
    parse_rgb(&p->color, token->token[2]);
}

void parse_sphere(t_rt *world, t_token *token, int i)
{
    t_primitive *p;

    p = &world->primitives_list[i];

    p->id = generate_id();
    p->type[0] = 's';
    p->type[1] = 'p';
    p->type[2] = '\0';

    parse_coordinates(&p->position, token->token[1]);

    p->diameter = ft_strtof(token->token[2]);

    parse_rgb(&p->color, token->token[3]);
}



void parse_camera(t_rt *world, t_token *token, int i)
{
    t_primitive *p;

    p = &world->primitives_list[i];

    p->id = generate_id();
    p->type[0] = 'C';
    p->type[1] = '\0';
    p->type[2] = '\0';

    parse_coordinates(&p->position, token->token[1]);
    parse_coordinates(&p->norm_vector, token->token[2]);
    p->fov = ft_strtof(token->token[3]);
}

void parse_light(t_rt *world, t_token *token, int i)
{
    t_primitive *p;

    p = &world->primitives_list[i];

    p->id = generate_id();
    p->type[0] = 'L';
    p->type[1] = '\0';
    p->type[2] = '\0';

    parse_coordinates(&p->position, token->token[1]);
    p->ratio = ft_strtof(token->token[2]);
    parse_rgb(&p->color, token->token[3]);
}

void parse_plane(t_rt *world, t_token *token, int i)
{
    t_primitive *p;

    p = &world->primitives_list[i];

    p->id = generate_id();
    p->type[0] = 'p';
    p->type[1] = 'l';
    p->type[2] = '\0';

    parse_coordinates(&p->position, token->token[1]);
    parse_coordinates(&p->norm_vector, token->token[2]);
    parse_rgb(&p->color, token->token[3]);
}

/*
  cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255

∗ identifier: cy
∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗ the cylinder diameter: 14.2
∗ the cylinder height: 21.42
∗ R,G,B colors in range [0,255]: 10, 0, 255
*/
void parse_cylinder(t_rt *world, t_token *token, int i)
{
    t_primitive *p;

    p = &world->primitives_list[i];

    p->id = generate_id();
    p->type[0] = 'c';
    p->type[1] = 'y';
    p->type[2] = '\0';

    parse_coordinates(&p->position, token->token[1]);
    parse_coordinates(&p->norm_vector, token->token[2]);
    p->diameter = ft_strtof(token->token[3]);
    p->height = ft_strtof(token->token[4]);
    parse_rgb(&p->color, token->token[5]);
}

void fillup_world(t_rt *world, t_token *token, int i)
{
    char *id;

    // memset world

    id = token->token[0];

    if (ft_strcmp(id, "A") == 0)
        parse_ambient(world, token, i);
    else if (ft_strcmp(id, "C") == 0)
        parse_camera(world, token, i);
    else if (ft_strcmp(id, "L") == 0)
        parse_light(world, token, i);
    else if (ft_strcmp(id, "sp") == 0)
        parse_sphere(world, token, i);
    else if (ft_strcmp(id, "pl") == 0)
        parse_plane(world, token, i);
    else if (ft_strcmp(id, "cy") == 0)
        parse_cylinder(world, token, i);
    world->obj_counted++;
}
