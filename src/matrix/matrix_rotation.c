#include "minirt.h"

/**
 * @brief Checks if a vector is already aligned with the up (Y) direction.
 *
 * Used to optimize rotation logic when no rotation is needed.
 *
 * @param dot The dot product between the up vector and the target vector.
 * @return true if vectors are aligned, false otherwise.
 */
static inline bool	is_up_aligned(float dot)
{
	return (fabs(dot - 1.0f) < EPSILON);
}

/**
 * @brief Checks if a vector is opposite to the up (Y) direction.
 *
 * Used to handle the 180° rotation case where axis-based rotation breaks down.
 *
 * @param dot The dot product between the up vector and the target vector.
 * @return true if vectors are opposite, false otherwise.
 */
static inline bool	is_down_aligned(float dot)
{
	return (fabs(dot + 1.0f) < EPSILON);
}

/**
 * @brief Sets a row of a 3x3 rotation matrix using axis-angle data.
 *
 * Used internally to build a full rotation matrix row-by-row from 
 * a normalized axis and precomputed cosine/sine/trig values.
 *
 * @param row Pointer to the row in the matrix to be filled.
 * @param data Array containing [cos(angle), sin(angle), 1 - cos(angle)].
 * @param axis Normalized axis of rotation.
 * @param row_idx Index of the row to compute (0, 1, or 2).
 */
static inline void	set_rotation_row(float *row, float data[],
	t_tuple axis, int row_idx)
{
	float	x;
	float	y;
	float	z;

	x = axis.x;
	y = axis.y;
	z = axis.z;
	if (row_idx == 0)
	{
		row[0] = data[2] * x * x + data[0];
		row[1] = data[2] * x * y - data[1] * z;
		row[2] = data[2] * x * z + data[1] * y;
	}
	else if (row_idx == 1)
	{
		row[0] = data[2] * x * y + data[1] * z;
		row[1] = data[2] * y * y + data[0];
		row[2] = data[2] * y * z - data[1] * x;
	}
	else if (row_idx == 2)
	{
		row[0] = data[2] * x * z - data[1] * y;
		row[1] = data[2] * y * z + data[1] * x;
		row[2] = data[2] * z * z + data[0];
	}
}

/**
 * @brief Fills a 4x4 matrix with values for a rotation around an arbitrary axis.
 *
 * Uses Rodrigues' rotation formula to populate the matrix.
 *
 * @param m Pointer to the matrix to fill.
 * @param axis The axis to rotate around (assumed normalized).
 * @param angle The rotation angle in radians.
 */
static inline void	fill_rotation_matrix(t_matrix *m, t_tuple axis, float angle)
{
	float	c;
	float	s;
	float	t;
	float	data[3];

	c = cosf(angle);
	s = sinf(angle);
	t = 1 - c;
	data[0] = c;
	data[1] = s;
	data[2] = t;
	create_identity_matrix_4x4(m);
	set_rotation_row(m->rows[0].cols, data, axis, 0);
	set_rotation_row(m->rows[1].cols, data, axis, 1);
	set_rotation_row(m->rows[2].cols, data, axis, 2);
}

/**
 * @brief Builds a rotation matrix that aligns the up (Y) vector 
 * with a target normal.
 *
 * This is used to orient an object to a new surface normal. Handles aligned and
 * 180-degree inverted cases explicitly, otherwise builds 
 * a proper rotation matrix.
 *
 * @param rotation_m Pointer to the matrix to store the result.
 * @param target_normal The target direction to align Y with.
 */
void	build_rotation_matrix_to_align_y(t_matrix *rotation_m,
	t_tuple target_normal)
{
	t_tuple	up;
	t_tuple	axis;
	float	dot;

	create_vector(&up, 0, 1, 0);
	dot = dot_product(up, target_normal);
	normalize_vector(&target_normal);
	if (is_up_aligned(dot))
		return (create_identity_matrix_4x4(rotation_m));
	if (is_down_aligned(dot))
	{
		create_identity_matrix_4x4(rotation_m);
		rotation_m->rows[1].cols[1] = -1;
		rotation_m->rows[2].cols[2] = -1;
		return ;
	}
	cross_product(&axis, up, target_normal);
	normalize_vector(&axis);
	fill_rotation_matrix(rotation_m, axis, acosf(dot));
}
