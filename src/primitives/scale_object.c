#include "minirt.h"

void scale_object(t_rt *world, float factor)
{
    int idx = world->selected_primitive_index;

    if (idx < 0 || idx >= world->obj_counted)
        return;

    t_primitive *p = &world->primitives_list[idx];

    if (p->type == PLANE)
        return ;

    /* new diameter with clamping */
    float new_diam = p->diameter * factor;

    if (new_diam < 0.10f)
        new_diam = 0.10f;
    if (new_diam > 5.00f)
        new_diam = 5.00f;

    p->diameter = new_diam;
    /* rebuild matrix: same recipe  (T * S) */
    float radius = p->diameter / 2.0f;
    t_tuple scale_vec = { radius, radius, radius, 0.0f };
    t_matrix scale_m, trans_m, temp;

    printf("\nmatrix = \n");
    print_matrix(p->matrix);

    t_transform transformer;
    create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
    create_point(&transformer.scale, radius, radius, radius);
    create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
    transform(&p->matrix, transformer);

    printf("\nmatrix new = \n");
    print_matrix(p->matrix);
    invert_matrix(&p->inv_matrix, p->matrix);
    transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}


void translate_object(t_rt *world, float factor_x, float factor_y, float factor_z)
{
    int idx = world->selected_primitive_index;

    if (idx < 0 || idx >= world->obj_counted)
        return;

    t_primitive *p = &world->primitives_list[idx];

    float new_pos_x = p->position.x + factor_x;
    float new_pos_y = p->position.y + factor_y;
    float new_pos_z = p->position.z + factor_z;



    p->position.x = new_pos_x;
    p->position.y = new_pos_y;
    p->position.z = new_pos_z;

    float radius = p->diameter / 2.0f;

    printf("\nmatrix = \n");
    print_matrix(p->matrix);

    t_transform transformer;
    create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
    create_point(&transformer.scale, radius, radius, radius);
    create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
    transform(&p->matrix, transformer);

    printf("\nmatrix new = \n");
    print_matrix(p->matrix);
    invert_matrix(&p->inv_matrix, p->matrix);
    transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}