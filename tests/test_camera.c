#include "minirt.h"


int	main(int argc, char **argv)
{

    // setup world
    t_rt rt;    
    parse(argv[1], &rt);


    // printf("fov: %f\n", rt.cam.fov);
    // printf("pixel_size: %f\n", rt.cam.pix_size);
    // printf("half_w: %f\n", rt.cam.half_width);
    // printf("half_h: %f\n", rt.cam.half_height);
    // printf("half_view: %f\n", rt.cam.half_view);



    // setup mlx
    rt.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);
    

    t_tuple ray_origin = {0, 0, -5, 1};

   // color for pixel
    t_tuple color;
    create_color(&color, 1, 0.5, 0.2);

    
    int y = 0;
    int x;
    // float   world_y;
    // float   world_x;
    // float   wall_z = 7;
    t_ray ray;
    t_tuple ray_vector;
    t_tuple position;

    t_comps comps;


    while (y < SCREEN_WIDTH)
    {
        x = 0;
        // world_y = half - pixel_size * y;
        while (x < SCREEN_HEIGHT)
        {
            // world_x = -half + pixel_size * x;
            // create_point(&position, world_x, world_y, wall_z);
            // sub_tuples(&ray_vector, position, ray_origin);

            // create_ray(&ray, ray_origin, ray_vector);


            ray_for_pixel(&ray, &rt.cam, x, y);
            
            color_at(&comps, &color, &rt, &ray);
            
            if (ray.is_hit == true)
                mlx_put_pixel(rt.scene, x, y, float_to_hex(color));
            else
                mlx_put_pixel(rt.scene, x, y, 0x58c0dc);
            //mlx_put_pixel(rt.scene, x, y, float_to_hex(rt.amb.amb_component));
            x++;
        }
        y++;
    }
    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);



    return (EXIT_SUCCESS);
} 
