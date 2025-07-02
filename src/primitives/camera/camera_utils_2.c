#include "minirt.h"

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

bool is_zero_vector(t_tuple v)
{
    return (v.x == 0 && v.y == 0 && v.z == 0);
}
