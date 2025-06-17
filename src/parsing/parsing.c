#include "minirt.h"

static bool is_singleton_id(char id)
{
    return (id == 'A' || id == 'C' || id == 'L');
}

static void set_singleton_flag(bool *flags, char id)
{
    if (id == 'A')
        flags[0] = true;
    else if (id == 'C')
        flags[1] = true;
    else if (id == 'L')
        flags[2] = true;
}

static bool is_singleton_duplicate(bool *flags, char id)
{
    if (id == 'A' && flags[0])
        return (true);
    if (id == 'C' && flags[1])
        return (true);
    if (id == 'L' && flags[2])
        return (true);
    return (false);
}

static void dispatch_parser(t_primitive *prim, char **tokens)
{
    if (ft_strcmp(tokens[0], "A") == 0)
        parse_ambient(prim, tokens);
    else if (ft_strcmp(tokens[0], "C") == 0)
        parse_camera(prim, tokens);
    else if (ft_strcmp(tokens[0], "L") == 0)
        parse_light(prim, tokens);
    else if (ft_strcmp(tokens[0], "sp") == 0)
        parse_sphere(prim, tokens);
    else if (ft_strcmp(tokens[0], "pl") == 0)
        parse_plane(prim, tokens);
    else if (ft_strcmp(tokens[0], "cy") == 0)
        parse_cylinder(prim, tokens);
}

static void parse_rt_map(t_pars *map_tmp, const char *map)
{
    char **lines;
    char **tokens;
    char *id;
    char id_char;
    bool singleton_flags[3] = {false, false, false};
    int count;
    int i;

    lines = ft_split(map, '\n');
    count = 0;
    i = 0;
    while (lines[i])
    {
        if (is_line_empty_or_space(lines[i]))
        {
            i++;
            continue ;
        }
        tokens = split_whitespace(lines[i]);
        if (!tokens[0])
        {
            free_str_array(tokens);
            i++;
            continue ;
        }

        id = tokens[0];
        id_char = id[0];
        if (is_singleton_id(id_char) && is_singleton_duplicate(singleton_flags, id_char))
            exit_with_error("Duplicate singleton element");

        set_singleton_flag(singleton_flags, id_char);

        dispatch_parser(&map_tmp->element[count], tokens);
        map_tmp->element[count].id = generate_id();
        count++;
        free_str_array(tokens);
        i++;
    }
    map_tmp->count = count;
    free_str_array(lines);
}

int parse(char *map, t_rt *world)
{
    t_pars  *map_tmp;
    uint8_t elements;

    if(!is_map_valid(map))
        return (EXIT_FAILURE);
    elements = count_elements(map);
    if (elements > MAX_PRIMITIVES)
        return (EXIT_FAILURE);
    map_tmp = init_map_tmp(elements);
    if (!map_tmp)
        return (EXIT_FAILURE);

    parse_rt_map(map_tmp, map);

    fillup_world(&world, map_tmp);

    free_map_tmp(&map_tmp);
    return (EXIT_SUCCESS);
}
