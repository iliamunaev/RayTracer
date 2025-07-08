#include "minirt.h"

/**
 * @brief Create a 4x4 matrix from a flat array of 16 float values.
 *
 * Fills the matrix row-by-row using values from the input array.
 * Assumes the array contains exactly 16 values (4x4).
 *
 * @param matrix Pointer to the t_matrix to populate.
 * @param data Array of 16 floats representing the matrix values.
 */
void	create_matrix_4x4(t_matrix *matrix, const float data[])
{
	uint8_t	x;
	uint8_t	y;
	int		i;

	x = 0;
	i = 0;
	matrix->size = 4;
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

/**
 * @brief Create a 4x4 identity matrix.
 *
 * Sets all diagonal elements to 1 and the rest to 0.
 * Useful as a starting point for transformations like rotation or translation.
 *
 * @param matrix Pointer to the t_matrix to initialize.
 */
void	create_identity_matrix_4x4(t_matrix *matrix)
{
	int	i;
	int	j;

	matrix->size = 4;
	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			if (i == j)
				matrix->rows[i].cols[j] = 1;
			else
				matrix->rows[i].cols[j] = 0;
			j++;
		}
		i++;
	}
}
