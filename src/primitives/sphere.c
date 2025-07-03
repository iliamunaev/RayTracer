#include "minirt.h"



void    create_sphere(t_primitive *sphere, t_tuple position)
{
    sphere->id = generate_id();
    sphere->position.x = position.x;
    sphere->position.y = position.y;
    sphere->position.z = position.z;
    sphere->position.w = position.w;
    create_identity_matrix_4x4(&sphere->matrix);
}