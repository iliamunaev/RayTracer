#include "minirt.h"

void    get_cylinder_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point)
{
    t_tuple     object_point;
    t_tuple     object_normal;
    float       distance;

    mult_matrix_by_tuple(&object_point, object->inv_matrix, world_point);
    distance = object_point.x * object_point.x + object_point.z * object_point.z;
    if (distance < 1 && object_point.y >= object->cylinder_max - EPSILON)
        create_vector(&object_normal, 0, 1, 0);
    else if (distance < 1 && object_point.y <= object->cylinder_min + EPSILON)
        create_vector(&object_normal, 0, -1, 0);
    else
        create_vector(&object_normal, object_point.x, 0, object_point.z);
    mult_matrix_by_tuple (normal, object->tran_matrix, object_normal);
    normal->w = 0;
    normalize_vector(normal);
}

void    get_normal_at(t_tuple *normal, t_primitive *object, t_tuple world_point)
{
    t_tuple     object_point;
    t_tuple     object_normal;
    t_tuple     zero_point;

    mult_matrix_by_tuple(&object_point, object->inv_matrix, world_point);
    create_point(&zero_point, 0, 0, 0);
    sub_tuples(&object_normal, object_point, zero_point);
    mult_matrix_by_tuple (normal, object->tran_matrix, object_normal);
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