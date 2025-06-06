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
    union 
    {
        float   x;
        float   r;
    };
    union 
    {
        float   y;
        float   g;
    };
    union 
    {
        float   z;
        float   b;
    };
    union 
    {
        uint8_t w;
        uint8_t a;
    };
}   t_tuple;

//COLORS
void        create_color(t_tuple *color, float r, float g, float b, float a);
uint32_t    float_to_hex(const t_tuple color);

# endif // MINIRT_H