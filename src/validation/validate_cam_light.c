#include "minirt.h"

/**
 * @brief Validate ambient light parameters from a `.rt` scene line.
 *
 * Expected format: `A <ratio> <R,G,B>`
 *
 * - ratio: float in range [0.0, 1.0]
 * - color: RGB values in range [0, 255]
 *
 * @param token Parsed token list representing the ambient line.
 * @return true if the parameters are valid, false otherwise.
 */
bool	is_validate_ambient(t_token *token)
{
	if (!token->token[1] || !token->token[2])
		return (false);
	if (!is_float_in_range(token->token[1], 0.0f, 1.0f))
		return (false);
	if (!is_color_rgb(token->token[2]))
		return (false);
	return (true);
}

/**
 * @brief Validate camera parameters from a `.rt` scene line.
 *
 * Expected format: `C <position> <orientation> <FOV>`
 *
 * - position: 3D vector (x,y,z)
 * - orientation: normalized 3D vector, each component ∈ [-1, 1]
 * - FOV: float in range [0.0, 180.0]
 *
 * @param token Parsed token list representing the camera line.
 * @return true if the parameters are valid, false otherwise.
 */
bool	is_validate_camera(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3])
		return (false);
	if (!is_vec3_unbounded(token->token[1]))
	{
		err("Invalid camera position vector");
		return (false);
	}
	if (!is_vec3_normalized(token->token[2]))
	{
		err("Invalid camera orientation vector (must be in [-1,1])");
		return (false);
	}
	if (!is_float_in_range(token->token[3], 0.0f, 180.0f))
	{
		err("Invalid FOV value");
		return (false);
	}
	return (true);
}

/**
 * @brief Validate light parameters from a `.rt` scene line.
 *
 * Expected format: `L <position> <brightness> <R,G,B>`
 *
 * - position: 3D vector (x,y,z)
 * - brightness: float in range [0.0, 1.0]
 * - color: RGB values in range [0, 255]
 *
 * @param token Parsed token list representing the light line.
 * @return true if the parameters are valid, false otherwise.
 */
bool	is_validate_light(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3])
	{
		err("Light: Missing one or more arguments");
		return (false);
	}
	if (!is_vec3_unbounded(token->token[1]))
	{
		err("Light: Invalid position vector");
		return (false);
	}
	if (!is_float_in_range(token->token[2], 0.0f, 1.0f))
	{
		err("Light: Brightness must be in [0.0, 1.0]");
		return (false);
	}
	if (!is_color_rgb(token->token[3]))
	{
		err("Light: Invalid RGB color");
		return (false);
	}
	return (true);
}
