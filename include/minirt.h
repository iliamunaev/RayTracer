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
# define NUM_MAT_COLS 4

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*scene;
}	t_rt;

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	uint8_t	w;
}	t_tuple;

typedef struct s_row
{
	float	cols[NUM_MAT_COLS];
}	t_row;

typedef struct s_matrix
{
	t_row	rows[NUM_MAT_COLS];
	uint8_t	size;
}	t_matrix;


// matrix
void	create_matrix(t_matrix *matrix, uint8_t size);
void	fillup_matrix(t_matrix *matrix, const float data[]);
bool	are_matrices_equal(const t_matrix a, const t_matrix b);
void	mult_matxs(t_matrix *a, const t_matrix b, const t_matrix c);

// For testing
// Delete on production
void print_matrix(const t_matrix matrix);

# endif // MINIRT_H

