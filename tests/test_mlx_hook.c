#include "minirt.h"


int	main(int argc, char **argv)
{

    // setup world
    (void)argc;
    t_rt world;
    init_world(&world);

    setup_mlx(&world);

    parse(argv[1], &world);

    render(&world);

	mlx_loop_hook(world.mlx, world_loop, &world);
    mlx_loop(world.mlx);
    mlx_terminate(world.mlx);

    return (EXIT_SUCCESS);
} 
