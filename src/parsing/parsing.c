#include "minirt.h"

int	read_file(const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Error");
	return (fd);
}

static void skip_spaces(char **line)
{
    while (ft_isspace(**line))
        (*line)++;
}

void parse_line(char *line, t_token *tokens)
{
    char    *start;
    size_t  len;
    size_t  i;
    size_t  j;

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
        ft_memset(tokens->token[i], 0, MAX_TOKEN_LENGTH);
        j = 0;
        while (j < len)
        {
            tokens->token[i][j] = start[j];
            j++;
        }
        tokens->token[i][len] = '\0';
        i++;
    }
    while (i < MAX_NUM_TOKENS)
        tokens->token[i++][0] = '\0';
}


int parse(const char *map_file, t_rt *world)
{
    int     fd;
	char    *line;
    t_token tokens;
    int       i;

    fd = read_file(map_file); // open map file for reading
	if (fd < 0)
        return (EXIT_FAILURE);
    i = 0;
    while (line = get_next_line(fd)) // read line by line, add mamory clininig if malloc fails in get next line
	{
        // add validation
        /*
        if(!is_line_valid(line)) // validate line
        {
            free(line);
            close(fd);
            return (EXIT_FAILURE);
        }
        */

        parse_line(line, &tokens); // fillup world with primitives
        fillup_world(world, &tokens, i);
        free(line);
        i++;
    }
	close(fd);
    return (EXIT_SUCCESS);
}
