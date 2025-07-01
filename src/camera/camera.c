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
    mult_matrix_by_tuple(&pixel, cam->matrix, pixel_point);

    t_tuple origin;
    t_tuple point = {0, 0, 0, 1.0f,};    
    mult_matrix_by_tuple(&origin, cam->matrix, point);

    t_tuple direction;
    sub_tuples(&direction, pixel, origin);

    normalize_vector(&direction);

    ray->origin = origin;
    ray->direction = direction;
}



// void rebuild_camera(t_rt *rt)
// {
//     printf("DEBUG: rebuild_camera() Start\n");

//     t_tuple to;
//     t_tuple up = (t_tuple){0, 1, 0, 0};

//     // Sanity check: norm_vector must be valid and non-zero
//     if (isnan(rt->cam.norm_vector.x) || isnan(rt->cam.norm_vector.y) || isnan(rt->cam.norm_vector.z))
//     {
//         fprintf(stderr, "ERROR: norm_vector has NaN — resetting to default (0,0,-1)\n");
//         rt->cam.norm_vector = (t_tuple){0.0f, 0.0f, -1.0f, 0.0f};
//     }
//     else if (magnitude_vector(rt->cam.norm_vector) < EPSILON)
//     {
//         fprintf(stderr, "Warning: norm_vector magnitude ~0 — resetting to (0,0,-1)\n");
//         rt->cam.norm_vector = (t_tuple){0.0f, 0.0f, -1.0f, 0.0f};
//     }

//     normalize_vector(&rt->cam.norm_vector);

//     // Compute the "look at" target: to = position + direction
//     add_tuples(&to, rt->cam.position, rt->cam.norm_vector);

//     // Recompute camera projection plane parameters
//     rt->cam.half_view   = get_half_view(rt);
//     rt->cam.half_width  = get_half_width(rt);
//     rt->cam.half_height = get_half_height(rt);
//     rt->cam.pix_size    = (rt->cam.half_width * 2.0f) / (float)img_w;

//     printf("DEBUG: rebuild_camera() calling transform_cam_view()\n");
//     transform_cam_view(rt, rt->cam.position, to, up);

//     printf("DEBUG: rebuild_camera() calling invert_matrix()\n");
//     invert_matrix(&rt->cam.inv_matrix, rt->cam.matrix);

//     printf("DEBUG: rebuild_camera() rt->cam.matrix\n");
    
//     print_matrix(rt->cam.matrix);
    
//     printf("DEBUG: rebuild_camera() rt->cam.matrix\n");
//     print_matrix(rt->cam.inv_matrix);

//     printf("DEBUG: rebuild_camera() END\n");
// }

bool is_zero_vector(t_tuple v)
{
    return (v.x == 0 && v.y == 0 && v.z == 0);
}


void rebuild_camera(t_rt *rt)
{
    
    printf("\n---------------DEBUG: START rebuild_camera()\n");
   
    printf("\nDEBUG: cam->matrix BEFOR transform_cam_view()\n");
    print_matrix(rt->cam.matrix);

    if (is_zero_vector(rt->cam.norm_vector))
    {
        rt->cam.norm_vector = (t_tuple){0, 0, 1, 0};
    }
    
    // Build view matrix
    t_tuple from = rt->cam.position;

    t_tuple to = {
        rt->cam.position.x + rt->cam.norm_vector.x,
        rt->cam.position.y + rt->cam.norm_vector.y,
        rt->cam.position.z + rt->cam.norm_vector.z,
        1.0f
    };

    t_tuple up = {0.0f, 1.0f, 0.0f, 0.0f}; // world up

    printf("DEBUG: cam.position = (%f, %f, %f)\n",
       rt->cam.position.x, rt->cam.position.y, rt->cam.position.z);


    transform_cam_view(rt, from, to, up); // transform updates cam->matrix

    printf("\nDEBUG: cam->matrix AFTER transform_cam_view()\n");
    print_matrix(rt->cam.matrix);



    invert_matrix(&rt->cam.inv_matrix, rt->cam.matrix);
    printf("\nDEBUG: cam->inv_matrix\n");
    print_matrix(rt->cam.inv_matrix);

    if (rt->cam.fov == 0.0f)
        rt->cam.fov = 70.0f;

    rt->cam.half_view = get_half_view(rt);

    rt->cam.half_height = get_half_height(rt) ;
    rt->cam.pix_size = get_pixel_size(rt);

    printf("\nnDEBUG: rt->cam.half_view: %f\n", rt->cam.half_view);
    printf("\nnDEBUG: rt->cam.half_height: %f\n", rt->cam.half_height);
    printf("\nnDEBUG: rt->cam.pix_size: %f\n", rt->cam.pix_size);

    printf("\n---------------DEBUG: END rebuild_camera()\n");
}

