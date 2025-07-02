#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdint.h>

#define NUM_MAT_COLS 4

typedef struct s_tuple t_tuple;
typedef struct s_transform t_transform;

typedef struct s_row
{
	float cols[NUM_MAT_COLS];
} t_row;

typedef struct s_matrix
{
	t_row rows[NUM_MAT_COLS];
	uint8_t size;
} t_matrix;

typedef struct s_shear
{
	float	xy;
	float	xz;
	float	yx;
	float	yz;
	float	zx;
	float	zy;
} t_shear;

// matrix.c
void	create_identity_matrix_4x4(t_matrix *matrix);
// void	create_identity_matrix_3x3(t_matrix *matrix);
void create_matrix_4x4(t_matrix *matrix, const float data[]);
void fillup_matrix(t_matrix *matrix, const float data[]);
bool are_matrices_equal(const t_matrix a, const t_matrix b);
void create_submatrix(const t_matrix matrix, t_matrix *submatrix, uint8_t col, uint8_t row);

// math_matrix.c
void mult_matrices(t_matrix *a,const t_matrix b, t_matrix c);
void mult_matrix_by_tuple(t_tuple *tuple, const t_matrix m, const t_tuple t);
void dev_matrix_by_value(t_matrix *matrix, const float value);
float get_matrix_determinant_2x2(t_matrix m);
float get_matrix_minor(const t_matrix matrix, uint8_t col, uint8_t row);
float get_matrix_cofactor(const t_matrix matrix, uint8_t col, uint8_t row);
float get_matrix_determinant(const t_matrix m);

// matrix_manipulations.c
void transpose_matrix(t_matrix *matrix);
void transpose_return_new_matrix(t_matrix *transposed_matrix, t_matrix original_matrix);
void invert_matrix(t_matrix *inverted, const t_matrix matrix);
void	translate(t_matrix *matrix, t_tuple translation);
void	scale(t_matrix *matrix, t_tuple scaling);
void	rotate(t_matrix *matrix, t_tuple rotation);
void	rotate_x(t_matrix *matrix, float degrees);
void	rotate_y(t_matrix *matrix, float degrees);
void	rotate_z(t_matrix *matrix, float degrees);
void	shear(t_matrix *matrix, t_shear shearing);
void	transform(t_matrix *matrix, t_transform transform);

// matrix_utils.c
void swap_values(float *a, float *b);
bool is_invertible(const float det);
void	fill_data_arr(float *data, const float x, const float y, const float z, const float w);


// For testing
// Delete on production
void print_matrix(const t_matrix matrix);

#endif // MATRIX_H
