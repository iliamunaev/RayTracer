#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>

# include "math_utils.h"
# include "utils.h"
# include "matrix.h"
# include "ray.h"
# include "primitives.h"
# include "../lib/libft/libft.h"
# include "parsing.h"
# include "validation.h"


#define BPP sizeof(int32_t)
#define MAX_PRIMITIVES 32
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*scene;
    uint8_t     obj_counted;
    t_primitive primitives_list[MAX_PRIMITIVES];
}	t_rt;


typedef struct s_transform
{
	t_tuple	rotate;
	t_tuple scale;
	t_tuple translate;
} t_transform;


//COLORS
void        create_color(t_tuple *color, float r, float g, float b);
uint32_t    float_to_hex(const t_tuple color);
void        sub_colors(t_tuple *c, const t_tuple a, const t_tuple b);
void        add_colors(t_tuple *c, const t_tuple a, const t_tuple b);
void        mult_colors(t_tuple *tuple, const t_tuple a, const t_tuple b);


//transform_view.c
void transform_view(t_rt *rt, t_tuple from, t_tuple to, t_tuple up);

#endif // MINIRT_H
