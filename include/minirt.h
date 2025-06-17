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
# include "matrix.h"
# include "ray.h"
# include "primitives.h"
# include "../lib/libft/libft.h"
# include "parsing.h"
# include "validation.h"


#define BPP sizeof(int32_t)
#define MAX_PRIMITIVES 32


typedef struct s_amb_light
{
	char	id;
	float	ratio;
	t_tuple	color;
}	t_amb_light;


typedef struct s_cam
{
    char    id;
    t_tuple    coordinates;
    t_tuple    norm_vector;
    float		fov;    
}   t_cam;

typedef struct s_light
{
    char	id;
	t_tuple	coordinates;
    float	brightness;   
    t_tuple	color;   
}   t_light;

typedef struct s_sphere
{
    char    id;
    t_tuple    coordinates;
    float   diameter;   
    t_tuple	color;   
}   t_sphere;

typedef struct s_plane_tmp
{
    char    id;
    t_tuple    coordinates;
    t_tuple    norm_vector;   
    t_tuple    color;   
}   t_plane_tmp;

typedef struct s_cylinder_tmp
{
    char    id;
    t_tuple    coordinates;
    t_tuple    norm_vector;   
    float    diameter; 
    float    height; 
    t_tuple    color;   
}   t_cylinder_tmp;

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*scene;
    uint8_t     obj_counted;
    t_primitive primitives_list[MAX_PRIMITIVES];
	t_amb_light	amb_light;
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
