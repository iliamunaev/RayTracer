#include "minirt.h"

void	test_fill_full_matrix(t_matrix *matrix, const float data[])
{
	uint8_t	x;
	uint8_t	y;
	uint8_t	i;

	i = 0;
	x = 0;

	while (x < matrix->size)
	{
		y = 0;
		while (y < matrix->size)
		{
			matrix->rows[x].cols[y] = data[i];
			i++;
			y++;
		}
		x++;
	}
}

int	main(void)
{
    t_matrix matrix;

    create_identity_matrix_4x4(&matrix);

    float data[16] = {
        -2, -8, 3, 5,
        -3, 1, 7, 3,
        1, 2,-9, 6,
        -6, 7, 7, -9
    };

    test_fill_full_matrix(&matrix, data);

    printf("Res\n");


    print_matrix(matrix);

    float d = determinant(matrix);
    printf("determinant: %f\n", d);


    return (0);
}
