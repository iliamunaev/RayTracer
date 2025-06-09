#include "minirt.h"
#include <assert.h>

void test_transpose_matrix(void)
{
	t_matrix m, expected;


	float data[4] = {
		1, 2, 3, 4
	};

	create_identity_matrix(&m, 4);

	fillup_matrix(&m, data);

	printf("\n");

	print_matrix(m);

	transpose_matrix(&m);
	printf("\n");


	print_matrix(m);
}

int main()
{
	test_transpose_matrix();
	return 0;
}
