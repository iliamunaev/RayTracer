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
# include "reflection.h"


#define BPP sizeof(int32_t)
#define MAX_PRIMITIVES 32
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600


typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*scene;
    uint8_t     obj_counted;	
    t_primitive primitives_list[MAX_PRIMITIVES];
	t_amb		amb;
	t_cam		cam;
	t_light		light;
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





#endif // MINIRT_H
