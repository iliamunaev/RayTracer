#include "minirt.h"

/**
 * @brief Transposes the matrix in place (swap rows with columns).
 *
 * Only the upper triangle is traversed to avoid double-swapping.
 *
 * @param matrix Pointer to the matrix to transpose.
 */
void transpose_matrix(t_matrix *matrix)
{
	int i;
	int j;

	i = 0;
	while (i < matrix->size)
	{
		j = i + 1;
		while (j < matrix->size)
		{
			swap_values(&matrix->rows[i].cols[j], &matrix->rows[j].cols[i]);
			j++;
		}
		i++;
	}
}

void invert_matrix(t_matrix *inverted, const t_matrix matrix)
{
	float det;
	float data[16];
	uint8_t x;
	uint8_t y;
	uint8_t i;

	// print_matrix(matrix);

	det = get_matrix_determinant(matrix);
	if (!is_invertible(det))
	{
		print_matrix(matrix);

		err("Error: matrix not invertible");
		exit(3);
		return;
	}
	i = 0;
	y = 0;
	while (y < matrix.size)
	{
		x = 0;
		while (x < matrix.size)
		{
			data[i] = get_matrix_cofactor(matrix, x, y);
			i++;
			x++;
		}
		y++;
	}
	create_matrix_4x4(inverted, data);
	transpose_matrix(inverted);
	dev_matrix_by_value(inverted, det);
}

void	translate(t_matrix *matrix, t_tuple translation)
{
	// create_identity_matrix_4x4(matrix);

	matrix->rows[0].cols[3] = translation.x;
	matrix->rows[1].cols[3] = translation.y;
	matrix->rows[2].cols[3] = translation.z;
}

void	scale(t_matrix *matrix, t_tuple scaling)
{
	create_identity_matrix_4x4(matrix);
	if (scaling.x == 0 && scaling.y == 0 && scaling.z == 0)
		return ;
	matrix->rows[0].cols[0] = scaling.x;
	matrix->rows[1].cols[1] = scaling.y;
	matrix->rows[2].cols[2] = scaling.z;
}


void	rotate_x(t_matrix *matrix, float degrees)
{
	float	radians;

	//radians = get_radians(degrees);
	radians = degrees;
	matrix->rows[1].cols[1] = cos(radians);
	matrix->rows[1].cols[2] = -sin(radians);
	matrix->rows[2].cols[1] = sin(radians);
	matrix->rows[2].cols[2] = cos(radians);	

}
void	rotate_y(t_matrix *matrix, float degrees)
{
	float	radians;

	radians = get_radians(degrees);
	matrix->rows[0].cols[0] = cos(radians);
	matrix->rows[0].cols[2] = sin(radians);
	matrix->rows[2].cols[0] = -sin(radians);
	matrix->rows[2].cols[2] = cos(radians);	

}
void	rotate_z(t_matrix *matrix, float degrees)
{
	float	radians;

	radians = get_radians(degrees);
	matrix->rows[0].cols[0] = cos(radians);
	matrix->rows[0].cols[1] = -sin(radians);
	matrix->rows[1].cols[0] = sin(radians);
	matrix->rows[1].cols[1] = cos(radians);	

}


void	rotate(t_matrix *matrix, t_tuple rotation)
{
	create_identity_matrix_4x4(matrix);
	if (rotation.x != 0)
		rotate_x(matrix, rotation.x);
	if (rotation.y != 0)
		rotate_y(matrix, rotation.y);
	if (rotation.z != 0)
		rotate_z(matrix, rotation.z);
}

void	transform(t_matrix *matrix, t_transform transform)
{
	
    t_matrix tmp_m;


    // create_identity_matrix_4x4(matrix);

    // Rotation
    rotate(&tmp_m, transform.rotate);
    mult_matrices(matrix, tmp_m, *matrix);

    // Scaling
    scale(&tmp_m, transform.scale);
    mult_matrices(matrix, tmp_m, *matrix);

    // Translation
    translate(&tmp_m, transform.translate);
    mult_matrices(matrix, tmp_m, *matrix);
}
