#include "minirt.h"
#include "matrix.h"

static float get_dot_product_row_col(const float row[NUM_MAT_COLS], const t_matrix matrix, int col)
{
	return (row[0] * matrix.rows[0].cols[col] +
			row[1] * matrix.rows[1].cols[col] +
			row[2] * matrix.rows[2].cols[col] +
			row[3] * matrix.rows[3].cols[col]);
}

void mult_matrices(t_matrix *product_m, const t_matrix b, const t_matrix c)
{
	int i;
	int j;

	i = 0;
	product_m->size = b.size;
	while (i < product_m->size)
	{
		j = 0;
		while (j < product_m->size)
		{
			product_m->rows[i].cols[j] = get_dot_product_row_col(b.rows[i].cols, c, j);
			j++;
		}
		i++;
	}
}

static float get_dot_product_row_tuple(const float row[NUM_MAT_COLS], const t_tuple t)
{
	return (row[0] * t.x + row[1] * t.y + row[2] * t.z + row[3] * t.w);
}

void mult_matrix_by_tuple(t_tuple *product, const t_matrix matrix, const t_tuple tuple)
{
	product->x = get_dot_product_row_tuple(matrix.rows[0].cols, tuple);
	printf("product->x %f\n",product->x);

	product->y = get_dot_product_row_tuple(matrix.rows[1].cols, tuple);
	printf("product->y %f\n",product->y);

	product->z = get_dot_product_row_tuple(matrix.rows[2].cols, tuple);
	printf("product->z %f\n",product->z);

	product->w = get_dot_product_row_tuple(matrix.rows[3].cols, tuple);
	printf("product->w %f\n",product->w);

}

float get_matrix_determinant_2x2(const t_matrix matrix)
{
	float a;
	float b;

	a = matrix.rows[0].cols[0] * matrix.rows[1].cols[1];
	b = matrix.rows[0].cols[1] * matrix.rows[1].cols[0];
	return (a - b);
}

void create_submatrix(const t_matrix matrix, t_matrix *submatrix, uint8_t col, uint8_t row)
{
	uint8_t x;
	uint8_t y;
	uint8_t a;
	uint8_t b;

	submatrix->size--;
	y = 0;
	b = 0;
	while (y < matrix.size)
	{
		x = 0;
		a = 0;
		if (y == row)
			y++;
		while (x < matrix.size && y < matrix.size)
		{
			if (x == col)
				x++;
			submatrix->rows[a].cols[b] = matrix.rows[y].cols[x];
			x++;
			a++;
		}
		y++;
		b++;
	}
}

float get_matrix_minor(const t_matrix matrix, uint8_t col, uint8_t row)
{
	t_matrix submatrix;
	uint8_t sub_i;
	uint8_t sub_j;
	uint8_t i;
	uint8_t j;

	sub_i = 0;
	sub_j = 0;
	submatrix.size = matrix.size - 1;
	i = 0;
	while (i < matrix.size)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		sub_j = 0;
		j = 0;
		while (j < matrix.size)
		{
			if (j == col)
			{
				j++;
				continue;
			}
			submatrix.rows[sub_i].cols[sub_j] = matrix.rows[i].cols[j];
			sub_j++;
			j++;
		}
		sub_i++;
		i++;
	}
	return (get_matrix_determinant(submatrix));
}

float get_matrix_determinant(const t_matrix matrix)
{
	float det;
	float cof;
	uint8_t col;

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

float get_matrix_cofactor(const t_matrix matrix, uint8_t col, uint8_t row)
{
	float minor;
	float cofactor;

	minor = get_matrix_minor(matrix, col, row);
	if ((col + row) % 2 != 0)
		cofactor = -minor;
	else
		cofactor = minor;
	return (cofactor);
}

void dev_matrix_by_value(t_matrix *matrix, const float value)
{
	uint8_t i;
	uint8_t j;

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
