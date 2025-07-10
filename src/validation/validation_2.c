#include "minirt.h"

/**
 * @brief Count how many valid tokens are present in the token array.
 *
 * @param tokens A pointer to the t_token structure.
 * @return Number of non-empty tokens found (max MAX_NUM_TOKENS).
 */
static inline int	count_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (count < MAX_NUM_TOKENS && tokens->token[count][0] != '\0')
		count++;
	return (count);
}

/**
 * @brief Validate if the number of tokens is within the expected maximum
 *        for a given identifier (A, C, L, sp, pl, cy).
 *
 * @param id     The identifier string (e.g., "A", "C", "sp").
 * @param tokens A pointer to the token array to validate.
 * @return true if the token count is within valid limits; false otherwise.
 */
bool	is_max_num_tokens_valid(char *id, t_token *tokens)
{
	int	num_tokens;

	num_tokens = count_tokens(tokens);
	if (ft_strcmp(id, "A") == 0)
		return (num_tokens <= MAX_NUM_TOKENS_A);
	else if (ft_strcmp(id, "C") == 0)
		return (num_tokens <= MAX_NUM_TOKENS_C);
	else if (ft_strcmp(id, "L") == 0)
		return (num_tokens <= MAX_NUM_TOKENS_L);
	else if (ft_strcmp(id, "sp") == 0)
		return (num_tokens <= MAX_NUM_TOKENS_SP);
	else if (ft_strcmp(id, "pl") == 0)
		return (num_tokens <= MAX_NUM_TOKENS_PL);
	else if (ft_strcmp(id, "cy") == 0)
		return (num_tokens <= MAX_NUM_TOKENS_CY);
	return (false);
}

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
bool	validate_ambient(t_token *tokens)
{
	if (tokens->vstate.seen_ambient || !is_validate_ambient(tokens))
	{
		err("Error: ambient");
		return (false);
	}
	tokens->vstate.seen_ambient = true;
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
bool	validate_camera(t_token *tokens)
{
	if (tokens->vstate.seen_camera || !is_validate_camera(tokens))
	{
		err("Error: camera");
		return (false);
	}
	tokens->vstate.seen_camera = true;
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
bool	validate_light(t_token *tokens)
{
	if (tokens->vstate.seen_light || !is_validate_light(tokens))
	{
		err("Error: light");
		return (false);
	}
	tokens->vstate.seen_light = true;
	return (true);
}
