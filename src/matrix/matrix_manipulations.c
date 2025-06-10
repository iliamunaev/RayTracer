#include "minirt.h"

/**
 * @brief Transposes the matrix in place (swap rows with columns).
 *
 * Only the upper triangle is traversed to avoid double-swapping.
 *
 * @param matrix Pointer to the matrix to transpose.
 */
void transpose_matrix(t_matrix *matrix)
{
	int i;
	int j;

	i = 0;
	while (i < matrix->size)
	{
		j = i + 1;
		while (j < matrix->size)
		{
			swap_values(&matrix->rows[i].cols[j], &matrix->rows[j].cols[i]);
			j++;
		}
		i++;
	}
}

void invert_matrix(t_matrix *inverted, const t_matrix matrix)
{
	float det;
	float data[16];
	uint8_t x;
	uint8_t y;
	uint8_t i;

	det = get_matrix_determinant(matrix);
	if (!is_invertible(det))
	{
		err("Error: matrix not invertible");
		return;
	}
	i = 0;
	y = 0;
	while (y < matrix.size)
	{
		x = 0;
		while (x < matrix.size)
		{
			data[i] = get_matrix_cofactor(matrix, x, y);
			i++;
			x++;
		}
		y++;
	}
	create_matrix_4x4(inverted, data);
	transpose_matrix(inverted);
	dev_matrix_by_value(inverted, det);
}


void	translate(t_matrix *matrix, t_tuple translation)
{
	create_identity_matrix_4x4(matrix);
	matrix->rows[0].cols[3] = translation.x;
	matrix->rows[1].cols[3] = translation.y;
	matrix->rows[2].cols[3] = translation.z;
}
