#include "minirt.h"

/**
 * is_validate_ambient - Validate ambient light parameters.
 * @token: Token list for the ambient line. Expected format: A ratio R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool is_validate_ambient(t_token *token)
{
	// Format: A 0.2 255,255,255
	if (!token->token[1] || !token->token[2])
		return (false);
	if (!is_float_in_range(token->token[1], 0.0f, 1.0f))
		return (false);
	if (!is_color_rgb(token->token[2]))
		return (false);
	return (true);
}

/**
 * is_validate_camera - Validate camera parameters.
 * @token: Token list for the camera line. Expected format: C position orientation FOV.
 *
 * Return: true if valid, false otherwise.
 */
bool is_validate_camera(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3])
		return (false);

	if (!is_vec3_unbounded(token->token[1]))   // position
	{
		err("Invalid camera position vector");
		return (false);
	}
	if (!is_vec3_normalized(token->token[2]))   // orientation vector
	{
		err("Invalid camera orientation vector (must be in [-1,1])");
		return (false);
	}
	if (!is_float_in_range(token->token[3], 0.0f, 180.0f))  // FOV
	{
		err("Invalid FOV value");
		return (false);
	}

	return (true);
}

/**
 * is_validate_light - Validate light parameters.
 * @token: Token list for the light line. Expected format: L position brightness R,G,B.
 *
 * Return: true if valid, false otherwise.
 */
bool is_validate_light(t_token *token)
{
	// Format: L -40.0,50.0,0.0 0.6 10,0,255
	if (!token->token[1] || !token->token[2] || !token->token[3])
	{
		err("Light: Missing one or more arguments");
		return (false);
	}
	if (!is_vec3_unbounded(token->token[1]))  // position
	{
		err("Light: Invalid position vector");
		return (false);
	}
	if (!is_float_in_range(token->token[2], 0.0f, 1.0f))  // brightness
	{
		err("Light: Brightness must be in [0.0, 1.0]");
		return (false);
	}
	if (!is_color_rgb(token->token[3]))  // color
	{
		err("Light: Invalid RGB color");
		return (false);
	}
	return (true);
}
