#include "minirt.h"

/**
 * is_float_in_range - Check if a string represents
 * a float within range [min, max].
 * @s: String to parse as float.
 * @min: Minimum allowed value (inclusive).
 * @max: Maximum allowed value (inclusive).
 *
 * Return: true if valid float within range, false otherwise.
 */
bool	is_float_in_range(char *s, float min, float max)
{
	float	val;

	val = ft_strtof(s);
	return (val >= min && val <= max);
}

/**
 * is_vec3_unbounded - Validate if a string represents
 *  a 3D vector with 3 floats.
 * @s: String in the format "x,y,z".
 *
 * Return: true if it contains exactly 3 valid float values, 
 * false otherwise.
 */
bool	is_vec3_unbounded(char *s)
{
	char	**parts;
	int		count;
	int		i;
	bool	has_digits;

	parts = ft_split(s, ',');
	count = 0;
	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), (false));
	i = 0;
	while (i < 3)
	{
		has_digits = false;
		ft_strtof_valid(parts[i], &has_digits);
		if (!has_digits)
			return (false);
		i++;
	}
	free_split(parts);
	return (true);
}

/**
 * @brief Check if all 3 float strings are in range [-1.0, 1.0].
 * 
 * @param parts Array of 3 strings.
 * @return true if all values are valid and normalized.
 */
static bool	is_three_floats_normalized(char **parts)
{
	int		i;
	float	val;
	bool	has_digits;

	i = 0;
	while (i < 3)
	{
		has_digits = false;
		ft_strtof_valid(parts[i], &has_digits);
		if (!has_digits)
			return (false);
		val = ft_strtof(parts[i]);
		if (val < -1.0f || val > 1.0f)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Check if a string represents a normalized 3D vector.
 * 
 * @param s String in format "x,y,z" with each value in [-1.0, 1.0]
 * @return true if valid normalized vector, false otherwise
 */
bool	is_vec3_normalized(char *s)
{
	char	**parts;
	int		count;

	parts = ft_split(s, ',');
	count = 0;
	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), false);
	if (!is_three_floats_normalized(parts))
		return (free_split(parts), false);
	free_split(parts);
	return (true);
}

/**
 * is_color_rgb - Validate if a string represents an RGB color in range [0,255].
 * @s: String in the format "R,G,B".
 *
 * Return: true if valid RGB color, false otherwise.
 */
bool	is_color_rgb(char *s)
{
	char	**parts;
	int		count;
	int		i;
	int		val;

	parts = ft_split(s, ',');
	count = 0;
	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), (false));
	i = 0;
	while (i < 3)
	{
		val = ft_atoi(parts[i]);
		if (val < 0 || val > 255)
			return (free_split(parts), (false));
		i++;
	}
	free_split(parts);
	return (true);
}
