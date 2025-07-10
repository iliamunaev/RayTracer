#include "minirt.h"

static void	parse_line(char *line, t_token *tokens)
{
	char	*start;
	size_t	len;
	size_t	i;

	i = 0;
	while (*line && i < MAX_NUM_TOKENS)
	{
		skip_spaces(&line);
		if (*line == '\0' || *line == '\n')
			break ;
		start = line;
		while (*line && !ft_isspace(*line))
			line++;
		len = line - start;
		if (len >= MAX_TOKEN_LENGTH)
			len = MAX_TOKEN_LENGTH - 1;
		copy_token(tokens->token[i], start, len);
		i++;
	}
	while (i < MAX_NUM_TOKENS)
		tokens->token[i++][0] = '\0';
}

static int	process_line(char *line, t_token *tokens, t_rt *world,
		int *obj_count)
{
	parse_line(line, tokens);
	if (!is_line_valid(tokens))
	{
		err("Error: Invalid line in scene file");
		free(line);
		return (EXIT_FAILURE);
	}
	fillup_world(world, tokens, *obj_count);
	if (ft_strcmp(tokens->token[0], "sp") == 0 || ft_strcmp(tokens->token[0],
			"pl") == 0 || ft_strcmp(tokens->token[0], "cy") == 0)
		(*obj_count)++;
	free(line);
	return (EXIT_SUCCESS);
}

static int	check_singletons(t_token *tokens)
{
	if (!tokens->vstate.seen_ambient)
	{
		printf("DEBUG: %i\n", tokens->vstate.seen_ambient);
		return (err("Error: Missing ambient light (A)"), EXIT_FAILURE);
	}
	if (!tokens->vstate.seen_camera)
		return (err("Error: Missing camera (C)"), EXIT_FAILURE);
	if (!tokens->vstate.seen_light)
		return (err("Error: Missing light (L)"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	set_base_material(t_rt *world, int i)
{
	world->primitives_list[i].material.ambient = world->amb.brightness;
	world->primitives_list[i].material.diffuse = 0.9;
	world->primitives_list[i].material.specular = 0.1;
	world->primitives_list[i].material.shininess = 50;
	world->primitives_list[i].material.reflection = 0.0;
	world->primitives_list[i].material.transparency = 0;
	world->primitives_list[i].material.refraction = 1;
}

void	set_glass_material(t_rt *world, int i)
{
	world->primitives_list[i].material.diffuse = 0.1;
	world->primitives_list[i].material.ambient = 0.1;
	world->primitives_list[i].material.specular = 3.0;
	world->primitives_list[i].material.shininess = 250;
	world->primitives_list[i].material.reflection = 0.95;
	world->primitives_list[i].material.transparency = 0.8;
	world->primitives_list[i].material.refraction = 1.52;
}

void	set_material(int *obj_count, t_rt *world)
{
	int	i;

	i = 0;
	while (i < *obj_count)
	{
		set_base_material(world, i);
		if (world->primitives_list[i].bonus_type == GLASS)
			set_glass_material(world, i);
		if (world->primitives_list[i].bonus_type == CHECKER)
			world->primitives_list[i].material.reflection = 0.4;
		i++;
	}
}

static int	process_file_lines(int fd, t_rt *world, t_token *tokens,
		int *obj_count)
{
	char	*line;
	int		line_num;

	line_num = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_line_empty(line))
		{
			free(line);
			continue ;
		}
		if (process_line(line, tokens, world, obj_count))
			return (EXIT_FAILURE);
		line_num++;
	}
	set_material(obj_count, world);
	return (EXIT_SUCCESS);
}

int	parse(const char *map_file, t_rt *world)
{
	int		fd;
	int		obj_count;
	t_token	tokens;

	obj_count = 0;
	ft_memset(&tokens, 0, sizeof(t_token));
	fd = read_file(map_file);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (process_file_lines(fd, world, &tokens, &obj_count) == EXIT_FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	world->obj_counted = obj_count;
	if (check_singletons(&tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("SUCCESS: map validation\n");
	return (EXIT_SUCCESS);
}
