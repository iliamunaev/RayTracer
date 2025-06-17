#include "minirt.h"

static void copy_data(t_primitive *dst, const t_primitive *src)
{
	dst->id = generate_id();
	dst->char_id = src->char_id;
	dst->position = src->position;
	dst->norm_vector = src->norm_vector;
	dst->ratio = src->ratio;
	dst->brightness = src->brightness;
	dst->color = src->color;
	dst->diameter = src->diameter;
	dst->height = src->height;
	dst->fov = src->fov;
	dst->matrix = src->matrix;
}

void fillup_world(t_rt *world, const t_pars *map_tmp)
{
	int i;

    world->mlx = NULL;
	world->scene = NULL;
	world->obj_counted = map_tmp->count;
    i = 0;
	while (i < map_tmp->count)
	{
		copy_data(&world->primitives_list[i], &map_tmp->element[i]);
		i++;
	}
}
