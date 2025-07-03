#include "minirt.h"

t_primitive *find_primitive(t_rt *world, t_type type)
{
    int i = 0;

    while (i < world->obj_counted)
    {
        if (world->primitives_list[i].type == type)
            return &world->primitives_list[i];
        i++;
    }
    err("Primitive not found");
    return NULL;
}
uint8_t generate_id()
{
    static uint8_t current_id = 0;
    return (current_id++);
}