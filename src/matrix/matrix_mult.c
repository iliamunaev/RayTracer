#include "minirt.h"

/**
 * @brief Computes the dot product between a matrix row and a tuple.
 *
 * Used internally to multiply a matrix by a tuple.
 *
 * @param row A 4-element row of the matrix.
 * @param t The tuple to multiply.
 * @return The scalar dot product result.
 */
static inline float	get_dot_product_row_tuple(const float row[NUM_MAT_COLS],
	const t_tuple t)
{
	return (row[0] * t.x + row[1] * t.y + row[2] * t.z + row[3] * t.w);
}

/**
 * @brief Computes the dot product between a matrix row and a matrix column.
 *
 * Used internally to multiply two matrices together.
 *
 * @param row A row from matrix A.
 * @param matrix Matrix B.
 * @param col Column index of matrix B.
 * @return The scalar dot product result.
 */
static float	get_dot_prod_r_c(const float row[NUM_MAT_COLS],
	const t_matrix matrix, int col)
{
	return (row[0] * matrix.rows[0].cols[col]
		+ row[1] * matrix.rows[1].cols[col]
		+ row[2] * matrix.rows[2].cols[col]
		+ row[3] * matrix.rows[3].cols[col]);
}

/**
 * @brief Multiplies two matrices and stores the result.
 *
 * Computes product_m = b × c and stores the result in `product_m`.
 * The operation respects matrix size and assumes both inputs are square.
 *
 * @param product_m Pointer to the output matrix.
 * @param b Left-hand side matrix.
 * @param c Right-hand side matrix.
 */
void	mult_matrices(t_matrix *product_m, const t_matrix b, t_matrix c)
{
	int	i;
	int	j;

	i = 0;
	product_m->size = b.size;
	while (i < product_m->size)
	{
		j = 0;
		while (j < product_m->size)
		{
			product_m->rows[i].cols[j] = get_dot_prod_r_c(b.rows[i].cols, c, j);
			j++;
		}
		i++;
	}
}

/**
 * @brief Multiplies a matrix by a tuple (vector or point).
 *
 * Computes product = matrix × tuple and stores the result in `product`.
 *
 * @param product Pointer to the output tuple.
 * @param matrix The matrix to apply.
 * @param tuple The input tuple.
 */
void	mult_matrix_by_tuple(t_tuple *product, const t_matrix matrix,
	const t_tuple tuple)
{
	product->x = get_dot_product_row_tuple(matrix.rows[0].cols, tuple);
	product->y = get_dot_product_row_tuple(matrix.rows[1].cols, tuple);
	product->z = get_dot_product_row_tuple(matrix.rows[2].cols, tuple);
	product->w = get_dot_product_row_tuple(matrix.rows[3].cols, tuple);
}
