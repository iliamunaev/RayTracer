#include "minirt.h"

/**
 * @brief Validate the ambient light definition in the scene.
 *
 * Checks for duplicates using the validation state and validates the format
 * and range of the ambient light data.
 *
 * @param tokens Parsed token list representing the ambient light line.
 * @param v Pointer to the validation state tracking duplicates.
 * @return true if the ambient light is valid and unique, false otherwise.
 */
bool	validate_ambient(t_token *tokens, t_validation_state *v)
{
	if (v->seen_ambient || !is_validate_ambient(tokens))
	{
		err("Error: ambient");
		return (false);
	}
	v->seen_ambient = true;
	return (true);
}

/**
 * @brief Validate the camera definition in the scene.
 *
 * Ensures that only one camera is defined and that the parameters are valid.
 *
 * @param tokens Parsed token list representing the camera line.
 * @param v Pointer to the validation state tracking duplicates.
 * @return true if the camera is valid and unique, false otherwise.
 */
bool	validate_camera(t_token *tokens, t_validation_state *v)
{
	if (v->seen_camera || !is_validate_camera(tokens))
	{
		err("Error: camera");
		return (false);
	}
	v->seen_camera = true;
	return (true);
}

/**
 * @brief Validate the light definition in the scene.
 *
 * Ensures only one light is defined (if your scene supports a single light),
 * and validates position, brightness, and color.
 *
 * @param tokens Parsed token list representing the light line.
 * @param v Pointer to the validation state tracking duplicates.
 * @return true if the light is valid and unique, false otherwise.
 */
bool	validate_light(t_token *tokens, t_validation_state *v)
{
	if (v->seen_light || !is_validate_light(tokens))
	{
		err("Error: light");
		return (false);
	}
	v->seen_light = true;
	return (true);
}
