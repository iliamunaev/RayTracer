#include "minirt.h"


int	main(int argc, char **argv)
{

    // setup world
    t_rt rt;    
    parse(argv[1], &rt);


    printf("fov: %f\n", rt.cam.fov);
    printf("pixel_size: %f\n", rt.cam.pix_size);
    printf("half_w: %f\n", rt.cam.half_width);
    printf("half_h: %f\n", rt.cam.half_height);
    printf("half_view: %f\n", rt.cam.half_view);


    /*
    // setup mlx
    rt.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);


    // printf("fov: %f\n", rt.cam.fov);
    // printf("pixel_size: %f\n", rt.cam.pix_size);
    

    t_tuple ray_origin = {0, 0, -5, 1};

    // float   field_of_view = 7;
    // float   half_view = field_of_view / 2;
    
    // float   pixel_size = get_pixel_size(&rt);



   // color for pixel
    t_tuple color;
    create_color(&color, 1, 0.5, 0.2);

    
    int y = 0;
    int x;
    float   world_y;
    float   world_x;
    float   wall_z = 7;
    t_ray ray;
    t_tuple ray_vector;
    t_tuple position;

    t_primitive *light;
    light = find_primitive(&rt, "L");

    while (y < SCREEN_WIDTH)
    {
        x = 0;
        world_y = half_view - rt.cam.pix_size * y;
        while (x < SCREEN_HEIGHT)
        {
            world_x = -half_view + rt.cam.pix_size * x;
            create_point(&position, world_x, world_y, wall_z);
            sub_tuples(&ray_vector, position, ray_origin);

            create_ray(&ray, ray_origin, ray_vector);
            
            get_ray_intersections(&ray, &rt);
            get_hit(&ray); 
            
            if (ray.is_hit == true)
            {
                lighting(&color, ray.hit.object, light, ray);
                mlx_put_pixel(rt.scene, x, y, float_to_hex(color));
                
            }
            else
            {
                mlx_put_pixel(rt.scene, x, y,  0x58c0dc);
            } 
            x++;
        }
        y++;
    }
    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);
*/

    return (EXIT_SUCCESS);
} 
