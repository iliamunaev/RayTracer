#include "minirt.h"

/**
 * @brief Check if the identifier token is valid (non-null and non-empty).
 *
 * Identifiers include "A", "C", "L", "sp", "pl", "cy", etc.
 *
 * @param id Pointer to the identifier string.
 * @return true if the identifier is valid, false otherwise.
 */
static bool	is_identifier_valid(char *id)
{
	if (!id || id[0] == '\0')
	{
		err("Error: Empty identifier");
		return (false);
	}
	return (true);
}

/**
 * @brief Validate unique scene elements: ambient light, camera, and light.
 *
 * Each of these elements must appear only once in the .rt file. This function
 * ensures the element is valid and updates the validation state.
 *
 * @param id Identifier string ("A", "C", or "L").
 * @param tokens The parsed tokens for the line.
 * @param v Pointer to the validation state.
 * @return true if the element is valid and not duplicated, false otherwise.
 */
static bool	validate_cam_light(char *id, t_token *tokens,
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

/**
 * @brief Validate a primitive object in the scene: sphere, plane, or cylinder.
 *
 * Checks the identifier and calls the appropriate validation function.
 * Prints an error and returns false if the identifier is unknown.
 *
 * @param id Identifier string ("sp", "pl", or "cy").
 * @param tokens The parsed tokens for the line.
 * @return true if the primitive is valid, false otherwise.
 */
static bool	validate_primitive(char *id, t_token *tokens)
{
	if (ft_strcmp(id, "sp") == 0)
		return (is_validate_sphere(tokens));
	else if (ft_strcmp(id, "pl") == 0)
		return (is_validate_plane(tokens));
	else if (ft_strcmp(id, "cy") == 0)
		return (is_validate_cylinder(tokens));
	else
	{
		err("Error: Unknown identifier");
		return (false);
	}
}

/**
 * @brief Validate a single line of the .rt scene file.
 *
 * Ensures the identifier is valid, checks for duplicate A/C/L elements,
 * and validates primitives like spheres, planes, and cylinders.
 *
 * @param tokens Parsed token list from one line of input.
 * @param vstate Validation state used to track seen elements.
 * @return true if the line is syntactically and semantically valid, 
 * false otherwise.
 */
bool	is_line_valid(t_token *tokens, t_validation_state *vstate)
{
	char	*id;

	id = tokens->token[0];
	if (!is_identifier_valid(id))
		return (false);
	if (validate_cam_light(id, tokens, vstate))
		return (true);
	return (validate_primitive(id, tokens));
}
