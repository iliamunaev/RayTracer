#include "minirt.h"

/*
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
    transpose_matrix(&object.matrix);
    mult_matrix_by_tuple (&normal, object.matrix, object_normal);
    normal->w = 0;
    normalize_vector(normal);
}
    */

    int main(void)
    {
        t_primitive sphere;
        t_tuple sp_position = {0, 0, 0, 1};
        create_sphere(&sphere, sp_position);
        
       /*  t_transform transf_val = {
        {0, 0, M_PI/5, 1},
        {1, 0.5, 1, 1},
        {0, 0, 0, 1}
        }; */
        t_transform transf_val = {
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 1, 0, 1}
        };
        transform(&sphere.matrix, transf_val);

        t_tuple normal;
        t_tuple world_point = {0, 1.70711, -0.70711, 1};
        create_vector(&normal, 0, 0, 0);
        get_normal_at(&normal, sphere, world_point);
        printf("normal v = x: %f, y: %f, z: %f, w: %f", normal.x, normal.y, normal.z, normal.w);
    }