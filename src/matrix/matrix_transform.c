#include "minirt.h"

/**
 * @brief Creates a translation matrix using a translation vector.
 *
 * The resulting matrix will move points in space by the x, y, and z
 * values of the given translation vector.
 *
 * @param matrix Pointer to the matrix to initialize.
 * @param translation The translation vector.
 */
void	translate(t_matrix *matrix, t_tuple translation)
{
	create_identity_matrix_4x4(matrix);
	matrix->rows[0].cols[3] = translation.x;
	matrix->rows[1].cols[3] = translation.y;
	matrix->rows[2].cols[3] = translation.z;
}

/**
 * @brief Creates a scaling matrix using a scaling vector.
 *
 * The resulting matrix will scale points in space along the x, y, and z axes.
 * If all scaling components are zero, the operation is skipped.
 *
 * @param matrix Pointer to the matrix to initialize.
 * @param scaling The scaling factors along each axis.
 */
void	scale(t_matrix *matrix, t_tuple scaling)
{
	create_identity_matrix_4x4(matrix);
	if (scaling.x == 0 && scaling.y == 0 && scaling.z == 0)
		return ;
	matrix->rows[0].cols[0] = scaling.x;
	matrix->rows[1].cols[1] = scaling.y;
	matrix->rows[2].cols[2] = scaling.z;
}

/**
 * @brief Applies a full transformation (rotation, scaling, translation).
 *
 * Constructs and applies a transformation matrix in the order:
 * rotate → scale → translate. This function uses temporary matrix storage
 * and applies each step by matrix multiplication.
 *
 * @param matrix Pointer to the output transformation matrix.
 * @param transform The transformation struct containing rotate,
 * scale, translate.
 */
void	transform(t_matrix *matrix, t_transform transform)
{
	t_matrix	tmp_m;

	create_identity_matrix_4x4(matrix);
	if (fabsf(transform.rotate.x) > EPSILON
		|| fabsf(transform.rotate.y) > EPSILON
		|| fabsf(transform.rotate.z) > EPSILON)
	{
		build_rotation_matrix_to_align_y(&tmp_m, transform.rotate);
		mult_matrices(matrix, tmp_m, *matrix);
	}
	scale(&tmp_m, transform.scale);
	mult_matrices(matrix, tmp_m, *matrix);
	translate(&tmp_m, transform.translate);
	mult_matrices(matrix, tmp_m, *matrix);
}
