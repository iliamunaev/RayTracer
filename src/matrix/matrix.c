#include "minirt.h"

/**
 * @brief Initializes a matrix with a given number of active rows.
 *
 * This function sets the `size` field of the matrix, which determines how many
 * rows will be used in operations like filling or comparison.
 *
 * @param matrix Pointer to the matrix to initialize.
 * @param size Number of rows to mark as used (should not exceed NUM_MAT_COLS).
 */
void	create_matrix(t_matrix *matrix, uint8_t size)
{
	matrix->size = size;
}

/**
 * @brief Fills the matrix with values from a flat array (row-major order).
 *
 * Assumes that the matrix has already been initialized using `create_matrix()`.
 * Copies `matrix->size * NUM_MAT_COLS` elements from the input array into
 * the matrix row by row.
 *
 * @param matrix Pointer to the matrix to fill.
 * @param data Flat array of float values to populate the matrix.
 */
void	fillup_matrix(t_matrix *matrix, const float data[])
{
	uint8_t	x;
	uint8_t	y;
	uint8_t	i;
	uint8_t size;

	size = matrix->size;
	i = 0;
	x = 0;

	while (x < matrix->size)
	{
		y = 0;
		while (y < matrix->size)
		{
			matrix->rows[x].cols[y] = data[i];
			y++;
			i++;
		}
		x++;
	}
}

/**
 * @brief Compares two matrices for equality.
 *
 * This function checks that both matrices have the same number of rows
 * (`size`) and that each corresponding element is equal using `is_equal()`.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @return true if matrices are equal; false otherwise.
 */
bool	are_matrices_equal(const t_matrix a, const t_matrix b)
{
	int i;
	int j;

	i = 0;
	while(i < a.size)
	{
		j = 0;
		while (j < b.size)
		{
			if(!is_equal(a.rows[i].cols[j], b.rows[i].cols[j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	create_identity_matrix(t_matrix *matrix)
{
	int	i;
	int	j;
	create_matrix(matrix, 4);

	i = 0;
	while(i < matrix->size)
	{
		j = 0;
		while(j < matrix->size)
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
