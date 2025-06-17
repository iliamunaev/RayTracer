#include "minirt.h"

/*
- Each type of element can be separated by one or more line break(s).
- Each type of information from an element can be separated by one or more
space(s).
- Each type of element can be set in any order in the file.
- Elements which are defined by a capital letter can only be declared 
once inthe scene.
- Each element first’s information is the type identifier (composed by one or two
character(s)), followed by all specific information for each object in a strict
order 
*/

void parse_ambient_light(char *map, t_rt *world)
{
    char  id;
    int i;

    id = 'A';
    i = 0;
    while(map[i])
    {
        skip_spacese(map, &i);
        if (map[i] == id)
        {
            world->amb_light.id = map[i];
            i++;
            world->amb_light.ratio = ft_strtof(map[i]);
            skip_not_space(map[i], &i);
            skip_spacese(map, &i);
        }
        i++;
    }
}
// void parse_camera(char *map, t_rt *world)
// {

// }
// void parse_light(char *map, t_rt *world)
// {

// }

// void parse_sphere(char *map, t_rt *world)
// {

// }
    
// void parse_plane(char *map, t_rt *world)
// {

// }
// void parse_cylinder(char *map, t_rt *world)
// {

// }

int parse(char *map, t_rt *world)
{
    if(!is_map_valid(map))
        return (EXIT_FAILURE);  

    
    parse_ambient_light(map, world);
    // parse_camera(map, world);
    // parse_light(map, world);
    // parse_sphere(map, world);
    // parse_plane(map, world);
    // parse_cylinder(map, world);

    return (EXIT_SUCCESS);
}