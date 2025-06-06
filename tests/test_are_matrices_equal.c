# include "minirt.h"

int main()
{
	t_matrix a, b;

    create_matrix(&a, 4);
    create_matrix(&b, 4);

    float data1[16] = {
        1, 2, 3, 4,
        5.5, 6.5, 7.5, 8.5,
        9, 10, 11, 12,
        13.5, 14.5, 15.5, 16.5
    };

	float data2[16] = {
        1, 2, 3, 4,
        5.5, 6.5, 7.5, 8.5,
        9, 10, 11, 12,
        13.5, 14.5, 15.5, 16 // 16.5 in matrix a
    };

    fillup_matrix(&a, data1);
    fillup_matrix(&b, data2);

	int result = are_matrices_equal(a, b);

	printf("Equal == %i\n", result);
	return 0;
}
