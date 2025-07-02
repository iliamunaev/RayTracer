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
