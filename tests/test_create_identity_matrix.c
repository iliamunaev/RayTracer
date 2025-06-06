#include "minirt.h"
#include <assert.h>

void test_identity_matrix(void)
{
	t_matrix m;
	create_identity_matrix(&m);

	// Check diagonals == 1.0 and others == 0.0
	for (int i = 0; i < m.size; i++)
	{
		for (int j = 0; j < m.size; j++)
		{
			if (i == j)
				assert(is_equal(m.rows[i].cols[j], 1.0f));
			else
				assert(is_equal(m.rows[i].cols[j], 0.0f));
		}
	}
	print_matrix(m);
	printf("Test passed!\n");
}

int main()
{
	test_identity_matrix();
	return 0;
}
