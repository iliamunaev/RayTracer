#include "minirt.h"


void resize_object(t_rt *world, float factor)
{
    int idx = world->selected_primitive_index;
    if (idx < 0 || idx >= world->obj_counted)
        return;

    t_primitive *p = &world->primitives_list[idx];
    if (p->type != SPHERE)
        return;

    /* new diameter with clamping */
    float new_diam = p->diameter * factor;
    if (new_diam < 0.10f) new_diam = 0.10f;
    if (new_diam > 5.00f) new_diam = 5.00f;
    p->diameter = new_diam;

    /* rebuild matrix: same recipe  (T * S) */
    float radius = p->diameter / 2.0f;
    t_tuple scale_vec = { radius, radius, radius, 0.0f };

    t_matrix scale_m, trans_m;
    scale(&scale_m,     scale_vec);
    translate(&trans_m, p->position);

    mult_matrices(&p->matrix, trans_m, scale_m);
    invert_matrix(&p->inv_matrix, p->matrix);
}
