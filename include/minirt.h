#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>


# include "math_utils.h"
# include "utils.h"


#define BPP sizeof(int32_t)

typedef struct s_rt
{
    mlx_t           *mlx;
    mlx_image_t     *scene;
}   t_rt;

typedef struct s_tuple
{
    float   x;
    float   y;
    float   z;
    uint8_t w;
}   t_tuple;


# endif // MINIRT_H