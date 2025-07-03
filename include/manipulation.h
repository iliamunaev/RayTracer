#ifndef MANIPULATION_H
# define MANIPULATION_H

# define FACTOR_INC 1.1f
# define FACTOR_DEC 0.9f
# define FACTOR_STBL 0.3f

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_rt t_rt;

void scale_object(t_rt *world, float factor);




# endif // MANIPULATION_H