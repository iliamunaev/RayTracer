#include "minirt.h"

float get_half_view(t_rt *rt)
{
    float fov_rad;

    fov_rad = get_radians(rt->cam.fov);
    return (tanf(fov_rad / 2.0f));
}

float calculate_aspect(void)
{
    return (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
}


float calculate_half_width(float aspect, float half_view)
{
    if (aspect >= 1.0f)
        return (half_view);
    else

        return (half_view * aspect);
}

float calculate_half_height(float aspect, float half_view)
{

    if (aspect >= 1.0f)
        return (half_view / aspect);
    else
        return (half_view);
}

float calculate_pixel_size(float half_width)
{
    return ((half_width * 2.0f) / SCREEN_WIDTH);
}


float get_half_width(t_rt *rt)
{
    float aspect;
    float half_view;

    aspect = calculate_aspect();
    half_view = get_half_view(rt);
    return(calculate_half_width(aspect, half_view));
}

float get_half_height(t_rt *rt)
{
    float aspect;
    float half_view;

    aspect = calculate_aspect();
    half_view = get_half_view(rt);
    return(calculate_half_height(aspect, half_view));
}

float get_pixel_size(t_rt *rt)
{
    float half_width;

    half_width = get_half_width(rt);
    return (calculate_pixel_size(half_width));
}

static bool is_zero_vector(t_tuple v)
{
    return (v.x == 0 && v.y == 0 && v.z == 0);
}


void rebuild_camera(t_rt *rt)
{
    t_tuple from;
    t_tuple to = {
        rt->cam.position.x + rt->cam.norm_vector.x,
        rt->cam.position.y + rt->cam.norm_vector.y,
        rt->cam.position.z + rt->cam.norm_vector.z,
        1.0f
    };
    t_tuple up = {0.0f, 1.0f, 0.0f, 0.0f};

    if (is_zero_vector(rt->cam.norm_vector))
    {
        rt->cam.norm_vector = (t_tuple){0, 0, 1, 0};
    }    
    from = rt->cam.position;

    transform_cam_view(rt, from, to, up);
    invert_matrix(&rt->cam.inv_matrix, rt->cam.matrix);

    if (rt->cam.fov == 0.0f)
        rt->cam.fov = 70.0f;

    rt->cam.half_view = get_half_view(rt);
    rt->cam.half_height = get_half_height(rt) ;
    rt->cam.pix_size = get_pixel_size(rt);
}

