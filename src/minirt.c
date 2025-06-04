#include "minirt.h"

int	main(int argc, char **argv)
{

    // remove on production
    (void)argc;
    (void)argv;

    t_rt rt;

    /* validation stage */

	// if (validation() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);


    rt.mlx = mlx_init(256, 256, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);

    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);


    /* cleanup stage*/
    // implement later

    return (EXIT_SUCCESS);
}