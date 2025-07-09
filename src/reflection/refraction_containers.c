#include "minirt.h"

bool	containers_includes(t_primitive **containers, int count,
		t_primitive *obj)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (containers[i] == obj)
			return (true);
		i++;
	}
	return (false);
}

void	containers_remove(t_primitive **containers, int *count,
		t_primitive *obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < *count)
	{
		if (containers[i] == obj)
			break ;
		i++;
	}
	j = i;
	while (j < *count - 1)
	{
		containers[j] = containers[j + 1];
		j++;
	}
	--(*count);
}

void	containers_append(t_primitive **containers, int *count,
		t_primitive *obj)
{
	if (*count < MAX_CONTAINERS)
	{
		containers[*count] = obj;
		++(*count);
	}
	else
	{
		// NEEDS TO BE DEALT WITH
		printf("max containers\n");
	}
}