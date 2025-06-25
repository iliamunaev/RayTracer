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
static bool is_line_empty(const char *line)
{
    while (*line)
    {
        if (!ft_isspace(*line) && *line != '\n')
            return (false);
        line++;
    }
    return (true);
}

void    create_material(t_rt *rt)
{
    int i;
    float amb_light;

    amb_light = rt->amb.brightness;


    i = 0;
    while(i < rt->obj_counted)
    {
        rt->primitives_list[i].material.ambient = amb_light;
        rt->primitives_list[i].material.diffuse = 0.9;
        rt->primitives_list[i].material.specular = 0.1;
        rt->primitives_list[i].material.shininess = 50;
        i++;
    }
}


int parse(const char *map_file, t_rt *world)
{
    int     fd;
	char    *line;
    t_token tokens;
    int       i;
    int       j;

    fd = read_file(map_file); // open map file for reading
	if (fd < 0)
        return (EXIT_FAILURE);
    i = 0;
    j = 0;
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
        if (is_line_empty(line))
        {
            free(line);
            continue;
        }
        parse_line(line, &tokens);
        
   
        fillup_world(world, &tokens, j);
        
        if (ft_strcmp(tokens.token[0], "sp") == 0 ||
        ft_strcmp(tokens.token[0], "pl") == 0 ||
        ft_strcmp(tokens.token[0], "cy") == 0)
        {
            j++;
        }
        free(line);
        i++;
    }    
    world->obj_counted = j;
    create_material(world);
	close(fd);
    return (EXIT_SUCCESS);
}
