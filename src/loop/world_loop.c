#include "minirt.h"

/**
 * @brief Translate the selected object based on arrow key input.
 *
 * If Control is held with UP/DOWN, translates along the Z axis.
 * Otherwise translates along the X or Y axis.
 *
 * @param world The rendering world context.
 * @param keydata The input key event from MLX.
 */
static void	handle_translate(t_rt *world, mlx_key_data_t keydata)
{
	float	x;
	float	y;
	float	z;

	x = 0;
	y = 0;
	z = 0;
	if (keydata.key == MLX_KEY_UP && (keydata.modifier & MLX_CONTROL))
		z = 0.1;
	else if (keydata.key == MLX_KEY_DOWN && (keydata.modifier & MLX_CONTROL))
		z = -0.1;
	else if (keydata.key == MLX_KEY_RIGHT)
		x = 0.1;
	else if (keydata.key == MLX_KEY_LEFT)
		x = -0.1;
	else if (keydata.key == MLX_KEY_DOWN)
		y = -0.1;
	else if (keydata.key == MLX_KEY_UP)
		y = 0.1;
	translate_object(world, x, y, z);
}

/**
 * @brief Rotate the selected object based on arrow key input.
 *
 * Applies incremental rotation along X, Y, or Z axis.
 * Holding Control allows Z-axis rotation.
 *
 * @param world The rendering world context.
 * @param keydata The input key event from MLX.
 */
static void	handle_rotate(t_rt *world, mlx_key_data_t keydata)
{
	float	x;
	float	y;
	float	z;

	x = 0;
	y = 0;
	z = 0;
	if (keydata.key == MLX_KEY_RIGHT)
		x = -FACTOR_01;
	else if (keydata.key == MLX_KEY_LEFT)
		x = FACTOR_01;
	else if (keydata.key == MLX_KEY_DOWN)
		y = FACTOR_01;
	else if (keydata.key == MLX_KEY_UP)
		y = -FACTOR_01;
	else if (keydata.key == MLX_KEY_UP && (keydata.modifier & MLX_CONTROL))
		z = -FACTOR_01 * 2;
	else if (keydata.key == MLX_KEY_DOWN && (keydata.modifier & MLX_CONTROL))
		z = FACTOR_01 * 2;
	rotate_object(world, x, y, z);
}

/**
 * @brief Scale the selected object using keypad add/subtract.
 *
 * Increase or decrease scale by a fixed factor.
 *
 * @param world The rendering world context.
 * @param keydata The input key event from MLX.
 */
static void	handle_scale(t_rt *world, mlx_key_data_t keydata)
{
	float	factor;

	factor = 0;
	if (keydata.key == MLX_KEY_KP_ADD)
		factor = FACTOR_INC;
	else if (keydata.key == MLX_KEY_KP_SUBTRACT)
		factor = FACTOR_DEC;
	scale_object(world, factor);
}

/**
 * @brief Handle object manipulation based on current world mode.
 *
 * Delegates to camera, scale, translate, or rotate handlers.
 *
 * @param world The rendering world context.
 * @param keydata The input key event from MLX.
 * @return true if the event was handled, false otherwise.
 */
bool	handle_object(t_rt *world, mlx_key_data_t keydata)
{
	if (world->mode == MODE_CAM)
		return (handle_cam(world, keydata));
	if (world->mode == MODE_SCALE)
		handle_scale(world, keydata);
	else if (world->mode == MODE_TRANSLATE)
		handle_translate(world, keydata);
	else if (world->mode == MODE_ROTATE)
		handle_rotate(world, keydata);
	else
		return (false);
	return (true);
}

/**
 * @brief Main MLX loop hook for processing key input.
 *
 * Handles key presses and triggers camera or object updates.
 * Re-renders the scene if needed.
 *
 * @param keydata The key event data from MLX.
 * @param param Pointer to the t_rt world context.
 */
void	world_loop(mlx_key_data_t keydata, void *param)
{
	t_rt	*world;
	bool	moved;
	bool	changed;

	world = (t_rt *)param;
	moved = false;
	changed = false;
	if (keydata.action != MLX_PRESS)
		return ;
	if (key_action(world, keydata, &moved, &changed))
	{
		if (moved)
			rebuild_camera(world);
		if (moved || changed)
			render(world);
	}
}
