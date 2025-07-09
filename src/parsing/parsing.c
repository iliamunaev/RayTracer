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

static int	process_line(char *line, t_token *tokens, t_rt *world, int *obj_count)
{
	parse_line(line, tokens);
	printf("VALIDATING LINE: \"%s\"\n", line); // DEBUG
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

static int	check_singletons(t_validation_state *vstate)
{
	if (!vstate->seen_ambient)
		return (err("Error: Missing ambient light (A)"), EXIT_FAILURE);
	if (!vstate->seen_camera)
		return (err("Error: Missing camera (C)"), EXIT_FAILURE);
	if (!vstate->seen_light)
		return (err("Error: Missing light (L)"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	process_file_lines(int fd, t_rt *world, t_validation_state *vstate,
		int *obj_count)
{
	char	*line;
	// t_token	tokens;
	int		line_num;
	float	amb_light;
	int		i;

	line_num = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_line_empty(line))
		{
			free(line);
			continue ;
		}
		if (process_line(line, tokens, world, obj_count))
			return (EXIT_FAILURE);
		line_num++;
	}
	return (EXIT_SUCCESS);
	amb_light = world->amb.brightness;
	i = 0;
	while (i < world->obj_counted)
	{
		world->primitives_list[i].material.ambient = amb_light;
		world->primitives_list[i].material.diffuse = 0.9;
		world->primitives_list[i].material.specular = 0.1;
		world->primitives_list[i].material.shininess = 50;
		if (world->primitives_list[i].type == PLANE)
		{
			world->primitives_list[i].material.reflection = 0.6;
			world->primitives_list[i].material.transparency = 0.0;
			world->primitives_list[i].material.refraction = 1;
		}
		else if (world->primitives_list[i].type == SPHERE)
		{
			world->primitives_list[i].material.diffuse = 0.1;
			world->primitives_list[i].material.ambient = 0.1;
			world->primitives_list[i].material.specular = 1.0;
			world->primitives_list[i].material.shininess = 250;
			world->primitives_list[i].material.reflection = 0.95;
			world->primitives_list[i].material.transparency = 0.95;
			world->primitives_list[i].material.refraction = 1.52;
		}
		else
		{
			world->primitives_list[i].material.reflection = 0.0;
			world->primitives_list[i].material.transparency = 0;
			world->primitives_list[i].material.refraction = 1;
		}
		i++;
	}
}

int	parse(const char *map_file, t_rt *world)
{
	int					fd;
	// t_validation_state	vstate;
	int					obj_count;
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
	create_material(world);
	if (check_singletons(&vstate) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("Success: map validation\n");
	return (EXIT_SUCCESS);
}
