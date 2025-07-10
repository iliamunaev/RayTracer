#include "minirt.h"

/**
 * is_valid_rgb_component - Check if a string represents an int [0,255].
 * @s: component string (e.g. "255")
 *
 * Return: true if valid, false otherwise.
 */
static bool	is_valid_rgb_component(const char *s)
{
	bool	has_digits;
	int		val;

	has_digits = false;
	ft_strtof_valid(s, &has_digits);
	if (!has_digits)
		return (false);
	val = ft_atoi(s);
	return (val >= 0 && val <= 255);
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

	parts = ft_split(s, ',');
	count = 0;
	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), false);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_component(parts[i]))
			return (free_split(parts), false);
		i++;
	}
	free_split(parts);
	return (true);
}
