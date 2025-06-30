#include "minirt.h"

void world_loop(t_rt *world)
{
    mlx_image_to_window(world->mlx, world->scene, 0, 0);
}
