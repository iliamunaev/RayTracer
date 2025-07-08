#include "minirt.h"

/**
 * is_float_in_range - Check if a string represents a float within range [min, max].
 * @s: String to parse as float.
 * @min: Minimum allowed value (inclusive).
 * @max: Maximum allowed value (inclusive).
 *
 * Return: true if valid float within range, false otherwise.
 */
bool is_float_in_range(const char *s, float min, float max)
{
	float val = ft_strtof(s);
	return (val >= min && val <= max);
}

/**
 * is_vec3_unbounded - Validate if a string represents a 3D vector with 3 floats.
 * @s: String in the format "x,y,z".
 *
 * Return: true if it contains exactly 3 valid float values, false otherwise.
 */
bool is_vec3_unbounded(const char *s)
{
	char **parts = ft_split(s, ',');
	int count = 0;

	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), (false));

	for (int i = 0; i < 3; i++)
		ft_strtof(parts[i]);
	free_split(parts);
	return (true);
}

/**
 * is_vec3_normalized - Validate if a string represents a normalized 3D vector.
 * @s: String in the format "x,y,z" where each float ∈ [-1.0, 1.0].
 *
 * Return: true if valid normalized vector, false otherwise.
 */
bool is_vec3_normalized(const char *s)
{
	char **parts = ft_split(s, ',');
	int count = 0;

	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), (false));

	for (int i = 0; i < 3; i++)
	{
		float val = ft_strtof(parts[i]);
		if (val < -1.0f || val > 1.0f)
			return (free_split(parts), (false));
	}

	free_split(parts);
	return (true);
}

/**
 * is_color_rgb - Validate if a string represents an RGB color in range [0,255].
 * @s: String in the format "R,G,B".
 *
 * Return: true if valid RGB color, false otherwise.
 */
bool is_color_rgb(const char *s)
{
	char **parts = ft_split(s, ',');
	int count = 0;

	while (parts && parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), (false));
	for (int i = 0; i < 3; i++)
	{
		int val = atoi(parts[i]);
		if (val < 0 || val > 255)
			return (free_split(parts), (false));
	}
	free_split(parts);
	return (true);
}
