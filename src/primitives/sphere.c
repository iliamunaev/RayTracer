#include "minirt.h"

uint8_t generate_id()
{
    static uint8_t current_id = 0;
    return (current_id++);
}

void    create_sphere(t_primitive *sphere, t_tuple position)
{
    sphere->id = generate_id();
    sphere->position.x = position.x;
    sphere->position.y = position.y;
    sphere->position.z = position.z;
    sphere->position.w = position.w;
}