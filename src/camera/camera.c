#include "minirt.h"

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

void ray_for_pixel(t_ray *ray, t_cam *cam, float px, float py)
{
    float xoffset;
    float yoffset;
    float world_x;
    float world_y;
    
    xoffset = (px + 0.5) * cam->pix_size;
    yoffset = (py + 0.5) * cam->pix_size;
    
    world_x = cam->half_view - xoffset;
    world_y = cam->half_height - yoffset;
    
    t_tuple pixel_point = {world_x, world_y, -1.0f, 1.0f,};

    t_tuple pixel;
    mult_matrix_by_tuple(&pixel, cam->inv_matrix, pixel_point);

    t_tuple origin;
    t_tuple point = {0, 0, 0, 1.0f,};    
    mult_matrix_by_tuple(&origin, cam->inv_matrix, point);

    t_tuple direction;
    sub_tuples(&direction, pixel, origin);

    normalize_vector(&direction);

    ray->origin = origin;
    ray->direction = direction;
    //ray_transform(ray, cam->inv_matrix);
}