#include "minirt.h"

/**
 * @brief Initializes the MLX graphics context and creates the 
 * rendering image buffer. Exits the program if initialization 
 * or image creation fails.
 *
 * @param world pointer to the main rendering context (t_rt struct)
 */
void	setup_mlx(t_rt *world)
{
	world->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT", true);
	if (!world->mlx)
	{
		err("Error\nmlx_init failed");
		exit(EXIT_FAILURE);
	}
	world->scene = mlx_new_image(world->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!world->scene)
	{
		err("Error\nmlx_new_image failed");
		mlx_terminate(world->mlx);
		exit(EXIT_FAILURE);
	}
	ft_memset(world->scene->pixels, 255, world->scene->width
		* world->scene->height * BPP);
}
