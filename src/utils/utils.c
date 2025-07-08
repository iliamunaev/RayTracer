#include "minirt.h"

/**
 * free_split - Frees a null-terminated array of strings.
 * @split: Array of strings to free.
 */
void free_split(char **split)
{
	int i;

	if (!split)
		return;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
/**
 * @brief Fills a memory area with a specified byte.
 *
 * This function sets the first `n` bytes of the memory area pointed to
 * by `s` to the constant byte value `c`. It is commonly used to initialize
 * or reset memory to a specific value.
 *
 * @param s Pointer to the memory area to be filled.
 * @param c The byte value to set, passed as an `int` but cast to
 *          `unsigned char`.
 * @param n The number of bytes to fill.
 * @return void* A pointer to the memory area `s`.
 */
// void	*ft_memset(void *s, int c, size_t n)
// {
// 	unsigned char	*buffer;

// 	buffer = (unsigned char *)s;
// 	while (n > 0)
// 	{
// 		*buffer = (unsigned char)c;
// 		buffer++;
// 		n--;
// 	}
// 	return (s);
// }

void create_vector(t_tuple *vector, float x, float y, float z)
{
    vector->w = 0;
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void create_point(t_tuple *point, float x, float y, float z)
{
    point->w = 1;
    point->x = x;
    point->y = y;
    point->z = z;
}

void err(char *msg)
{
	if (msg)
		while(*msg)
			write(2, msg++, 1);
	write(2, "\n", 1);
}
