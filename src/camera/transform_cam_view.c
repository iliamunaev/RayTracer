#include "minirt.h"

/**
 * @brief Build the orientation matrix from camera position,
 * target, and up vector.
 *
 * @param orientation Output matrix to store orientation.
 * @param from Camera position.
 * @param to Look-at target.
 * @param up Up direction vector.
 */
static void	build_camera_orientation(t_matrix *orientation,
	t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;
	t_tuple	true_up;

	sub_tuples(&forward, to, from);
	normalize_vector(&forward);
	if (fabsf(forward.x) < EPSILON && fabsf(forward.z) < EPSILON)
		create_vector(&up, 0, 0, -1);
	cross_product(&left, forward, up);
	normalize_vector(&left);
	cross_product(&true_up, left, forward);
	create_identity_matrix_4x4(orientation);
	orientation->rows[0].cols[0] = left.x;
	orientation->rows[0].cols[1] = left.y;
	orientation->rows[0].cols[2] = left.z;
	orientation->rows[1].cols[0] = true_up.x;
	orientation->rows[1].cols[1] = true_up.y;
	orientation->rows[1].cols[2] = true_up.z;
	orientation->rows[2].cols[0] = -forward.x;
	orientation->rows[2].cols[1] = -forward.y;
	orientation->rows[2].cols[2] = -forward.z;
}

/**
 * @brief Compute the camera's transformation matrix from world to view space.
 *
 * Builds orientation and translation matrices and combines them into the final
 * view transformation matrix (`rt->cam.matrix`).
 *
 * @param rt The world context containing the camera.
 * @param from Camera position.
 * @param to Look-at target.
 * @param up Up direction vector.
 */
void	transform_cam_view(t_rt *rt, t_tuple from, t_tuple to, t_tuple up)
{
	t_matrix	orientation;
	t_matrix	translation;
	t_tuple		neg_from;

	create_identity_matrix_4x4(&rt->cam.matrix);
	build_camera_orientation(&orientation, from, to, up);
	create_identity_matrix_4x4(&translation);
	create_vector(&neg_from, -from.x, -from.y, -from.z);
	translate(&translation, neg_from);
	mult_matrices(&rt->cam.matrix, orientation, translation);
	invert_matrix(&rt->cam.inv_matrix, rt->cam.matrix);
}
