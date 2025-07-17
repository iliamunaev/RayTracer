#include "minirt.h"

/**
 * @brief Checks if a given object is present in the container list.
 *
 * @param containers array of primitive pointers currently in the container
 * @param count number of objects in the container
 * @param obj the object to check for presence
 * @return true if the object is in the container, false otherwise
 */
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

/**
 * @brief Removes a specified object from the container list, 
 * shifting elements left.
 *
 * @param containers array of primitive pointers
 * @param count pointer to the number of objects in the container
 * @param obj the object to be removed
 */
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

/**
 * @brief Appends a new object to the container list if capacity allows.
 * Errors out if MAX_CONTAINERS is exceeded.
 *
 * @param containers array of primitive pointers
 * @param count pointer to the number of objects in the containe
 * @param obj the object to add
 */
void	containers_append(t_primitive **containers, int *count,
		t_primitive *obj)
{
	if (*count < MAX_CONTAINERS)
	{
		containers[*count] = obj;
		++(*count);
	}
	else
		err("maximum containers reached");
}
