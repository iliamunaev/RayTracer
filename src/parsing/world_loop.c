#include "minirt.h"

static void debug_cam_pos(const char *axis, float before, float after)
{
    printf("cam.position.%s Before: %f\n", axis, before);
    printf("cam.position.%s After: %f\n", axis, after);
}

static void debug_fov(const char *label, float before, float after)
{
    printf("FOV %s: %f -> %f\n", label, before, after);
}  




void world_loop(mlx_key_data_t keydata, void *param)
{
    t_rt *world = (t_rt *)param;

    if (keydata.action != MLX_PRESS)
        return;

    bool moved = false;

    if (keydata.key == MLX_KEY_UP)
    {
        float before = world->cam.position.y;
        world->cam.position.y += 1.0f;
        debug_cam_pos("y", before, world->cam.position.y);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_DOWN)
    {
        float before = world->cam.position.y;
        world->cam.position.y -= 1.0f;
        debug_cam_pos("y", before, world->cam.position.y);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
    {
        float before = world->cam.position.x;
        world->cam.position.x -= 1.0f;
        debug_cam_pos("x", before, world->cam.position.x);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
    {
        float before = world->cam.position.x;
        world->cam.position.x += 1.0f;
        debug_cam_pos("x", before, world->cam.position.x);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_W)
    {
        float before = world->cam.position.z;
        world->cam.position.z += 1.0f;
        debug_cam_pos("z", before, world->cam.position.z);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_S)
    {
        float before = world->cam.position.z;
        world->cam.position.z -= 1.0f;
        debug_cam_pos("z", before, world->cam.position.z);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_Q)
    {
        float before = world->cam.fov;
        world->cam.fov -= 1.0f;
        debug_fov("-", before, world->cam.fov);
        moved = true;
    }
    else if (keydata.key == MLX_KEY_E)
    {
        float before = world->cam.fov;
        world->cam.fov += 1.0f;
        debug_fov("+", before, world->cam.fov);
        moved = true;
    }
    // else if (keydata.key == MLX_KEY_R)
    // {
    //     printf("Resetting camera position to (0, 0, 0)\n");
    //     world->cam.position = (t_tuple){0.0f, 0.0f, 0.0f, 1.0f};
    //     moved = true;
    // }
    else if (keydata.key == MLX_KEY_ESCAPE)
    {
        printf("Exiting...\n");
        mlx_close_window(world->mlx);
    }

    if (moved)
    {
        rebuild_camera(world);
        render(world); // Optional
    }
}
