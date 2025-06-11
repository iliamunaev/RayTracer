#include "minirt.h"

int main(void)
{
    t_tuple vector = {-1, 1, 1, 1};
    t_tuple result;
    t_tuple scaling = {2, 3, 4, 1};
    t_matrix matrix;
    t_matrix inverted_matrix;

    scale(&matrix, scaling);
   // invert_matrix(&inverted_matrix, matrix);
   // print_matrix(inverted_matrix);
     printf("\n");
    mult_matrix_by_tuple(&result, matrix, vector);
    printf("\n scaled point is= x: %f, y: %f, z: %f, w: %f\n", result.x, result.y, result.z, result.w);
}