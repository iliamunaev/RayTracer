#include "minirt.h"

static inline void assign_values(t_tuple *color, int rgb[])
{
	float	inv_255;

	inv_255 = 1.0f / 255.0f;
	color->r = rgb[0] * inv_255;
	color->g = rgb[1] * inv_255;
	color->b = rgb[2] * inv_255;
	color->a = 1.0f;
}

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

void	skip_spaces(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}
