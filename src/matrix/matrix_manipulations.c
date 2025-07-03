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

void transpose_return_new_matrix(t_matrix *transposed_matrix, t_matrix original_matrix)
{
    int i = 0;
    int j;

    transposed_matrix->size = original_matrix.size;

    while (i < original_matrix.size)
    {
        j = 0;
        while (j < original_matrix.size)
        {
            transposed_matrix->rows[j].cols[i] = original_matrix.rows[i].cols[j];
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
	create_identity_matrix_4x4(matrix);

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

	//radians = get_radians(degrees);
	matrix->rows[0].cols[0] = cos(radians);
	matrix->rows[0].cols[2] = sin(radians);
	matrix->rows[2].cols[0] = -sin(radians);
	matrix->rows[2].cols[2] = cos(radians);	

}
void	rotate_z(t_matrix *matrix, float degrees)
{
	float	radians;

	//radians = get_radians(degrees);
	matrix->rows[0].cols[0] = cos(radians);
	matrix->rows[0].cols[1] = -sin(radians);
	matrix->rows[1].cols[0] = sin(radians);
	matrix->rows[1].cols[1] = cos(radians);	

}


void build_rotation_matrix(t_matrix *rotation_m, t_tuple normal)
{
    t_tuple tangent;
    t_tuple bitangent;
	t_tuple up;

    //normalize_vector(&normal);
    create_identity_matrix_4x4(rotation_m);
	create_vector(&up, 0, 1, 0);
	if (fabs(dot_product(normal, up)) > 0.999f)
    {
        return ;
    }
    cross_product(&tangent, up, normal);
    normalize_vector(&tangent);
    cross_product(&bitangent, normal, tangent);
    rotation_m->rows[0].cols[0] = tangent.x;
    rotation_m->rows[0].cols[1] = tangent.y;
    rotation_m->rows[0].cols[2] = tangent.z;
    rotation_m->rows[1].cols[0] = bitangent.x;
    rotation_m->rows[1].cols[1] = bitangent.y;
    rotation_m->rows[1].cols[2] = bitangent.z;
    rotation_m->rows[2].cols[0] = normal.x;
    rotation_m->rows[2].cols[1] = normal.y;
    rotation_m->rows[2].cols[2] = normal.z;
}

void build_rotation_matrix_to_align_y(t_matrix *rotation_m, t_tuple target_normal)
{
    t_tuple up;
    t_tuple axis;
    float angle;
    float c, s, t;
    float x, y, z;

    create_vector(&up, 0, 1, 0);
    normalize_vector(&target_normal);
    float dot = dot_product(up, target_normal);
    if (fabs(dot - 1.0f) < EPSILON)
    {
        create_identity_matrix_4x4(rotation_m);
        return;
    }
    else if (fabs(dot + 1.0f) < EPSILON)
    {
        create_identity_matrix_4x4(rotation_m);
        rotation_m->rows[1].cols[1] = -1;
        rotation_m->rows[2].cols[2] = -1;
        return;
    }
    cross_product(&axis, up, target_normal);
    normalize_vector(&axis);
    angle = acosf(dot);
    x = axis.x;
    y = axis.y;
    z = axis.z;
    c = cosf(angle);
    s = sinf(angle);
    t = 1 - c;
    create_identity_matrix_4x4(rotation_m);
    rotation_m->rows[0].cols[0] = t*x*x + c;
    rotation_m->rows[0].cols[1] = t*x*y - s*z;
    rotation_m->rows[0].cols[2] = t*x*z + s*y;
    rotation_m->rows[1].cols[0] = t*x*y + s*z;
    rotation_m->rows[1].cols[1] = t*y*y + c;
    rotation_m->rows[1].cols[2] = t*y*z - s*x;
    rotation_m->rows[2].cols[0] = t*x*z - s*y;
    rotation_m->rows[2].cols[1] = t*y*z + s*x;
    rotation_m->rows[2].cols[2] = t*z*z + c;
}


void	transform(t_matrix *matrix, t_transform transform)
{
	
    t_matrix tmp_m;

	create_identity_matrix_4x4(matrix);
	// Rotation
	if (fabsf(transform.rotate.x) > EPSILON ||
    	fabsf(transform.rotate.y) > EPSILON ||
    	fabsf(transform.rotate.z) > EPSILON)
	{
		build_rotation_matrix_to_align_y(&tmp_m, transform.rotate);
    	mult_matrices(matrix, tmp_m, *matrix);
	}

	// Scaling
    scale(&tmp_m, transform.scale);
    mult_matrices(matrix, tmp_m, *matrix);

    // Translation
    translate(&tmp_m, transform.translate);
    mult_matrices(matrix, tmp_m, *matrix);


}
