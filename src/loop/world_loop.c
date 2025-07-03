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

static bool handle_sphere(t_rt *world, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_2)
        resize_spere(world, RESIZING_FACTOR_DEC);
    else if (keydata.key == MLX_KEY_3)
        resize_spere(world, RESIZING_FACTOR_INC);
    else
        return (false);
    return (true);
}


// static bool handle_cylinder(t_rt *world, mlx_key_data_t keydata)
// {
//     if (keydata.key == MLX_KEY_3)
//         resize_cylinder_hight(world, RESIZING_FACTOR_DEC);
//     else if (keydata.key == MLX_KEY_4)
//         resize_cylinder_hight(world, RESIZING_FACTOR_INC);
//     else if (keydata.key == MLX_KEY_5)
//         resize_cylinder_width(world, RESIZING_FACTOR_INC);
//     else if (keydata.key == MLX_KEY_6)
//         resize_cylinder_width(world, RESIZING_FACTOR_INC);
//     else
//         return (false);
//     return (true);
// }

// static bool key_acton(t_rt *world, mlx_key_data_t keydata, bool *moved, bool *changed)
// {

//     if (keydata.key == MLX_KEY_ESCAPE)
//     {
//         printf("Exiting...\n");
//         mlx_close_window(world->mlx);
//         return (false);
//     }
//     if (handle_cam(world, keydata))
//     {
//         *moved = true;
//         return (true);
//     }
//     else if (handle_sphere(world, keydata))
//     {
//         *changed = true;
//         return (true);
//     }
//     else if (handle_cylinder(world, keydata))
//     {
//         *changed = true;
//         return (true);
//     }

// }


static void scale_primitive(t_rt *world, mlx_key_data_t keydata)
{
    int i = world->selected_primitive_index;

    if (i < 0 || i >= world->obj_counted)
        return;

    t_primitive *prim = &world->primitives_list[i];

    if (prim->type == SPHERE)
        handle_sphere(world, keydata);

        
    // else if (prim->type == CYLINDER)
    //     handle_cylinder(world, keydata);
    // else if (prim->type == CUBE)
    //     handle_cube(world, keydata);
    // Add more primitives here
}

static bool key_acton(t_rt *world, mlx_key_data_t keydata, bool *moved, bool *changed)
{
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
    if (keydata.key == MLX_KEY_1 && world->selected_primitive_index > -1)
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
    if (world->mode == MODE_SCALE)
    {
        scale_primitive(world, keydata);
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
