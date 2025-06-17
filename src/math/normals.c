#include "minirt.h"

void    get_normal_at(t_tuple *normal, t_primitive object, t_tuple world_point)
{
    t_tuple     object_point;
    t_tuple     object_normal;
    t_tuple     zero_point;
    t_matrix    m_inverse;

    invert_matrix(&m_inverse, object.matrix);
    mult_matrix_by_tuple(&object_point, m_inverse, world_point);
    create_point(&zero_point, 0, 0, 0);
    sub_tuples(&object_normal, object_point, zero_point);
    transpose_matrix(&m_inverse);
    mult_matrix_by_tuple (normal, m_inverse, object_normal);
    normal->w = 0;
    normalize_vector(normal);
}