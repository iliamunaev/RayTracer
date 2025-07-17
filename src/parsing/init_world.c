#include "minirt.h"

/**
 * @brief Initializes the world structure to default values.
 *
 * Sets all fields of the t_rt world struct to zero, including clearing
 * each primitive in the primitives_list. Also sets 
 * the selected primitive index to -1.
 *
 * @param world Pointer to the world structure to initialize.
 */
void	init_world(t_rt *world)
{
	int	i;

	i = 0;
	ft_memset(world, 0, sizeof(t_rt));
	while (i < MAX_PRIMITIVES)
	{
		ft_memset(&world->primitives_list[i], 0, sizeof(t_primitive));
		i++;
	}
	i = 0;
	while (i < MAX_LIGHTS)
	{
		ft_memset(&world->lights[i], 0, sizeof(t_light));
		i++;
	}
	world->selected_primitive_index = -1;
}
