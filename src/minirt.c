#include "minirt.h"

int	main(int argc, char **argv)
{

    // remove on production
    (void)argc;
    (void)argv;

    t_rt rt;
    uint32_t  w = 0;
    uint32_t  h = 0;
    
    /* validation stage */

	// if (validation() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

     rt.mlx = mlx_init(512, 512, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, 512, 512);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    //ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);
    while (h < 512)
    {
        w = 0;
        while (w < 512)
        {
            mlx_put_pixel(rt.scene, w, h, 0x58c0dc);
            w++;
        }
        h++;
    }

    //IF YOU WANT TO SEE THE PROJECTILE_LAUNCHER, COPY PASTE CODE FROM "projectile_launcher.c" 
    //AND USE INSTEAD OF THIS MAIN

    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);

    /* cleanup stage*/
    // implement later

    return (EXIT_SUCCESS);
}