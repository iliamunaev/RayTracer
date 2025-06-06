#include "minirt.h"

// COMPILATION
// cc -I ../include -I ../lib/MLX42/include  print_matrix.c ../src/matrix/*
void print_matrix(const t_matrix matrix)
{
    for (int i = 0; i < matrix.size; i++)
	{
        for (int j = 0; j < matrix.size; j++)
            printf(" %f", matrix.rows[i].cols[j]);
        printf("\n");
	}
}

int main()
{
    t_matrix matrix;
    create_matrix(&matrix, 4);

    float data[16] = {
        1, 2, 3, 4,
        5.5, 6.5, 7.5, 8.5,
        9, 10, 11, 12,
        13.5, 14.5, 15.5, 16.5
    };

    fillup_matrix(&matrix, data);
    print_matrix(matrix);

}
