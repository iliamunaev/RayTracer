#ifndef UTILS_H
# define UTILS_H

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_tuple	t_tuple;

// utils.c
void	create_vector(t_tuple *vector, float x, float y, float z);
void	create_point(t_tuple *point, float x, float y, float z);
void	err(char *msg);
void	free_split(char **split);

#endif // UTILS_H
