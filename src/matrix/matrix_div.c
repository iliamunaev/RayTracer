#include "minirt.h"

/**
 * @brief Divides all elements of a matrix by a scalar value.
 *
 * This operation is performed in-place, modifying the original matrix.
 *
 * @param matrix Pointer to the matrix to be divided.
 * @param value The scalar value by which to divide each element.
 */
void	dev_matrix_by_value(t_matrix *matrix, const float value)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			matrix->rows[i].cols[j] /= value;
			j++;
		}
		i++;
	}
}
