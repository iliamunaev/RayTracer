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

static void print_selected(int idx)
{
    char msg;

    if (idx == 0)
        msg = "SPHERE";
    else if (idx == 1)
        msg = "PLANE";
    else
        msg = "CYLINDER";
    printf("You choose: %s\n", msg);
}

static bool select_primitive(t_rt *world, mlx_key_data_t keydata)
{
    t_primitive *selected;

    if (keydata.key != MLX_KEY_C || world->obj_counted == 0)
        return (false);
    world->selected_primitive_index = (world->selected_primitive_index + 1) % world->obj_counted;
    selected = &world->primitives_list[world->selected_primitive_index];
    print_selected(world->selected_primitive_index);
    return (true);
}


void world_loop(mlx_key_data_t keydata, void *param)
{
    t_rt *world;
    bool moved;   
    bool selected;   
    
    world = (t_rt *)param;
    moved = false;
    selected = false;
    if (keydata.action != MLX_PRESS)
        return ;
    if (handle_camera_movement(world, keydata) || handle_fov_adjustment(world, keydata))
    {
        moved = true;
    }
    else if (choose_primitive(world, keydata))
    {
        selected = true;
    }
    else if (keydata.key == MLX_KEY_ESCAPE)
    {
        printf("Exiting...\n");
        mlx_close_window(world->mlx);
    }
    if (moved)
    {
        rebuild_camera(world);
        render(world);
    }
    if (selected)
    {
        printf("Success\n");
        // render(world);
    }

}
