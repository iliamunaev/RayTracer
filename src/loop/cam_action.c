#include "minirt.h"

/**
 * @brief Translate the camera position in X and Y axes using arrow keys.
 *
 * Moves the camera horizontally or vertically without any modifiers.
 *
 * @param world Pointer to the world context.
 * @param keydata The key input event.
 * @return true if the key triggered a translation, false otherwise.
 */
static bool	handle_cam_translate(t_rt *world, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_UP)
		world->cam.position.y += FACTOR_05;
	else if (keydata.key == MLX_KEY_DOWN)
		world->cam.position.y -= FACTOR_05;
	else if (keydata.key == MLX_KEY_LEFT)
		world->cam.position.x -= FACTOR_05;
	else if (keydata.key == MLX_KEY_RIGHT)
		world->cam.position.x += FACTOR_05;
	else
		return (false);
	return (true);
}

/**
 * @brief Adjust the camera field of view (FOV) using arrow keys + Control.
 *
 * LEFT + Control decreases FOV, RIGHT + Control increases FOV.
 *
 * @param world Pointer to the world context.
 * @param keydata The key input event.
 * @return true if the key triggered an FOV change, false otherwise.
 */
static bool	handle_cam_fov(t_rt *world, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.modifier & MLX_CONTROL))
		world->cam.fov -= FACTOR_05;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.modifier & MLX_CONTROL))
		world->cam.fov += FACTOR_05;
	else
		return (false);
	return (true);
}

/**
 * @brief Move the camera along the Z axis using UP/DOWN + Control.
 *
 * UP + Control moves camera forward, DOWN + Control moves it backward.
 *
 * @param world Pointer to the world context.
 * @param keydata The key input event.
 * @return true if the key triggered a depth change, false otherwise.
 */
static bool	handle_cam_depth(t_rt *world, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_UP && (keydata.modifier & MLX_CONTROL))
		world->cam.position.z += FACTOR_05;
	else if (keydata.key == MLX_KEY_DOWN && (keydata.modifier & MLX_CONTROL))
		world->cam.position.z -= FACTOR_05;
	else
		return (false);
	return (true);
}

/**
 * @brief Handle all camera-related key inputs (translation, depth, FOV).
 *
 * Delegates to the appropriate camera control handler based on input.
 *
 * @param world Pointer to the world context.
 * @param keydata The key input event.
 * @return true if any camera action was performed, false otherwise.
 */
bool	handle_cam(t_rt *world, mlx_key_data_t keydata)
{
	return (handle_cam_depth(world, keydata)
		|| handle_cam_fov(world, keydata)
		|| handle_cam_translate(world, keydata));
}
