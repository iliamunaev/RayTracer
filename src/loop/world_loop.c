#include "minirt.h"

static bool handle_cam_movement(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_UP)
        world->cam.position.y -= RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_DOWN)
        world->cam.position.y += RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
        world->cam.position.x -= RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
        world->cam.position.x += RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_W)
        world->cam.position.z += RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_S)
        world->cam.position.z -= RESIZING_FACTOR_STBL;
    else
        return (false);
    return (true);
}

static bool handle_cam_fov_adjustment(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_Q)
        world->cam.fov -= RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_E)
        world->cam.fov += RESIZING_FACTOR_STBL;
    else
        return (false);
    return (true);
}

static bool handle_resizing(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_1)
        resize_spere(world, RESIZING_FACTOR_DEC);
    else if (keydata.key == MLX_KEY_2)
        resize_spere(world, RESIZING_FACTOR_INC);
    else
        return (false);
    return (true);
}

static bool key_acton(t_rt *world, mlx_key_data_t keydata, bool *moved, bool *changed)
{

    if (keydata.key == MLX_KEY_ESCAPE)
    {
        printf("Exiting...\n");
        mlx_close_window(world->mlx);
        return (false);
    }
    if (handle_cam_movement(world, keydata))
    {
        *moved = true;
        return (true);
    }
    else if (handle_cam_fov_adjustment(world, keydata))
    {
        *moved = true;
        return (true);
    }

    else if (handle_resizing(world, keydata))
    {
        *changed = true;
        return (true);
    }

}

void world_loop(mlx_key_data_t keydata, void *param)
{
    t_rt *world = (t_rt *)param;
    bool moved;
    bool changed;
    
    moved = false;
    changed = false;
    if (keydata.action != MLX_PRESS)
        return;

    if(key_acton(world, keydata, &moved, &changed))
    {
        if(moved)
            rebuild_camera(world);
        if (moved || changed)
                render(world);
    }



    // if (moved)
    // {
    //     rebuild_camera(world);
    // }
    // if (moved || changed)
    // {
    //     render(world);
    // }
}

