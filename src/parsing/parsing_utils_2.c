#include "minirt.h"

/**
 * @brief Opens a file in read-only mode and returns its file descriptor.
 *
 * @param map_file Path to the input scene file.
 * @return File descriptor on success, exits the program on failure.
 */
int	read_file(const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Error: open fd");
	return (fd);
}

/**
 * @brief Copies a substring into a token buffer with null termination.
 *
 * @param dest Destination buffer (token), must be at least MAX_TOKEN_LENGTH.
 * @param src Source string to copy from.
 * @param len Number of characters to copy from src.
 */
void	copy_token(char *dest, const char *src, size_t len)
{
	size_t	j;

	ft_memset(dest, 0, MAX_TOKEN_LENGTH);
	j = 0;
	while (j < len)
	{
		dest[j] = src[j];
		j++;
	}
	dest[len] = '\0';
}
