#include "minirt.h"


int	main(int argc, char **argv)
{

    // remove on production
    (void)argc;
    (void)argv;

    //t_rt rt;
    t_tuple vector;
    t_tuple point;

    create_vector(&vector, 1, 2, 3);
    create_point(&point, 5, 6, 7);

    printf("v x: %f\n", vector.x);
    printf("v y: %f\n", vector.y);
    printf("v z: %f\n", vector.z);
    printf("v w: %i\n", vector.w);

    printf("p x: %f\n", point.x);
    printf("p y: %f\n", point.y);
    printf("p z: %f\n", point.z);
    printf("p w: %i\n", point.w);

    
    /* validation stage */

	// if (validation() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

   /*  rt.mlx = mlx_init(256, 256, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);

    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx); */


    /* cleanup stage*/
    // implement later

    return (EXIT_SUCCESS);
}