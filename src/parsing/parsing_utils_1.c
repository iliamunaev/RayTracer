#include "minirt.h"

/**
 * @brief Assigns normalized RGB values (0.0–1.0) and alpha = 1.0 to the tuple.
 *
 * @param color Pointer to the t_tuple where color values will be stored.
 * @param rgb Integer array of RGB values in the range 0–255.
 */
static inline void	assign_values(t_tuple *color, int rgb[])
{
	float	inv_255;

	inv_255 = 1.0f / 255.0f;
	color->r = rgb[0] * inv_255;
	color->g = rgb[1] * inv_255;
	color->b = rgb[2] * inv_255;
	color->a = 1.0f;
}

/**
 * @brief Parses a string of RGB values (e.g., "255,128,0") 
 * into a normalized t_tuple.
 *
 * @param color Pointer to the t_tuple to store the parsed RGB values.
 * @param str The input string containing the RGB values.
 */
void	parse_rgb(t_tuple *color, const char *str)
{
	int		rgb[3];
	int		i;

	i = 0;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	while (*str && i < 3)
	{
		while (*str == ' ')
			str++;
		rgb[i] = 0;
		while (*str >= '0' && *str <= '9')
		{
			rgb[i] = rgb[i] * 10 + (*str - '0');
			str++;
		}
		while (*str == ' ')
			str++;
		if (*str == ',')
			str++;
		i++;
	}
	assign_values(color, rgb);
}

/**
 * @brief Parses a string of 3D coordinates (e.g., "1.0,2.5,-3.2")
 * into a t_tuple.
 *
 * @param position Pointer to the t_tuple to store the parsed coordinates.
 * @param str The input string containing the coordinates.
 */
void	parse_coordinates(t_tuple *position, const char *str)
{
	int			i;
	float		vals[3];
	const char	*p;

	p = str;
	i = 0;
	while (i < 3)
	{
		while (*p == ' ')
			p++;
		vals[i] = ft_strtof(p);
		while (*p && *p != ',')
			p++;
		if (*p == ',')
			p++;
		i++;
	}
	position->x = vals[0];
	position->y = vals[1];
	position->z = vals[2];
	position->w = 1.0f;
}

/**
 * @brief Checks if a given line is empty or contains only whitespace/newline.
 *
 * @param line The input string to check.
 * @return true if the line is empty or only whitespace; false otherwise.
 */
bool	is_line_empty(const char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line) && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

/**
 * @brief Advances the string pointer past all leading whitespace characters.
 *
 * @param line Pointer to the string pointer to update.
 */
void	skip_spaces(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}
