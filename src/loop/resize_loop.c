#include "minirt.h"

/**
 * @brief Checks if the screen needs to be redrawn after a resize event.
 * Waits for a short delay (debounce) before triggering a re-render to avoid
 * excessive computation during rapid resizing like dragging the window.
 *
 * @param param pointer to the scene
 */
void	check_redraw(void *param)
{
	t_rt	*world;
	double	now;
	double	elapsed;

	world = (t_rt *)param;
	if (world->needs_resize_render)
	{
		now = mlx_get_time();
		elapsed = now - world->last_resize_time;
		if (elapsed > 0.5)
		{
			rebuild_camera(world);
			render(world);
			world->needs_resize_render = 0;
		}
	}
}

/**
 * @brief Handles screen resize events by adjusting the rendering buffer size
 * and flagging the scene for re-rendering.
 *
 * @param width new screen width
 * @param height new screen height
 * @param param pointer to the scene
 */
void	resize_screen(int32_t width, int32_t height, void *param)
{
	t_rt	*world;

	world = (t_rt *)param;
	mlx_resize_image(world->scene, width, height);
	world->last_resize_time = mlx_get_time();
	world->needs_resize_render = 1;
}
