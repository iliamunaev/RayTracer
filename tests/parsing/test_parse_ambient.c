# include "minirt.h"

int main(int c, char **av)
{

    // printf("in main: %f\n", ft_strtof("0.2"));  // should print 0.200000

    t_rt    world;

    if (parse(av[1], &world) == EXIT_FAILURE)
    {
        err("Error");
		return (EXIT_FAILURE);
    }


    int id = world.primitives_list[0].id;
    char type = world.primitives_list[0].type;
    float ratio = world.primitives_list[0].ratio;
    t_tuple color = world.primitives_list[0].color;

    printf("\nFINAL OUTPUT: \n id: %i\n type: %c\n ratio: %f\n R: %f\n G: %f\n B: %f\n", id, type, ratio, color.r, color.g, color.b);
    int id1 = world.primitives_list[1].id;
    char type1 = world.primitives_list[1].type;
    float ratio1 = world.primitives_list[1].ratio;
    t_tuple color1 = world.primitives_list[1].color;

    printf("\nFINAL OUTPUT: \n id: %i\n type: %c\n ratio: %f\n R: %f\n G: %f\n B: %f\n", id1, type1, ratio1, color1.r, color1.g, color1.b);
}

