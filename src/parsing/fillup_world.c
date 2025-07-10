#include "minirt.h"

/**
 * @brief Populates the world scene structure based on the current token.
 *
 * Determines the type of scene element by its identifier 
 * and dispatches
 * parsing to the appropriate function (ambient light, camera, 
 * light, or primitives).
 *
 * @param rt     Pointer to the main scene structure.
 * @param token  Tokenized line from the scene file.
 * @param j      Index for storing objects in the primitive list 
 * (used for sp, pl, cy).
 */
void	fillup_world(t_rt *rt, t_token *token, int j)
{
	char	*id;

	id = token->token[0];
	if (ft_strcmp(id, "A") == 0)
		parse_ambient(rt, token);
	else if (ft_strcmp(id, "C") == 0)
		parse_camera(rt, token);
	else if (ft_strcmp(id, "L") == 0)
		parse_light(rt, token);
	else if (ft_strcmp(id, "sp") == 0)
		parse_sphere(rt, token, j);
	else if (ft_strcmp(id, "pl") == 0)
		parse_plane(rt, token, j);
	else if (ft_strcmp(id, "cy") == 0)
		parse_cylinder(rt, token, j);
	else
		err("Error: Unknown identifier");
}
