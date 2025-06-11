#include "minirt.h"

int main(void)
{
    

    t_tuple result;

    // rotate
    t_matrix m_rotate;
    t_tuple rotation = {90, 0, 0, 1};
    rotate(&m_rotate, rotation);
    print_matrix(m_rotate);
    printf("\n");


    // scale
    t_matrix m_scale;
    t_tuple scaling = {5, 5, 5, 1};
    scale(&m_scale, scaling);
    print_matrix(m_scale);
    printf("\n");

    //translate
    t_matrix m_translate;
    t_tuple translateion = {10, 5, 7, 1};
    translate(&m_translate, translateion);
    print_matrix(m_translate);
    printf("\n");

    //multiply
    t_matrix m_temp;
    mult_matrices(&m_temp, m_scale, m_rotate);

    t_matrix m_res;
    create_identity_matrix_4x4(&m_res);
    mult_matrices(&m_res, m_translate, m_temp);

    print_matrix(m_res);
    printf("\n");

    t_tuple point = {1, 0, 1, 1}; 
    mult_matrix_by_tuple(&result, m_res, point);

     printf("\n new point is= x: %f, y: %f, z: %f, w: %f\n", result.x, result.y, result.z, result.w);
}