#include "minirt.h"


int	main(void)
{
    t_matrix matrix;

    // step 1

    create_identity_matrix_4x4(&matrix);

    float data[4] = {
        0, 1, 2, 3
    };

    fillup_matrix(&matrix, data);

    printf("Res\n");


    print_matrix(matrix);

    
    // step 2

    printf("\n");

    t_matrix submatrix;

    create_identity_matrix_4x4(&submatrix);

    create_submatrix(matrix, &submatrix, 0, 3);

    print_matrix(submatrix);

    return (0);
}
