#include "minirt.h"

uint8_t generate_id()
{
    static uint8_t current_id = 0;
    return (current_id++);
}

void    create_sphere(t_sphere *sphere)
{
    sphere->id = generate_id();
}