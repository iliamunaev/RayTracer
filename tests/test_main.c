#include "minirt.h"


int	main(int argc, char **argv)
{
    (void)argc;
    t_rt world;

    init_world(&world);
    setup_mlx(&world);
    if (parse(argv[1], &world) != EXIT_SUCCESS)
    {
        mlx_terminate(world.mlx);
        return (EXIT_FAILURE);

    }
    render(&world);
    mlx_key_hook(world.mlx, world_loop, &world);
    mlx_mouse_hook(world.mlx, handle_mouse_click, &world);    
    mlx_cursor_hook(world.mlx, handle_mouse_move, &world);
    mlx_loop(world.mlx);
    mlx_terminate(world.mlx);

    return (EXIT_SUCCESS);
}
