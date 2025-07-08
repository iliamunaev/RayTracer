#include "minirt.h"

static bool handle_cam(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_UP && (keydata.modifier & MLX_CONTROL))
        world->cam.position.z += FACTOR_STBL;
    else if (keydata.key == MLX_KEY_DOWN && (keydata.modifier & MLX_CONTROL))
        world->cam.position.z -= FACTOR_STBL;

    else if (keydata.key == MLX_KEY_LEFT && (keydata.modifier & MLX_CONTROL))
         world->cam.fov -= FACTOR_STBL;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.modifier & MLX_CONTROL))
        world->cam.fov += FACTOR_STBL;

    else if (keydata.key == MLX_KEY_UP)
        world->cam.position.y -= FACTOR_STBL;
    else if (keydata.key == MLX_KEY_DOWN)
        world->cam.position.y += FACTOR_STBL;
    else if (keydata.key == MLX_KEY_LEFT)
        world->cam.position.x -= FACTOR_STBL;
    else if (keydata.key == MLX_KEY_RIGHT)
        world->cam.position.x += FACTOR_STBL;

    else
        return (false);
    return (true);
}

static bool handle_object(t_rt *world, mlx_key_data_t keydata)
{
    float factor;

    if (keydata.key == MLX_KEY_KP_ADD)

        factor = FACTOR_INC;

    else if (keydata.key == MLX_KEY_KP_SUBTRACT)
        factor = FACTOR_DEC;

    if(world->mode ==  MODE_CAM)
        handle_cam(world, keydata);

    if (world->mode == MODE_SCALE)
        scale_object(world, factor);
    if (world->mode == MODE_TRANSLATE)
    {
        float factor_x = 0;
        float factor_y = 0;
        float factor_z = 0;

        if (keydata.key == MLX_KEY_UP && (keydata.modifier & MLX_CONTROL))
        {
            factor_z = 0.1;
        }
        else if (keydata.key == MLX_KEY_DOWN && (keydata.modifier & MLX_CONTROL))
        {
            factor_z = -0.1;
        }

        else if (keydata.key == MLX_KEY_RIGHT)
        {
            factor_x = 0.1;
        }
        else if (keydata.key == MLX_KEY_LEFT)
        {
            factor_x = -0.1;
        }
        else if (keydata.key == MLX_KEY_DOWN)
        {
            factor_y = -0.1;
        }
        else if (keydata.key == MLX_KEY_UP)
        {
            factor_y = 0.1;
        }


        translate_object(world, factor_x, factor_y, factor_z );
    }
    if (world->mode == MODE_ROTATE)
    {
        float factor_x = 0;
        float factor_y = 0;
        float factor_z = 0;

        if (keydata.key == MLX_KEY_RIGHT)
        {
            factor_x = -0.1;
        }
        else if (keydata.key == MLX_KEY_LEFT)
        {
            factor_x = 0.1;
        }
        else if (keydata.key == MLX_KEY_DOWN)
        {
            factor_y = 0.1;
        }
        else if (keydata.key == MLX_KEY_UP)
        {
            factor_y = -0.1;
        }
        else if (keydata.key == MLX_KEY_UP && (keydata.modifier & MLX_CONTROL))
        {
            factor_z = -0.2;
        }
        else if (keydata.key == MLX_KEY_DOWN && (keydata.modifier & MLX_CONTROL))
        {
            factor_z = 0.2;
        }       
        rotate_object(world, factor_x, factor_y, factor_z );
    }
    else
        return (false);

    return (true);
}

static bool key_acton(t_rt *world, mlx_key_data_t keydata, bool *moved, bool *changed)
{
    int i;

    i = world->selected_primitive_index;
    if (keydata.key == MLX_KEY_ESCAPE)
    {
        printf("Exiting app...\n");
        mlx_close_window(world->mlx);
        return (false);
    }
    if (keydata.key == MLX_KEY_C )
    {
        if (world->mode == MODE_CAM)
        {
            printf("End CAM mode\n");

        }
        else
        {
            world->mode = MODE_CAM;
            printf("Start CAM mode\n");

        }
        return (true);
    }
    else if (keydata.key == MLX_KEY_S && i > -1)
    {
        if (world->mode == MODE_SCALE)
        {
            world->mode = MODE_NONE;
            printf("End SCALE mode\n");
        }
        else
        {
            world->mode = MODE_SCALE;
            printf("Start SCALE mode\n");
        }
        return (true);
    }
    else if (keydata.key == MLX_KEY_R && i > -1)
    {
        if (world->mode == MODE_ROTATE)
        {
            world->mode = MODE_ROTATE;
            printf("Exited ROTATE mode\n");
        }
        else
        {
            world->mode = MODE_ROTATE;
            printf("Start ROTATE mode\n");
        }
        return (true);
    }
    else if (keydata.key == MLX_KEY_T && i > -1)
    {
        if (world->mode == MODE_TRANSLATE)
        {
            world->mode = MODE_TRANSLATE;
            printf("Exited TRANSLATE mode\n");
        }
        else
        {
            world->mode = MODE_TRANSLATE;
            printf("Start TRANSLATE mode\n");
        }
        return (true);
    }
    if (world->mode != MODE_NONE && world->mode != MODE_CAM && i >= 0 && i < world->obj_counted)
    {
        handle_object(world, keydata);
        *changed = true;
        return (true);
    }
    if (world->mode != MODE_NONE && world->mode == MODE_CAM)
    {
        handle_cam(world, keydata);
        *moved = true;

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
