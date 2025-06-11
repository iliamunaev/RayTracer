#include "minirt.h"

int main(void)
{
    t_tuple point = {2, 3, 4, 1};
    t_shear shearing = {1, 0, 0, 0, 0, 0};
    t_tuple result;

    t_matrix matrix;
    // t_matrix inverted_matrix;

    shear(&matrix, shearing);

    //invert_matrix(&inverted_matrix, matrix);
   // print_matrix(inverted_matrix);

    printf("\n");
    
    mult_matrix_by_tuple(&result, matrix, point);
    //print_matrix(result);
     printf("\n sheared point is= x: %f, y: %f, z: %f, w: %f\n", result.x, result.y, result.z, result.w);
}