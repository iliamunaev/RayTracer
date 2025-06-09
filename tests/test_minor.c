#include "minirt.h"
/*

float	minor(const t_matrix matrix, uint8_t col, uint8_t row)
{

	float	minor;
	t_matrix *submatrix;

	create_identity_matrix_3x3(&submatrix);

	create_submatrix(matrix, &submatrix, col, row);

	minor = matrix_determinant_2x2(submatrix);

	return (minor);
}	
*/
int	main(void)
{
    t_matrix matrix;
    float m;

    // step 1

    create_identity_matrix_4x4(&matrix);

    float data[4] = {
        1, 2, 3, 4
    };

    fillup_matrix(&matrix, data);
    printf("Res\n");
    print_matrix(matrix);

    
    // step 2

    printf("\n");

    float d = determinant(matrix);

    printf("determinant: %f\n", d);

    return (0);
}
