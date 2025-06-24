#include "minirt.h"


int	main(int argc, char **argv)
{
    t_rt rt;    
    parse(argv[1], &rt);
    
    uint64_t  canvas_size = 400;
    rt.mlx = mlx_init(canvas_size, canvas_size, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);
    rt.scene = mlx_new_image(rt.mlx, canvas_size, canvas_size);
    ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);


    // rt.obj_counted = 1;


    t_tuple ray_origin = {0, 0, -5, 1};
    float   wall_size = 7;
    float   pixel_size = wall_size / canvas_size;
    float   half = wall_size / 2;
    
    /* t_primitive sphere;
    t_tuple     sphere_position = {0, 0, 0, 1};
    create_sphere( &sphere, sphere_position); */
    
    //print_matrix(sphere.matrix);


    //t_tuple sphere_color;
    //create_color(&sphere_color, 1, 0, 0);
    create_material(&sphere, sphere_color);
   // rt.primitives_list[0] = sphere;


   // color for pixel
    t_tuple color;
    create_color(&color, 1, 0.5, 0.2);

    
    //t_primitive light;
    
    /* light.brightness = 1;
    create_color(&light.color, 1, 1, 1);
    create_point(&light.position, -10, 10, -10);
    */
   
   
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
         while (x < canvas_size)
        {
            mlx_put_pixel(rt.scene, x, y, 0x58c0dc);
            x++;
        }
        y++;
    }
    y = 0;

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
            get_ray_intersections(&ray, &rt);
            get_hit(&ray);
            
            t_primitive *light;

            find_light(&light, rt);

            if (ray.is_hit == true)
            {
                lighting(&color, ray.hit.object, light, ray);
                mlx_put_pixel(rt.scene, x, y, float_to_hex(color));

            }
/*             else
            {
                mlx_put_pixel(rt.scene, x, y,  0xFFFFFFFFFF);
            } */
            x++;
        }
        y++;
    }


    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);


    return (EXIT_SUCCESS);
} 
