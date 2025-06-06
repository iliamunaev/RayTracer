#ifndef MATRIX_H
# define MATRIX_H

# include <stdbool.h>
# include <stdint.h>

# define NUM_MAT_COLS 4

typedef struct s_tuple t_tuple;

typedef struct s_row
{
	float	cols[NUM_MAT_COLS];
}	t_row;

typedef struct s_matrix
{
	t_row	rows[NUM_MAT_COLS];
	uint8_t	size;
}	t_matrix;


// matrix
void	create_matrix(t_matrix *matrix, uint8_t size);
void	create_identity_matrix(t_matrix *matrix);
void	fillup_matrix(t_matrix *matrix, const float data[]);
bool	are_matrices_equal(const t_matrix a, const t_matrix b);

// math_matrix
void	mult_matxs(t_matrix *a, const t_matrix b, const t_matrix c);
void	mult_matx_tuple(t_tuple *tuple, const t_matrix m, const t_tuple t);


// For testing
// Delete on production
void print_matrix(const t_matrix matrix);

# endif // MATRIX_H

