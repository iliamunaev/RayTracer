#include "minirt.h"

// int main()
// {

    
//     printf("Hello world\n");

//     return 0;
// }

int	main(int argc, char **argv)
{

    // remove on production
    (void)argc;
    (void)argv;

    // t_rt rt;

    /* validation stage */

	// if (validation() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);


    mlx_t* mlx = mlx_init(256, 256, "Test", true);
    if (!mlx)
        exit(EXIT_FAILURE);

    mlx_image_t* img = mlx_new_image(mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    ft_memset(img->pixels, 255, img->width * img->height * BPP);

    mlx_image_to_window(mlx, img, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);


    /* cleanup stage*/
    // implement later

    return (EXIT_SUCCESS);
}