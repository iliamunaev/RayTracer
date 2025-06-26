#include "minirt.h"


int	main(int argc, char **argv)
{

    // setup world
    t_rt rt;    
    parse(argv[1], &rt);

    // setup mlx
    rt.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);
    
    render(&rt);

    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);

    return (EXIT_SUCCESS);
} 
