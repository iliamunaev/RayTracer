#include "minirt.h"


int	main(int argc, char **argv)
{

    // setup world
    t_rt rt;    
    parse(argv[1], &rt);

    t_ray ray;

    ray_for_pixel(&ray, &rt.cam, 1, 1);

    printf("Origin X: %f\n", ray.origin.x);
    printf("Origin Y: %f\n", ray.origin.y);
    printf("Origin Z: %f\n", ray.origin.z);

    printf("Direction X: %f\n", ray.direction.x);
    printf("Direction Y: %f\n", ray.direction.y);
    printf("Direction Z: %f\n", ray.direction.z);


    return (0);
} 
