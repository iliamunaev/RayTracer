#include "minirt.h"

int main(void)
{
    t_tuple point = {0, 1, 0, 1};
    t_tuple result;
    t_tuple rotation = {0, 0, 90, 0};

    t_matrix matrix;
    t_matrix inverted_matrix;

    rotate(&matrix, rotation);
    //invert_matrix(&inverted_matrix, matrix);
   // print_matrix(inverted_matrix);
     printf("\n");
    mult_matrix_by_tuple(&result, matrix, point);
    printf("\n roated point is= x: %f, y: %f, z: %f, w: %f\n", result.x, result.y, result.z, result.w);
}