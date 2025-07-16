#include "minirt.h"

/**
 * @brief Splits a line into tokens, separated by whitespace.
 * 
 * Fills up to MAX_NUM_TOKENS tokens, truncating each token
 * if it exceeds MAX_TOKEN_LENGTH - 1 characters.
 * Remaining token slots are zeroed out.
 *
 * @param line   Input line from the scene file.
 * @param tokens Token buffer to fill.
 */
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

/**
 * @brief Validates and processes a single line from the scene file.
 * 
 * Parses the line into tokens, checks if it's valid, and fills the scene.
 * Increments object count if a primitive is detected.
 *
 * @param line      Raw input line.
 * @param tokens    Pointer to token structure.
 * @param world     Main scene representation.
 * @param obj_count Pointer to object count.
 * @return int      EXIT_SUCCESS or EXIT_FAILURE.
 */
static int	process_line(char *line, t_token *tokens, t_rt *world,
		int *obj_count)
{
	parse_line(line, tokens);
	if (!is_line_valid(tokens))
	{
		err("Error\nInvalid line in scene file");
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

/**
 * @brief Verifies that single-instance scene components exist.
 * 
 * Ambient light (A), Camera (C), and Light (L) must each appear once.
 *
 * @param tokens Pointer to token structure (used for state flags).
 * @return int   EXIT_SUCCESS or EXIT_FAILURE if any are missing.
 */
static int	check_singletons(t_token *tokens, t_rt *world)
{
	if (!tokens->vstate.seen_ambient)
	{
		return (err("Error\nMissing ambient light (A)"), EXIT_FAILURE);
	}
	if (!tokens->vstate.seen_camera)
		return (err("Error\nMissing camera (C)"), EXIT_FAILURE);
	if (world->lightcount <= 0 || world->lightcount > MAX_LIGHTS)
		return (err("Error\nNot correct ammount of lights (L)"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Reads and processes all non-empty lines from a file.
 * 
 * Validates each line and updates the world structure. Sets material at the end.
 *
 * @param fd        File descriptor.
 * @param world     Scene world structure.
 * @param tokens    Token structure to store parsing info.
 * @param obj_count Pointer to the current object count.
 * @return int      EXIT_SUCCESS or EXIT_FAILURE.
 */
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

/**
 * @brief Entry point for scene file parsing.
 * 
 * Initializes parser state, validates required objects, and populates the scene.
 *
 * @param map_file Path to the .rt scene file.
 * @param world    Pointer to scene world struct.
 * @return int     EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
 */
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
	if (check_singletons(&tokens, world) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
