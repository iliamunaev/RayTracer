#include "minirt.h"

/*
typedef struct s_token
{
    char token[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];
} t_token;
 
*/
void world_loop(t_rt *world)
{
    // t_rt *world = (t_rt *)param;
    bool moved = false;

    mlx_image_to_window(world->mlx, world->scene, 0, 0);

    // Y-axis up/down (arrow keys)
    if (mlx_is_key_down(world->mlx, MLX_KEY_UP))
    {
        printf("cam.position.y Before: %f\n", world->cam.position.y);

        printf("Press UP\n");
        world->cam.position.y += 5.0f;
        moved = true;
        printf("cam.position.y After: %f\n", world->cam.position.y);

    }
    if (mlx_is_key_down(world->mlx, MLX_KEY_DOWN))
    {
        printf("cam.position.y Before: %f\n", world->cam.position.y);

        printf("Press DOWN\n");
        world->cam.position.y -= 5.0f;
        moved = true;
        printf("cam.position.y After: %f\n", world->cam.position.y);

    }

    // X-axis left/right (arrow keys or A/D)
    if (mlx_is_key_down(world->mlx, MLX_KEY_LEFT)
        || mlx_is_key_down(world->mlx, MLX_KEY_A))
    {
        printf("cam.position.x Before: %f\n", world->cam.position.x);

        printf("Press LEFT/A\n");
        world->cam.position.x -= 5.0f;
        moved = true;
        printf("cam.position.x After: %f\n", world->cam.position.x);

    }
    if (mlx_is_key_down(world->mlx, MLX_KEY_RIGHT)
        || mlx_is_key_down(world->mlx, MLX_KEY_D))
    {
        printf("cam.position.x Before: %f\n", world->cam.position.x);

        printf("Press RIGHT/D\n");
        world->cam.position.x += 5.0f;
        moved = true;

        printf("cam.position.x After: %f\n", world->cam.position.x);
    }

    // Z-axis forward/back (W/S)
    if (mlx_is_key_down(world->mlx, MLX_KEY_W))
    {
        printf("cam.position.z Before: %f\n", world->cam.position.z);
        printf("Press W\n");
        world->cam.position.z += 5.0f;
        moved = true;
        printf("cam.position.z Aftre: %f\n", world->cam.position.z);

    }
    if (mlx_is_key_down(world->mlx, MLX_KEY_S))
    {
        printf("Press S\n");
        world->cam.position.z -= 5.0f;
        moved = true;
    }

    // FOV increase/decrease
    if (mlx_is_key_down(world->mlx, MLX_KEY_Q))
    {
        printf("fox Before: %f\n", world->cam.fov);

        world->cam.fov -= 1.0f;
        printf("FOV -: %f\n", world->cam.fov);
        moved = true;
        printf("fox After: %f\n", world->cam.fov);

    }
    if (mlx_is_key_down(world->mlx, MLX_KEY_E))
    {
        printf("fox Before: %f\n", world->cam.fov);

        world->cam.fov += 1.0f;
        printf("FOV +: %f\n", world->cam.fov);
        moved = true;
        printf("fox After: %f\n", world->cam.fov);

    }

    // Reset camera position
    if (mlx_is_key_down(world->mlx, MLX_KEY_R))
    {
        printf("Reset camera\n");

        world->cam.position.x = 0;
        world->cam.position.y = 0;
        world->cam.position.z = 0;
        moved = true;
    }

    // Exit program with ESC
    if (mlx_is_key_down(world->mlx, MLX_KEY_ESCAPE))
    {
        printf("Exiting...\n");
        mlx_close_window(world->mlx);
    }

    if (moved)
    {
        printf("Start re-rendering\n");
        render(world);
        printf("Finish re-rendering\n");
    }
}

