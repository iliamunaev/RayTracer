#include "minirt.h"
#include <assert.h>

void test_transpose_matrix(void)
{
	t_matrix m, expected;

	create_matrix(&m, 4);
	create_matrix(&expected, 4);

	float data[16] = {
		0, 9, 3, 0,
		9, 8, 0, 8,
		1, 8, 5, 3,
		0, 0, 5, 8
	};

	float expected_data[16] = {
		0, 9, 1, 0,
		9, 8, 8, 0,
		3, 0, 5, 5,
		0, 8, 3, 8
	};

	fillup_matrix(&m, data);
	fillup_matrix(&expected, expected_data);

	transpose_matrix(&m);

	assert(are_matrices_equal(m, expected));
	printf("test_transpose_matrix passed.\n");
}

int main()
{
	test_transpose_matrix();
	return 0;
}
