#include "minirt.h"

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
bool are_matrices_equal(const t_matrix a, const t_matrix b)
{
	int i;
	int j;

	if(a.size != b.size)
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

void swap_values(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
bool is_invertible(const float det)
{
	return (fabs(det) > EPSILON);
}


