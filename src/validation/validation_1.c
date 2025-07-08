#include "minirt.h"

static bool	validate_cam_light(const char *id, const t_token *tokens,
	t_validation_state *v)
{
	if (ft_strcmp(id, "A") == 0)
		return (validate_ambient(tokens, v));
	else if (ft_strcmp(id, "C") == 0)
		return (validate_camera(tokens, v));
	else if (ft_strcmp(id, "L") == 0)
		return (validate_light(tokens, v));
	else
		return (false);
}

static bool	validate_primitive(const char *id, const t_token *tokens)
{
	if (ft_strcmp(id, "sp") == 0)
		return (is_validate_sphere(tokens));
	else if (ft_strcmp(id, "pl") == 0)
		return (is_validate_plane(tokens));
	else if (ft_strcmp(id, "cy") == 0)
		return (is_validate_cylinder(tokens));
	else
	{
		err("Unknown identifier");
		return (false);
	}
}

/**
 * is_line_valid - Validate a single line of the .rt scene file.
 * @tokens: Parsed token list from one line of input.
 * @vstate: Validation state for enforcing unique elements (A, C, L).
 *
 * Return: true if the line is syntactically and semantically valid, 
 * false otherwise.
 */
bool	is_line_valid(const t_token *tokens, t_validation_state *vstate)
{
	char	*id;

	id = tokens->token[0];
	if (has_too_many_tokens(tokens))
		return (false);
	if (!is_identifier_valid(id))
		return (false);
	if (validate_cam_light(id, tokens, vstate))
		return (true);
	return (validate_primitive(id, tokens));
}
