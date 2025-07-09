#include "minirt.h"

/**
 * @brief Transpose a square matrix in-place.
 *
 * Swaps elements symmetrically across the diagonal. Only the upper triangle
 * is traversed to avoid unnecessary swaps.
 *
 * @param matrix Pointer to the matrix to transpose.
 */
void	transpose_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

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

/**
 * @brief Transpose a matrix and store the result in a new matrix.
 *
 * Copies the transposed version of `original_matrix` into `transp_matrix`.
 *
 * @param transp_matrix Pointer to the matrix where the result will be stored.
 * @param original_matrix The matrix to transpose.
 */
void	transpose_return_new_matrix(t_matrix *transp_matrix,
	t_matrix original_matrix)
{
	int	i;
	int	j;

	transp_matrix->size = original_matrix.size;
	i = 0;
	while (i < original_matrix.size)
	{
		j = 0;
		while (j < original_matrix.size)
		{
			transp_matrix->rows[j].cols[i] = original_matrix.rows[i].cols[j];
			j++;
		}
		i++;
	}
}
