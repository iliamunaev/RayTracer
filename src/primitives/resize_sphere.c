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
    // t_tuple scale_vec = { radius, radius, radius, 0.0f };
    t_tuple scale_vec = { radius, radius, radius, 0.0f };


    t_matrix scale_m, trans_m, temp;

/*     scale(&scale_m,     scale_vec);
    printf("scale = \n");
    print_matrix(scale_m); */

    printf("\nmatrix = \n");
    print_matrix(p->matrix);

    //translate(&trans_m, p->position);
    t_transform transformer;

    create_point(&transformer.rotate, p->norm_vector.x, p->norm_vector.y, p->norm_vector.z);
    create_point(&transformer.scale, radius, radius, radius);
    create_point(&transformer.translate, p->position.x, p->position.y, p->position.z);
    transform(&p->matrix, transformer);

    //mult_matrices(&temp, scale_m, trans_m);
    //mult_matrices(&p->matrix, scale_m, p->matrix);
    printf("\nmatrix new = \n");
    print_matrix(p->matrix);
    invert_matrix(&p->inv_matrix, p->matrix);
    transpose_return_new_matrix(&p->tran_matrix, p->inv_matrix);
}


