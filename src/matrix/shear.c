#include "minirt.h"

static void move_xy(t_matrix *matrix, float val)
{
	matrix->rows[0].cols[1] += val;
}

static void move_xz(t_matrix *matrix, float val)
{
	matrix->rows[0].cols[2] += val;
}

static void move_yx(t_matrix *matrix, float val)
{
	matrix->rows[1].cols[0] += val;
}

static void move_yz(t_matrix *matrix, float val)
{
	matrix->rows[2].cols[1] += val;
}

static void move_zx(t_matrix *matrix, float val)
{
	matrix->rows[0].cols[2] += val;
}

static void move_zy(t_matrix *matrix, float val)
{
	matrix->rows[1].cols[2] += val;
}

void	shear(t_matrix *matrix, t_shear shearing)
{
    create_identity_matrix_4x4(matrix);
	move_xy(matrix, shearing.xy); 
	move_xz(matrix, shearing.xz);
	move_yx(matrix, shearing.yx);
	move_yz(matrix, shearing.yz);
	move_zx(matrix, shearing.zx);
	move_zy(matrix, shearing.zy);
}