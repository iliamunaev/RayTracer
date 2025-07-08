#include "minirt.h"

/**
 * is_validate_sphere - Validate sphere object parameters.
 * @token: Token list for the sphere line. 
 * Expected format: sp center diameter R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool	is_validate_sphere(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3])
		return (err("Error: Sphere: Missing one or more arguments"), false);
	if (!is_vec3_unbounded(token->token[1]))
		return (err("Error: Sphere: Invalid center vector"), false);
	if (!is_float_in_range(token->token[2], 0.0f, 10000.0f))
		return (err("Error: Sphere: Invalid diameter"), false);
	if (!is_color_rgb(token->token[3]))
		return (err("Error: Sphere: Invalid color format"), false);
	return (true);
}

/**
 * is_validate_plane - Validate plane object parameters.
 * @token: Token list for the plane line. Expected format: pl point normal R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool	is_validate_plane(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3])
		return (err("Error: Plane: Missing one or more arguments"), false);
	if (!is_vec3_unbounded(token->token[1]))
		return (err("Error: Plane: Invalid position vector"), false);
	if (!is_vec3_normalized(token->token[2]))
		return (err("Error: Plane: Invalid normal vector \
			(must be normalized in [-1,1])"), false);
	if (!is_color_rgb(token->token[3]))
		return (err("Error: Plane: Invalid RGB color"), false);
	return (true);
}

/**
 * is_validate_cylinder - Validate cylinder object parameters.
 * @token: Token list for the cylinder line. 
 * Expected format: cy center axis diameter height R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool	is_validate_cylinder(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3]
		|| !token->token[4] || !token->token[5])
		return (err("Cylinder: Missing one or more arguments"), false);
	if (!is_vec3_unbounded(token->token[1]))
		return (err("Error: Cylinder: Invalid center position"), false);
	if (!is_vec3_normalized(token->token[2]))
		return (err("Error: Cylinder: Invalid axis vector \
			(must be normalized in [-1,1])"), false);
	if (!is_float_in_range(token->token[3], 0.0f, 10000.0f))
		return (err("Error: Cylinder: Invalid diameter"), false);
	if (!is_float_in_range(token->token[4], 0.0f, 10000.0f))
		return (err("Error: Cylinder: Invalid height"), false);
	if (!is_color_rgb(token->token[5]))
		return (err("Error: Cylinder: Invalid color format"), false);
	return (true);
}
