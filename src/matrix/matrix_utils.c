#include "minirt.h"

/**
 * @brief Compares two matrices for element-wise equality.
 *
 * Each corresponding element in matrices `a` and `b` is 
 * compared using `is_equal()`.
 * Matrices must be the same size to be considered equal.
 *
 * @param a First matrix to compare.
 * @param b Second matrix to compare.
 * @return true if all elements match; false otherwise.
 */
bool	are_matrices_equal(const t_matrix a, const t_matrix b)
{
	int	i;
	int	j;

	if (a.size != b.size)
		return (false);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			if (!is_equal(a.rows[i].cols[j], b.rows[i].cols[j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * @brief Swap the values of two float variables.
 *
 * @param a Pointer to the first float.
 * @param b Pointer to the second float.
 */
void	swap_values(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Check if a matrix (or value) is invertible based on its determinant.
 *
 * A matrix is invertible if its determinant is not approximately zero,
 * using a defined `EPSILON` tolerance to account for floating-point precision.
 *
 * @param det The determinant value to check.
 * @return true if invertible; false otherwise.
 */
bool	is_invertible(const float det)
{
	return (fabs(det) > EPSILON);
}
