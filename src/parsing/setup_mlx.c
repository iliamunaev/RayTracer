#include "minirt.h"

void	setup_mlx(t_rt *world)
{
	world->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT", true);
	if (!world->mlx)
	{
		err("Error: mlx_init failed");
		exit(EXIT_FAILURE);
	}
	world->scene = mlx_new_image(world->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!world->scene)
	{
		err("Error: mlx_new_image failed");
		mlx_terminate(world->mlx);
		exit(EXIT_FAILURE);
	}
	ft_memset(world->scene->pixels, 255, world->scene->width
		* world->scene->height * BPP);
}
