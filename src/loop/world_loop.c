#include "minirt.h"

static bool handle_cam(t_rt *world, mlx_key_data_t keydata)
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
    else if (keydata.key == MLX_KEY_Q)
        world->cam.fov -= RESIZING_FACTOR_STBL;
    else if (keydata.key == MLX_KEY_E)
        world->cam.fov += RESIZING_FACTOR_STBL;
    else
        return (false);
    return (true);
}

static bool handle_object(t_rt *world, mlx_key_data_t keydata)
{
    if(world->mode == MODE_SCALE)
    {
        if (keydata.key == MLX_KEY_2)
            resize_object(world, RESIZING_FACTOR_DEC);
        else if (keydata.key == MLX_KEY_3)
            resize_object(world, RESIZING_FACTOR_INC);
        else
            return (false);
    }
    return (true);
}

static bool key_acton(t_rt *world, mlx_key_data_t keydata, bool *moved, bool *changed)
{
    int i;

    i = world->selected_primitive_index;
    if (keydata.key == MLX_KEY_ESCAPE)
    {
        if (world->mode != MODE_NONE)
        {
            world->mode = MODE_NONE;
            printf("Exited transformation mode\n");
            return (true);
        }
        printf("Exiting app...\n");
        mlx_close_window(world->mlx);
        return (false);
    }

    if (handle_cam(world, keydata))
    {
        *moved = true;
        return (true);
    }

    if (keydata.key == MLX_KEY_1 && i > -1)
    {
        if (world->mode == MODE_SCALE)
        {
            world->mode = MODE_NONE;
            printf("Exited SCALE mode\n");
        }
        else
        {
            world->mode = MODE_SCALE;
            printf("Start SCALE mode\n");
        }
        return (true);
    }
    if (world->mode != MODE_NONE && i >= 0 && i < world->obj_counted)
    {
        handle_object(world, keydata);
        *changed = true;
        return (true);
    }

    return (false);
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
}
