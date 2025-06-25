#include "minirt.h"

/**
 * @brief Computes a view transformation matrix from world space to camera space.
 *
 * This function builds a matrix that transforms world coordinates such that the
 * camera is positioned at `from`, looking toward `to`, with the `up` vector defining
 * the vertical direction.
 *
 * @param rt    Pointer to the rendering context containing primitives.
 * @param from  The camera position (eye point).
 * @param to    The target point the camera looks at.
 * @param up    The world's up direction (approximate vertical orientation).
 */
void transform_view(t_rt *rt, t_tuple from, t_tuple to, t_tuple up)
{
    t_tuple forward;
    t_tuple left;
    t_tuple true_up;
    t_matrix orientation;
    t_matrix translation;

    sub_tuples(&forward, to, from);       // forward = to - from
    normalize_vector(&forward);           // normalize forward

    normalize_vector(&up);

    cross_product(&left, forward, up);    // left = forward × up

    cross_product(&true_up, left, forward); // true_up = left × forward

    create_identity_matrix_4x4(&orientation);
    orientation.rows[0].cols[0] = left.x;
    orientation.rows[0].cols[1] = left.y;
    orientation.rows[0].cols[2] = left.z;

    orientation.rows[1].cols[0] = true_up.x;
    orientation.rows[1].cols[1] = true_up.y;
    orientation.rows[1].cols[2] = true_up.z;

    orientation.rows[2].cols[0] = -forward.x;
    orientation.rows[2].cols[1] = -forward.y;
    orientation.rows[2].cols[2] = -forward.z;

    // Create a translation matrix that moves the world by -from
    create_identity_matrix_4x4(&translation);
    negate_tuple(&from);                 // negate from vector for translation
    translate(&translation, from);      // build translation matrix

    mult_matrices(&rt->primitives_list[0].matrix, orientation, translation);
}
