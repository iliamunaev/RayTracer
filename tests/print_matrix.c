#include "minirt.h"

/**
 * @brief Prints the contents of a matrix to standard output.
 *
 * Each row of the matrix is printed on a new line. Columns are separated by spaces.
 * The number of rows printed is determined by `matrix.size`, and each row is
 * assumed to have `NUM_MAT_COLS` columns.
 *
 * @param matrix The matrix to print.
 */
void print_matrix(const t_matrix matrix)
{
    for (int i = 0; i < matrix.size; i++)
	{
        for (int j = 0; j < matrix.size; j++)
            printf(" %f", matrix.rows[i].cols[j]);
        printf("\n");
	}
}
