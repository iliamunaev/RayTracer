#include "minirt.h"

void free_map_tmp(t_pars *map_tmp)
{
	if (!map_tmp)
		return ;
	free(map_tmp->element);
	free(map_tmp);
}

uint8_t count_elements(const char *map)
{
    uint8_t count;

    count = 0;
    while (*map)
    {
        while (*map && ft_isspace(*map) && *map != '\n')
            map++;
        if (*map && *map != '\n')
            count++;
        while (*map && *map != '\n')
            map++;
        if (*map == '\n')
            map++;
    }
    return (count);
}
