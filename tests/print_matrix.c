#include "minirt.h"

void print_matrix(const t_matrix matrix)
{
    for (int i = 0; i < matrix.size; i++)
	{
        for (int j = 0; j < matrix.size; j++)
            printf(" %f", matrix.rows[i].cols[j]);
        printf("\n");
	}
}
