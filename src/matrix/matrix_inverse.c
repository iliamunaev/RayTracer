#include "minirt.h"

/**
 * @brief Fill a flat array with cofactor values of a 4x4 matrix.
 *
 * This function computes the cofactor of each element in the matrix
 * and stores it sequentially into the provided data array.
 *
 * @param data A float array of size 16 to hold the cofactor values.
 * @param matrix The original matrix from which to compute cofactors.
 */
static inline void	fill_cofactor_data(float *data, const t_matrix matrix)
{
	uint8_t	x;
	uint8_t	y;
	uint8_t	i;

	i = 0;
	y = 0;
	while (y < matrix.size)
	{
		x = 0;
		while (x < matrix.size)
		{
			data[i++] = get_matrix_cofactor(matrix, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief Check if the matrix is invertible and store its determinant.
 *
 * Computes the determinant of the matrix and checks if it's invertible.
 * If not, prints an error message.
 *
 * @param matrix The matrix to check.
 * @param det A pointer to store the determinant value.
 * @return true if the matrix is invertible, false otherwise.
 */
static inline bool	check_invertibility_or_return(const t_matrix matrix,
	float *det)
{
	*det = get_matrix_determinant(matrix);
	if (!is_invertible(*det))
	{
		err("Error\nmatrix not invertible");
		return (false);
	}
	return (true);
}

/**
 * @brief Invert a 4x4 matrix and store the result.
 *
 * This function calculates the inverse of a given 4x4 matrix
 * and stores the result in the provided `inverted` pointer.
 * The function returns early and logs an error if the matrix
 * is not invertible.
 *
 * @param inverted Pointer to the matrix where the inverse will be stored.
 * @param matrix The matrix to invert.
 */
void	invert_matrix(t_matrix *inverted, const t_matrix matrix)
{
	float	det;
	float	data[16];

	if (!check_invertibility_or_return(matrix, &det))
		return ;
	fill_cofactor_data(data, matrix);
	create_matrix_4x4(inverted, data);
	transpose_matrix(inverted);
	dev_matrix_by_value(inverted, det);
}
