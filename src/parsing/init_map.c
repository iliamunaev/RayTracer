#include "minirt.h"

t_pars *init_map_tmp(int num_el)
{
	t_pars *map_tmp;
	t_primitive *elements;

	map_tmp = malloc(sizeof(t_pars));
	if (!map_tmp)
		return (NULL);
	elements = ft_calloc(num_el, sizeof(t_primitive));
	if (!elements)
	{
		free(map_tmp);
		return (NULL);
	}
	map_tmp->element = elements;
	map_tmp->count = num_el;
	return (map_tmp);
}
