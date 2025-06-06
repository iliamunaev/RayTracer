#include "minirt.h"

typedef struct s_projectile
{
    t_tuple pos;
    t_tuple vel;
}   t_projectile;

typedef struct s_environment
{
    t_tuple grav;
    t_tuple wind;
}   t_environment;

void    tick(t_projectile *proj, const t_environment env, t_rt *rt)
{
    proj->pos.x += proj->vel.x;
    proj->pos.y += proj->vel.y;
    proj->pos.z += proj->vel.z;

    proj->vel.x += env.grav.x + env.wind.x;
    proj->vel.y += env.grav.y + env.wind.y;
    proj->vel.z += env.grav.z + env.wind.z;
    printf("projectile pos: x = %f, y = %f, z = %f\n", proj->pos.x, proj->pos.y, proj->pos.z);
    mlx_put_pixel(rt->scene, proj->pos.x, 512 - proj->pos.y, 0xFFFFFFFF);
}

int launch_projectile(t_rt *rt)
{
    t_projectile proj;
    t_environment env;

    // create projectile
    create_point (&proj.pos, 0, 1, 0);
    create_vector(&proj.vel, 1, 2, 0);
    normalize_vector(&proj.vel);
    mult_tuple(&proj.vel, 9); // multiply the velocity to shoot further

    //create environment
    create_vector(&env.grav, 0, -0.1, 0);
    create_vector(&env.wind, -0.02, 0, 0);

    //as long as projectile did not hit the ground (y = 0)
    while (proj.pos.y > 0)
        tick(&proj, env, rt);

    printf("landing spot is: x = %f, y = %f, z = %f\n", proj.pos.x, proj.pos.y, proj.pos.z);
    return (0);
}


int	main(int argc, char **argv)
{

    // remove on production
    (void)argc;
    (void)argv;

    t_rt rt;
    uint32_t  w = 0;
    uint32_t  h = 0;
    
    /* validation stage */

	// if (validation() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);

     rt.mlx = mlx_init(512, 512, "Test", true);
    if (!rt.mlx)
        exit(EXIT_FAILURE);

    rt.scene = mlx_new_image(rt.mlx, 512, 512);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    //ft_memset(rt.scene->pixels, 255, rt.scene->width * rt.scene->height * BPP);
    while (h < 512)
    {
        w = 0;
        while (w < 512)
        {
            mlx_put_pixel(rt.scene, w, h, 0x58c0dc);
            w++;
        }
        h++;
    }
    launch_projectile(&rt);
    mlx_image_to_window(rt.mlx, rt.scene, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(rt.mlx);
    mlx_terminate(rt.mlx);


    /* cleanup stage*/
    // implement later

    return (EXIT_SUCCESS);
}