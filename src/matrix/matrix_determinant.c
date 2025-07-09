#include "minirt.h"

/**
 * @brief Computes the determinant of a 2x2 matrix.
 *
 * Used as the base case for recursive determinant calculation.
 *
 * @param matrix A 2x2 matrix.
 * @return The scalar determinant of the matrix.
 */
static inline float	get_matrix_determinant_2x2(const t_matrix matrix)
{
	float	a;
	float	b;

	a = matrix.rows[0].cols[0] * matrix.rows[1].cols[1];
	b = matrix.rows[0].cols[1] * matrix.rows[1].cols[0];
	return (a - b);
}

/**
 * @brief Computes the minor determinant of a matrix
 * excluding one row and column.
 *
 * This is used in cofactor and determinant calculations.
 *
 * @param matrix Input matrix.
 * @param col Column index to exclude.
 * @param row Row index to exclude.
 * @return The determinant of the submatrix.
 */
static inline float	get_matrix_minor(const t_matrix matrix,
	uint8_t col, uint8_t row)
{
	t_matrix	submatrix;
	uint8_t		i;
	uint8_t		j;
	uint8_t		sub_i;
	uint8_t		sub_j;

	submatrix.size = matrix.size - 1;
	sub_i = 0;
	i = 0;
	while (i < matrix.size)
	{
		sub_j = 0;
		j = 0;
		while (j < matrix.size)
		{
			if (i != row && j != col)
				submatrix.rows[sub_i].cols[sub_j++] = matrix.rows[i].cols[j];
			j++;
		}
		if (i != row)
			sub_i++;
		i++;
	}
	return (get_matrix_determinant(submatrix));
}

/**
 * @brief Computes the determinant of a square matrix of any size.
 *
 * Recursively expands by minors. For size 2, uses optimized 2x2 logic.
 *
 * @param matrix The matrix whose determinant is to be calculated.
 * @return The determinant value.
 */
float	get_matrix_determinant(const t_matrix matrix)
{
	float	det;
	float	cof;
	uint8_t	col;

	det = 0.0f;
	col = 0;
	if (matrix.size == 2)
		return (get_matrix_determinant_2x2(matrix));
	while (col < matrix.size)
	{
		cof = get_matrix_cofactor(matrix, col, 0);
		det += matrix.rows[0].cols[col] * cof;
		col++;
	}
	return (det);
}

/**
 * @brief Computes the cofactor of an element in a matrix.
 *
 * Uses minor determinant and applies sign based on (row + col) parity.
 *
 * @param matrix Input matrix.
 * @param col Column index of the element.
 * @param row Row index of the element.
 * @return The signed cofactor value.
 */
float	get_matrix_cofactor(const t_matrix matrix, uint8_t col, uint8_t row)
{
	float	minor;
	float	cofactor;

	minor = get_matrix_minor(matrix, col, row);
	if ((col + row) % 2 != 0)
		cofactor = -minor;
	else
		cofactor = minor;
	return (cofactor);
}
