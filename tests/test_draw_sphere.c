#include "minirt.h"


    /* 
    uint8_t  w = 0;
    uint8_t  h = 0;
    
    while (h < size)
    {
        w = 0;
        while (w < size)
        {
            mlx_put_pixel(rt.scene, w, h, 0x58c0dc);
            w++;
        }
        h++;
    } */

int	main(void)
{
    t_rt rt;
    uint64_t  canvas_size = 400;

    rt.mlx = mlx_init(canvas_size, canvas_size, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);
    rt.scene = mlx_new_image(rt.mlx, canvas_size, canvas_size);
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);



    t_tuple ray_origin = {0, 0, -5, 1};
    float   wall_size = 7;
    float   pixel_size = wall_size / canvas_size;
    float   half = wall_size / 2;
    
    t_primitive sphere;
    t_tuple     sphere_position = {0, 0, 0, 1};
    create_sphere( &sphere, sphere_position);

    t_tuple color;
    create_color(&color, 250, 150, 90);


    int y = 0;
    int x;
    float   world_y;
    float   world_x;
    float   wall_z = 7;

    t_ray ray;
    t_tuple ray_vector;
    t_tuple position;


    while (y < canvas_size)
    {
        x = 0;
        world_y = half - pixel_size * y;
        while (x < canvas_size)
        {
            world_x = -half + pixel_size * x;
            create_point(&position, world_x, world_y, wall_z);
            sub_tuples(&ray_vector, position, ray_origin);
            create_ray(&ray, ray_origin, ray_vector);
            get_ray_intersections(&ray, rt);
            get_hit(&ray);
            if (ray.is_hit == true)
            {
                mlx_put_pixel(rt.scene, x, y, 0xFF0000FF);
            }
            else
                mlx_put_pixel(rt.scene, x, y,  0x58c0dc);
            x++;
        }
        y++;
    }


    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);


    return (EXIT_SUCCESS);
}