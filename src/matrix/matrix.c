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

// data[16] has always 16 values
void	fillup_matrix(t_matrix *matrix, const float data[])
{
	uint8_t	x;
	uint8_t	y;
	int i;

	x = 0;
	i = 0;

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

void	create_identity_matrix_4x4(t_matrix *matrix)
{
	int	i;
	int	j;

	matrix->size = 4;

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

// void	create_identity_matrix_3x3(t_matrix *matrix)
// {
// 	int	i;
// 	int	j;

// 	matrix->size = 3;

// 	i = 0;
// 	while(i < matrix->size)
// 	{
// 		j = 0;
// 		while(j < matrix->size)
// 		{
// 			if (i == j)
// 				matrix->rows[i].cols[j] = 1;
// 			else
// 				matrix->rows[i].cols[j] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	create_matrix_4x4(t_matrix *matrix, const float data[])
{
	create_identity_matrix_4x4(matrix);
	fillup_matrix(matrix, data);
}