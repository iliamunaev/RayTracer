#include "minirt.h"

/**
 * @brief Frees a null-terminated array of strings.
 *
 * Frees each individual string, then frees the array itself.
 *
 * @param split The array of dynamically allocated strings.
 */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Initialize a 3D vector (w = 0).
 *
 * Sets the given coordinates into the vector and 
 * marks it as a direction (w = 0).
 *
 * @param vector Pointer to the t_tuple to initialize.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 */
void	create_vector(t_tuple *vector, float x, float y, float z)
{
	vector->w = 0;
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

/**
 * @brief Initialize a 3D point (w = 1).
 *
 * Sets the given coordinates into the point and marks it as a position (w = 1).
 *
 * @param point Pointer to the t_tuple to initialize.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 */
void	create_point(t_tuple *point, float x, float y, float z)
{
	point->w = 1;
	point->x = x;
	point->y = y;
	point->z = z;
}

/**
 * @brief Print an error message to standard error (stderr).
 *
 * Writes each character in the string to file descriptor 2.
 * Appends a newline at the end.
 *
 * @param msg Null-terminated string to print.
 */
void	err(char *msg)
{
	if (msg)
		while (*msg)
			write(2, msg++, 1);
	write(2, "\n", 1);
}
