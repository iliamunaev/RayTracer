#include "minirt.h"

void	create_matrix(t_matrix *matrix, uint8_t size)
{
	matrix->size = size;
}

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
