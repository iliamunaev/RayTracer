#include "minirt.h"

/**
 * @brief Validate sphere object parameters from the .rt scene line.
 *
 * Expected format: `sp <center> <diameter> <R,G,B>`
 *
 * - center: a 3D vector ("x,y,z")
 * - diameter: a float ≥ 0
 * - color: RGB values in range [0, 255]
 *
 * @param token Parsed token list for the sphere line.
 * @return true if all parameters are valid, false otherwise.
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
 * @brief Validate plane object parameters from the .rt scene line.
 *
 * Expected format: `pl <point> <normal> <R,G,B>`
 *
 * - point: a 3D vector representing a point on the plane
 * - normal: a normalized 3D vector ("x,y,z"), each in [-1, 1]
 * - color: RGB values in range [0, 255]
 *
 * @param token Parsed token list for the plane line.
 * @return true if all parameters are valid, false otherwise.
 */
bool	is_validate_plane(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3])
		return (err("Error: Plane: Missing one or more arguments"), false);
	if (!is_vec3_unbounded(token->token[1]))
		return (err("Error: Plane: Invalid position vector"), false);
	if (!is_vec3_normalized(token->token[2]))
		return (err("Error: Plane: Invalid normal vector"), false);
	if (!is_color_rgb(token->token[3]))
		return (err("Error: Plane: Invalid RGB color"), false);
	return (true);
}

/**
 * @brief Validate cylinder object parameters from the .rt scene line.
 *
 * Expected format: `cy <center> <axis> <diameter> <height> <R,G,B>`
 *
 * - center: a 3D vector representing the base position
 * - axis: a normalized 3D vector ("x,y,z"), each in [-1, 1]
 * - diameter and height: float values ≥ 0
 * - color: RGB values in range [0, 255]
 *
 * @param token Parsed token list for the cylinder line.
 * @return true if all parameters are valid, false otherwise.
 */
bool	is_validate_cylinder(t_token *token)
{
	if (!token->token[1] || !token->token[2] || !token->token[3]
		|| !token->token[4] || !token->token[5])
		return (err("Error: Cylinder: Missing one or more arguments"), false);
	if (!is_vec3_unbounded(token->token[1]))
		return (err("Error: Cylinder: Invalid center position"), false);
	if (!is_vec3_normalized(token->token[2]))
		return (err("Error: Cylinder: Invalid axis vector"), false);
	if (!is_float_in_range(token->token[3], 0.0f, 10000.0f))
		return (err("Error: Cylinder: Invalid diameter"), false);
	if (!is_float_in_range(token->token[4], 0.0f, 10000.0f))
		return (err("Error: Cylinder: Invalid height"), false);
	if (!is_color_rgb(token->token[5]))
		return (err("Error: Cylinder: Invalid color format"), false);
	return (true);
}
