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

    create_identity_matrix_3x3(&matrix);

    float data[3] = {
        1, 2, 3
    };

    fillup_matrix(&matrix, data);

    printf("Res\n");


    print_matrix(matrix);

    
    // step 2

    printf("\n");

    m = minor(matrix,1, 2);


    printf("minor: %f\n", m);

    m = cofactor(matrix, 1, 2);

    printf("cofactor: %f\n", m);

    return (0);
}
