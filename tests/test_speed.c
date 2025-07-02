#include "minirt.h"
#include <time.h>

// Render time: 1.428597 seconds

int	main(int argc, char **argv)
{
    (void)argc;
    t_rt world;
    struct timespec start, end;

    init_world(&world);
    setup_mlx(&world);
    parse(argv[1], &world);

    // Start timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Measure this function
    render(&world);

    // End timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate time in seconds
    double render_time = (end.tv_sec - start.tv_sec) +
                         (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Render time: %.6f seconds\n", render_time);

    mlx_key_hook(world.mlx, world_loop, &world);
    mlx_loop(world.mlx);
    mlx_terminate(world.mlx);

    return (EXIT_SUCCESS);
}