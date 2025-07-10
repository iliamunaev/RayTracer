#ifndef MANIPULATION_H
# define MANIPULATION_H

# define FACTOR_INC 1.1f
# define FACTOR_DEC 0.9f
# define FACTOR_05 0.5f
# define FACTOR_01 0.1f

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_rt	t_rt;

void	scale_object(t_rt *world, float factor);
void	translate_object(t_rt *world, float factor_x,
			float factor_y, float factor_z );
void	rotate_object(t_rt *world, float factor_x,
			float factor_y, float factor_z );

#endif// MANIPULATION_H