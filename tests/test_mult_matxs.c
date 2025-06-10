#include "minirt.h"

int main()
{
	t_matrix a, b, c;

	create_matrix(&a, 4);
	create_matrix(&b, 4);
	create_matrix(&c, 4);

	float data1[16] = {
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4};

	float data2[16] = {
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4};

	fillup_matrix(&b, data1);
	fillup_matrix(&c, data2);

	printf("Matrix b:\n");
	print_matrix(b);
	printf("Matrix c:\n");
	print_matrix(c);

	mult_matrices(&a, b, c);

	printf("Result Matrix a:\n");
	print_matrix(a);
	return 0;
}
