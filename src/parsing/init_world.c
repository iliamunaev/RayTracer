#include "minirt.h"

void    init_world(t_rt *world)
{
    int i;

    i = 0;
    ft_memset(world, 0, sizeof(t_rt));
    while (i < MAX_PRIMITIVES)
    {
        ft_memset(&world->primitives_list[i], 0, sizeof(t_primitive));
        i++;
    }
    
}