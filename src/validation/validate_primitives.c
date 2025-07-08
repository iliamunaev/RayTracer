#include "minirt.h"

/**
 * is_validate_sphere - Validate sphere object parameters.
 * @token: Token list for the sphere line. Expected format: sp center diameter R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool is_validate_sphere(t_token *token)
{
	// Format: sp 0.0,0.0,20.6 12.6 10,0,255
	if (!token->token[1] || !token->token[2] || !token->token[3])
	{
		err("Sphere: Missing one or more arguments");
		return (false);
	}
	if (!is_vec3_unbounded(token->token[1]))  // center
	{
		err("Sphere: Invalid center vector");
		return (false);
	}
	if (!is_float_in_range(token->token[2], 0.0f, 10000.0f))  // diameter
	{
		err("Sphere: Invalid diameter");
		return (false);
	}
	if (!is_color_rgb(token->token[3]))  // color
	{
		err("Sphere: Invalid color format");
		return (false);
	}
	return (true);
}

/**
 * is_validate_plane - Validate plane object parameters.
 * @token: Token list for the plane line. Expected format: pl point normal R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool is_validate_plane(t_token *token)
{
	// Format: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
	if (!token->token[1] || !token->token[2] || !token->token[3])
	{
		err("Plane: Missing one or more arguments");
		return (false);
	}

	if (!is_vec3_unbounded(token->token[1]))  // point on plane
	{
		err("Plane: Invalid position vector");
		return (false);
	}
	if (!is_vec3_normalized(token->token[2]))  // normal vector
	{
		err("Plane: Invalid normal vector (must be normalized in [-1,1])");
		return (false);
	}
	if (!is_color_rgb(token->token[3]))  // color
	{
		err("Plane: Invalid RGB color");
		return (false);
	}

	return (true);
}

/**
 * is_validate_cylinder - Validate cylinder object parameters.
 * @token: Token list for the cylinder line. Expected format: cy center axis diameter height R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool is_validate_cylinder(t_token *token)
{
	// Format: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	if (!token->token[1] || !token->token[2] || !token->token[3] ||
		!token->token[4] || !token->token[5])
	{
		err("Cylinder: Missing one or more arguments");
		return (false);
	}

	if (!is_vec3_unbounded(token->token[1]))  // position (center)
	{
		err("Cylinder: Invalid center position");
		return (false);
	}
	if (!is_vec3_normalized(token->token[2]))  // axis vector
	{
		err("Cylinder: Invalid axis vector (must be normalized in [-1,1])");
		return (false);
	}
	if (!is_float_in_range(token->token[3], 0.0f, 10000.0f))  // diameter
	{
		err("Cylinder: Invalid diameter");
		return (false);
	}
	if (!is_float_in_range(token->token[4], 0.0f, 10000.0f))  // height
	{
		err("Cylinder: Invalid height");
		return (false);
	}
	if (!is_color_rgb(token->token[5]))  // RGB color
	{
		err("Cylinder: Invalid color format");
		return (false);
	}
	return (true);
}
