#include "minirt.h"

int main(void)
{
    t_matrix matrix;
    float m;

    // step 1

    create_identity_matrix_4x4(&matrix);

    float data[4] = {
        1, 2, 3, 4};

    fillup_matrix(&matrix, data);
    printf("Res\n");
    print_matrix(matrix);

    // step 2

    printf("\n");

    float d = get_matrix_determinant(matrix);

    printf("determinant: %f\n", d);

    return (0);
}
