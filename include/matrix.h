#ifndef MATRIX_H
# define MATRIX_H

# include <stdbool.h>
# include <stdint.h>

# define NUM_MAT_COLS 4

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_tuple		t_tuple;
typedef struct s_transform	t_transform;

typedef struct s_row
{
	float	cols[NUM_MAT_COLS];
}	t_row;

typedef struct s_matrix
{
	t_row	rows[NUM_MAT_COLS];
	uint8_t	size;
}	t_matrix;

// matrix.c
void	create_identity_matrix_4x4(t_matrix *matrix);
void	create_matrix_4x4(t_matrix *matrix, const float data[]);

// matrix_determinant.c
float	get_matrix_determinant(const t_matrix m);
float	get_matrix_cofactor(const t_matrix matrix, uint8_t col, uint8_t row);

// matrix_div.c
void	dev_matrix_by_value(t_matrix *matrix, const float value);

// matrix_inverse.c
void	invert_matrix(t_matrix *inverted, const t_matrix matrix);

// matrix_mult.c
void	mult_matrices(t_matrix *a, const t_matrix b, t_matrix c);
void	mult_matrix_by_tuple(t_tuple *tuple, const t_matrix m, const t_tuple t);

// matrix_rotation.c
void	build_rotation_matrix_to_align_y(t_matrix *rotation_m,
			t_tuple target_normal);

// matrix_transform.c
void	translate(t_matrix *matrix, t_tuple translation);
void	scale(t_matrix *matrix, t_tuple scaling);
void	transform(t_matrix *matrix, t_transform transform);

// matrix_transpose.c
void	transpose_matrix(t_matrix *matrix);
void	transpose_return_new_matrix(t_matrix *transposed_matrix,
			t_matrix original_matrix);

// matrix_utils.c
bool	are_matrices_equal(const t_matrix a, const t_matrix b);
void	swap_values(float *a, float *b);
bool	is_invertible(const float det);

// For testing
void	print_matrix(const t_matrix matrix);

#endif // MATRIX_H
