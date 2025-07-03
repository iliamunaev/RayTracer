#include "minirt.h"

void    handle_mouse_move(double x, double y, void *param)
{
    t_rt    *world;

    world = (t_rt *)param;
    world->mouse_x = x;
    world->mouse_y = y;
}

void    handle_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    t_rt    *world;
    t_ray   ray;
    int     index;
    int        i;

    world = (t_rt *)param;
    if (action != MLX_PRESS || button != MLX_MOUSE_BUTTON_LEFT)
        return ;

    // printf("DEBUG: Mouse X: %.2f, Y: %.2f\n", world->mouse_x, world->mouse_y);

    ray_for_pixel(&ray, &world->cam, world->mouse_x, world->mouse_y);
    get_ray_intersections(&ray, world);
    get_hit(&ray);

    if (ray.is_hit)
    {
        index = -1;
        i = 0;
        while (i < world->obj_counted)
        {
            if (&world->primitives_list[i] == ray.hit.object)
            {
                index = i;
                break ;
            }
            i++;
        }
        world->selected_primitive_index = index;
        printf("DEBUG: Clicked and selected primitive #%d \n", index);
    }
}
