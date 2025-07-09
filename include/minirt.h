#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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
# include "manipulation.h"

# define BPP 4UL
# define MAX_PRIMITIVES 32
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define BLUE   0
# define GREEN  1
# define RED	2
# define ALPHA  3
# define ZERO_CAM_FOV 0.0f
# define DEFAILT_CAM_FOV 70.0f

typedef enum e_mode
{
	MODE_NONE,
	MODE_SCALE,
	MODE_ROTATE,
	MODE_TRANSLATE,
	MODE_CAM
}	t_mode;

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*scene;
	uint8_t		obj_counted;
	t_primitive	primitives_list[MAX_PRIMITIVES];
	t_amb		amb;
	t_cam		cam;
	t_light		light;
	int			selected_primitive_index;
	t_mode		mode;
	double		mouse_x;
	double		mouse_y;
}	t_rt;

typedef struct s_transform
{
	t_tuple	rotate;
	t_tuple	scale;
	t_tuple	translate;
}	t_transform;

// render.c
void	render(t_rt *rt);
void	handle_mouse_click(mouse_key_t button, action_t action,
			modifier_key_t mods, void	*param);
void	handle_mouse_move(double x, double y, void	*param);
void	world_loop(mlx_key_data_t keydata, void	*param);

// loop/world_loop.c
bool	handle_object(t_rt *world, mlx_key_data_t keydata);

// loop/key_action.c
bool	key_action(t_rt *world, mlx_key_data_t keydata,
			bool *moved, bool *changed);

// loop/lop_utils.c
void	print_mode(int mode_1, int mode_2);

// loop/cam_action.c
bool	handle_cam(t_rt *world, mlx_key_data_t keydata);

#endif // MINIRT_H
