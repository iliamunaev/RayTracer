#include "minirt.h"

static float	dot_row_col(const float row[NUM_MAT_COLS], const t_matrix m, int col)
{
	return (row[0] * m.rows[0].cols[col] +
	       row[1] * m.rows[1].cols[col] +
	       row[2] * m.rows[2].cols[col] +
	       row[3] * m.rows[3].cols[col]);
}

void	mult_matxs(t_matrix *a, const t_matrix b, const t_matrix c)
{
	int	i;
	int j;

	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (j < a->size)
		{
			a->rows[i].cols[j] = dot_row_col(b.rows[i].cols, c, j);
			j++;
		}
		i++;
	}
}

static float	dot_row_tuple(const float row[NUM_MAT_COLS], const t_tuple t)
{
	return (row[0] * t.x + row[1] * t.y + row[2] * t.z + row[3] * t.w);
}

void mult_matx_tuple(t_tuple *tuple, const t_matrix m, const t_tuple t)
{
	tuple->x = dot_row_tuple(m.rows[0].cols, t);
	tuple->y = dot_row_tuple(m.rows[1].cols, t);
	tuple->z = dot_row_tuple(m.rows[2].cols, t);
	tuple->w = dot_row_tuple(m.rows[3].cols, t);
}

