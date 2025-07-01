#include "minirt.h"

/* void get_plane_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point)
{
    t_tuple     object_normal_local;
    t_matrix    m_inverse;

    create_vector(&object_normal_local,0 , 1, 0);
    invert_matrix(&m_inverse, object->matrix);
    transpose_matrix(&m_inverse);
    mult_matrix_by_tuple(normal, m_inverse, object_normal_local);
    normal->w = 0;
    normalize_vector(normal);
} */

void    get_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point)
{
    t_tuple     object_point;
    t_tuple     object_normal;
    t_tuple     zero_point;
    t_matrix    m_inverse;

    invert_matrix(&m_inverse, object->matrix);
    mult_matrix_by_tuple(&object_point, m_inverse, world_point);
    create_point(&zero_point, 0, 0, 0);
    sub_tuples(&object_normal, object_point, zero_point);
    transpose_matrix(&m_inverse);
    mult_matrix_by_tuple (normal, m_inverse, object_normal);
    normal->w = 0;
    normalize_vector(normal);
}

void    reflect_vec(t_tuple *reflected, t_tuple vector_in, t_tuple normal)
{
    t_tuple temp;

    create_point(&temp, normal.x, normal.y, normal.z);
    mult_tuple(&temp, 2);
    mult_tuple(&temp, dot_product(vector_in, normal));
    sub_tuples(reflected, vector_in, temp);
}