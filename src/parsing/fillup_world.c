#include "minirt.h"

void parse_ambient(t_rt *world, const t_token *token, int i)
{

    t_primitive *p = &world->primitives_list[i];
	
    p->id = generate_id();
    p->type = 'A';
	p->ratio = ft_strtof(token->token[1]);
    parse_rgb(&p->color, token->token[2]);
}


void fillup_world(t_rt	*world, const t_token *token, int i)
{
    const char *id;

	id = token->token[0];

    if (ft_strcmp(id, "A") == 0)
        parse_ambient(world, token, i);
    // else if (ft_strcmp(id, "C") == 0)
    //     parse_camera(&p, token);
    // else if (ft_strcmp(id, "L") == 0)
    //     parse_light(&p, token);
    // else if (ft_strcmp(id, "sp") == 0)
    //     parse_sphere(&p, token);
    // else if (ft_strcmp(id, "pl") == 0)
    //     parse_plane(&p, token);
    // else if (ft_strcmp(id, "cy") == 0)
    //     parse_cylinder(&p, token);

	world->obj_counted++;
}

