#include "minirt.h"

t_primitive *find_primitive(t_rt *world, char *type)
{
    int i = 0;

    while (i < world->obj_counted)
    {
        if (ft_strcmp(world->primitives_list[i].type, type) == 0)
            return (&world->primitives_list[i]);
        i++;
    }
    err("Primitive not found");
    return (NULL);
}