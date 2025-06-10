#include "minirt.h"

int main(void)
{
    t_tuple vector = {1, 2, 3, 1};
    t_tuple result;
    t_tuple translation = {-1, 1, 3, 1};
    t_matrix matrix;

    translate(&matrix, translation);
    print_matrix(matrix);
     printf("\n");
    mult_matrix_by_tuple(&result, matrix, vector);
    printf("\n translated point is= x: %f, y: %f, z: %f, w: %f\n", result.x, result.y, result.z, result.w);
}