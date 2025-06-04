#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include "utils.h"
# include <MLX42/MLX42.h>

#define BPP sizeof(int32_t)

typedef struct s_rs
{
    mlx_t   *mlx;
}   t_rt;

# endif // MINIRT_H