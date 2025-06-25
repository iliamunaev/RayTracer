#include "minirt.h"

// V_SCREEN_SIZE

// C from -50.0,0,20      to 0,0,1       70


// void camera()
// {
    
// }


float calculate_half_view(t_rt *rt)
{
    float fov_rad;

    fov_rad = get_radians(rt->cam.fov);
    return (tanf(fov_rad / 2.0f));
}

float calculate_aspect(void)
{
    return ((float)SCREEN_HEIGHT / (float)SCREEN_WIDTH);
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

float calculate_pixel_size(float half_width, float screen_width)
{
    return ((half_width * 2.0f) / screen_width);
}

float get_pixel_size(t_rt *rt)
{
    float half_width;
    float half_view;
    float aspect;

    half_view = calculate_half_view(rt);
    aspect = calculate_aspect();
    half_width = calculate_half_width(aspect, half_view);
    return ((half_width * 2.0f) / SCREEN_WIDTH);
}