#include "minirt.h"

int	main(int argc, char **argv)
{

    t_rt world;
    uint32_t  w = 0;
    uint32_t  h = 0;

	if (!validate_input_args(argc, argv))
		return (EXIT_FAILURE);
        
	if (parse(argv[1], &world) == EXIT_FAILURE)
    {
        err("Error");
		return (EXIT_FAILURE);
    }

    world.mlx = mlx_init(512, 512, "Test", true);
    if (!world.mlx)
    {
        err("Error");
        exit(EXIT_FAILURE);
    }

    world.scene = mlx_new_image(world.mlx, 512, 512);

    // Set the channels of each pixel in our image to the maximum byte value of 255.
    //ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);
    while (h < 512)
    {
        w = 0;
        while (w < 512)
        {
            mlx_put_pixel(world.scene, w, h, 0x58c0dc);
            w++;
        }
        h++;
    }

    //IF YOU WANT TO SEE THE PROJECTILE_LAUNCHER, COPY PASTE CODE FROM "projectile_launcher.c"
    //AND USE INSTEAD OF THIS MAIN

    mlx_image_to_window(world.mlx, world.scene, 0, 0);

    // Run the main loop and terminate on quit.
    mlx_loop(world.mlx);
    mlx_terminate(world.mlx);

    /* cleanup stage*/
    // implement later

    return (EXIT_SUCCESS);
}
