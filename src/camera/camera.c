#include "minirt.h"

// V_SCREEN_SIZE

// C from -50.0,0,20      to 0,0,1       70


// void camera()
// {
    
// }


float get_half_view(t_rt *rt)
{
    float fov_rad;

    fov_rad = get_radians(rt->cam.fov);
    return (tanf(fov_rad / 2.0f));
}

float calculate_aspect(void)
{
    float aspect;

    aspect = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
    return (aspect);
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