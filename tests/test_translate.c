#include "minirt.h"

int main(void)
{
    t_tuple point = {-3, 4, 5, 1};
    t_tuple result;
    t_tuple translation = {5, -3, 2, 1};
    t_matrix matrix;
    t_matrix inverted_matrix;

    translate(&matrix, translation);
    invert_matrix(&inverted_matrix, matrix);
    print_matrix(inverted_matrix);
     printf("\n");
    mult_matrix_by_tuple(&result, inverted_matrix, point);
    printf("\n translated point is= x: %f, y: %f, z: %f, w: %f\n", result.x, result.y, result.z, result.w);
}