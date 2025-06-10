#include "minirt.h"

// void mult_matrix_by_tuple(t_tuple *tuple, const t_matrix m, const t_tuple t)

int main()
{
	t_tuple tuple, t;
	t_matrix m;

	t.x = 1;
	t.y = 2;
	t.z = 3;
	t.w = 1;

	create_matrix(&m, 4);

	float data1[16] = {
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1};

	fillup_matrix(&m, data1);

	printf("Matrix m:\n");
	print_matrix(m);

	mult_matrix_by_tuple(&tuple, m, t);

	printf("tupl x: %f\n", tuple.x);
	printf("tupl y: %f\n", tuple.y);
	printf("tupl z: %f\n", tuple.z);
	printf("tupl w: %f\n", tuple.w);
	return 0;
}
