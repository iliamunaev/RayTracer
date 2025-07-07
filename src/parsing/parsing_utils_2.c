#include "minirt.h"

int	read_file(const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Error: open fd");
	return (fd);
}

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
