#include "minirt.h"

// void    setup_mlx(t_rt *world)
// {
//     world->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Test", true);
//     if (!world->mlx )
//         exit(EXIT_FAILURE);

//     world->scene = mlx_new_image(world->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
//     if (!world->scene)
//     {
//         mlx_terminate(world->mlx);
//         exit(EXIT_FAILURE);
//     }
//     ft_memset(world->scene->pixels, 255, world->scene->width * world->scene->height * BPP);
//     mlx_image_to_window(world->mlx, world->scene, 0, 0);
// }

void setup_mlx(t_rt *world)
{
    world->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT", true);
    if (!world->mlx)
    {
        fprintf(stderr, "mlx_init failed\n");
        exit(EXIT_FAILURE);
    }

    world->scene = mlx_new_image(world->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!world->scene)
    {
        fprintf(stderr, "mlx_new_image failed\n");
        mlx_terminate(world->mlx);
        exit(EXIT_FAILURE);
    }

    mlx_image_to_window(world->mlx, world->scene, 0, 0);

    fprintf(stderr, "mlx_new_image SUCCESS\n");

}
