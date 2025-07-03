#include "minirt.h"

static bool handle_camera_movement(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_UP)
        world->cam.position.y -= 1.0f;
    else if (keydata.key == MLX_KEY_DOWN)
        world->cam.position.y += 1.0f;
    else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
        world->cam.position.x -= 1.0f;
    else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
        world->cam.position.x += 1.0f;
    else if (keydata.key == MLX_KEY_W)
        world->cam.position.z += 1.0f;
    else if (keydata.key == MLX_KEY_S)
        world->cam.position.z -= 1.0f;
    else
        return (false);
    return (true);
}

static bool handle_fov_adjustment(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_Q)
        world->cam.fov -= 1.0f;
    else if (keydata.key == MLX_KEY_E)
        world->cam.fov += 1.0f;
    else
        return (false);
    return (true);
}

static bool handle_resizing(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_1)
        resize_spere(world, 0.9f);
    else if (keydata.key == MLX_KEY_2)
        resize_spere(world, 1.1f);
    else
        return (false);
    return (true);
}


void world_loop(mlx_key_data_t keydata, void *param)
{
    t_rt *world = (t_rt *)param;
    bool moved = false;
    bool changed = false;

    if (keydata.action != MLX_PRESS)
        return;

    if (keydata.key == MLX_KEY_ESCAPE)
    {
        printf("Exiting...\n");
        mlx_close_window(world->mlx);
        return;
    }

    if (handle_camera_movement(world, keydata))
        moved = true;
    else if (handle_fov_adjustment(world, keydata))
        moved = true;
    else if (handle_resizing(world, keydata))
        changed = true;

    if (moved)
    {
        rebuild_camera(world);
    }
    if (moved || changed)
    {
        render(world);
    }
}

