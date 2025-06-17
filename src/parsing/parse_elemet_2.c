#include "minirt.h"

void parse_light(t_primitive *prim, char **tokens)
{
    create_identity_matrix_4x4(&prim->matrix);
}

void parse_camera(t_primitive *prim, char **tokens)
{
    create_identity_matrix_4x4(&prim->matrix);
}

void parse_ambient(t_primitive *prim, char **tokens)
{
    create_identity_matrix_4x4(&prim->matrix);
}
