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
