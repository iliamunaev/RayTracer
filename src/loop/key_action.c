#include "minirt.h"

/**
 * @brief Check if a key is allowed in the current mode.
 *
 * Prevents unrelated keys from affecting the object when 
 * in a specific edit mode.
 * Allows movement, scaling, or rotation keys only in their respective modes.
 *
 * @param world Pointer to the world context.
 * @param key The keycode received from input.
 * @return true if the key is allowed in the current mode, false otherwise.
 */
static bool	is_allowed_key_in_mode(t_rt *world, int key)
{
	if (world->mode == MODE_SCALE)
		return (key == MLX_KEY_S || key == MLX_KEY_T
			|| key == MLX_KEY_C || key == MLX_KEY_R
			|| key == MLX_KEY_KP_ADD || key == MLX_KEY_KP_SUBTRACT);
	if (world->mode == MODE_TRANSLATE)
		return (key == MLX_KEY_S || key == MLX_KEY_T
			|| key == MLX_KEY_C || key == MLX_KEY_R
			|| key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT || key == MLX_KEY_UP
			|| key == MLX_KEY_DOWN);
	if (world->mode == MODE_ROTATE)
		return (key == MLX_KEY_S || key == MLX_KEY_T
			|| key == MLX_KEY_C || key == MLX_KEY_R
			|| key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT || key == MLX_KEY_UP
			|| key == MLX_KEY_DOWN);
	return (true);
}

/**
 * @brief Toggle a specific mode on or off for a selected object.
 *
 * If already in the given mode, switches back to MODE_NONE.
 * Otherwise, activates the given mode.
 *
 * @param world Pointer to the world context.
 * @param key The triggering key.
 * @param mode The mode to toggle.
 * @return true always (to indicate the key was handled).
 */
static bool	toggle_mode_if(t_rt *world, t_mode mode)
{
	if (world->mode == mode)
	{
		world->mode = MODE_NONE;
		print_mode(MODE_NONE, mode);
	}
	else
	{
		world->mode = mode;
		print_mode(mode, mode);
	}
	return (true);
}

/**
 * @brief Toggle camera control mode on or off.
 *
 * If already in camera mode, returns to MODE_NONE. 
 * Otherwise, activates camera control.
 *
 * @param world Pointer to the world context.
 * @return true always (to indicate the key was handled).
 */
static bool	toggle_cam_mode(t_rt *world)
{
	if (world->mode == MODE_CAM)
	{
		world->mode = MODE_NONE;
		print_mode(MODE_NONE, MODE_CAM);
	}
	else
	{
		world->mode = MODE_CAM;
		print_mode(MODE_CAM, MODE_CAM);
	}
	return (true);
}

/**
 * @brief Check if a mode toggle key was pressed and apply it.
 *
 * Only applies to CAM, SCALE, ROTATE, or TRANSLATE modes.
 * Mode toggles only work if an object is selected (for non-camera modes).
 *
 * @param world Pointer to the world context.
 * @param keydata The key input event.
 * @return true if mode was toggled, false otherwise.
 */
static bool	toggle_mode(t_rt *world, mlx_key_data_t keydata)
{
	int	i;

	i = world->selected_primitive_index;
	if (keydata.key == MLX_KEY_C)
		return (toggle_cam_mode(world));
	else if (keydata.key == MLX_KEY_S && i > -1)
		return (toggle_mode_if(world, MODE_SCALE));
	else if (keydata.key == MLX_KEY_R && i > -1)
		return (toggle_mode_if(world, MODE_ROTATE));
	else if (keydata.key == MLX_KEY_T && i > -1)
		return (toggle_mode_if(world, MODE_TRANSLATE));
	return (false);
}

/**
 * @brief Handle key input and perform mode toggling or object transformation.
 *
 * This function:
 * - Closes the app on Escape.
 * - Validates key use based on current mode.
 * - Toggles between edit modes or performs camera/object manipulation.
 *
 * @param world Pointer to the world context.
 * @param keydata The key input event.
 * @param moved Pointer to a bool flag set if the camera moved.
 * @param changed Pointer to a bool flag set if the object was modified.
 * @return true if any action was taken, false otherwise.
 */
bool	key_action(t_rt *world, mlx_key_data_t keydata,
	bool *moved, bool *changed)
{
	int	i;

	i = world->selected_primitive_index;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		printf("Exiting app...\n");
		mlx_close_window(world->mlx);
		return (false);
	}
	if (!is_allowed_key_in_mode(world, keydata.key))
		return (false);
	if (toggle_mode(world, keydata))
		return (true);
	if (world->mode != MODE_NONE && world->mode == MODE_CAM)
	{
		*moved = handle_cam(world, keydata);
		return (true);
	}
	if (world->mode != MODE_NONE && i >= 0 && i < world->obj_counted)
	{
		*changed = handle_object(world, keydata);
		return (true);
	}
	return (false);
}
