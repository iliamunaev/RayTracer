#include "minirt.h"

/**
 * @brief Handle mouse movement and store cursor coordinates in the world.
 *
 * Updates `world->mouse_x` and `world->mouse_y` to track current mouse position.
 *
 * @param x The X coordinate of the mouse.
 * @param y The Y coordinate of the mouse.
 * @param param Pointer to the t_rt world structure.
 */
void	handle_mouse_move(double x, double y, void *param)
{
	t_rt	*world;

	world = (t_rt *)param;
	world->mouse_x = x;
	world->mouse_y = y;
}

/**
 * @brief Check if the input corresponds to a left mouse button click.
 *
 * @param button The mouse button that was interacted with.
 * @param action The type of action (press or release).
 * @return true if the action is a left-click press, false otherwise.
 */
static bool	is_left_mouse_click(mouse_key_t button, action_t action)
{
	return (action == MLX_PRESS && button == MLX_MOUSE_BUTTON_LEFT);
}

/**
 * @brief Select the object hit by a ray and update selection state.
 *
 * Sets `selected_primitive_index` in the world to the index of the object
 * intersected by the ray, or -1 if no match found.
 *
 * @param world The rendering world context.
 * @param ray Pointer to the ray with hit information.
 */
static void	select_hit_object(t_rt *world, t_ray *ray)
{
	int	i;

	i = 0;
	world->selected_primitive_index = -1;
	while (i < world->obj_counted)
	{
		if (&world->primitives_list[i] == ray->hit.object)
		{
			world->selected_primitive_index = i;
			break ;
		}
		i++;
	}
}

/**
 * @brief Handle mouse click events and update selected object if hit.
 *
 * When left mouse button is clicked, generates a ray from the camera
 * through the current mouse position and checks for intersections.
 * If an object is hit, it becomes the selected object.
 *
 * @param button The mouse button pressed.
 * @param action The action (press/release).
 * @param mods Modifier keys (unused).
 * @param param Pointer to the t_rt world structure.
 */
void	handle_mouse_click(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param)
{
	t_rt	*world;
	t_ray	ray;

	world = (t_rt *)param;
	(void)mods;
	if (!is_left_mouse_click(button, action))
		return ;
	ray_for_pixel(&ray, &world->cam, world->mouse_x, world->mouse_y);
	get_ray_intersections(&ray, world);
	get_hit(&ray);
	if (ray.is_hit)
		select_hit_object(world, &ray);
}
