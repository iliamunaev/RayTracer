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

    // ambient

    int id = world.primitives_list[0].id;
    char *type= world.primitives_list[0].type;
    float ratio = world.primitives_list[0].ratio;
    t_tuple color = world.primitives_list[0].color;

    printf("\nAMBIENT 'A 0.2 255,255,255':\n");
    printf("id: %i\n", id);
    printf("type: %s\n", type);
    printf("ratio: %f\n", ratio);

    printf("R: %f\n",color.r);
    printf("G: %f\n",color.g);
    printf("B: %f\n",color.b);
    printf("A: %f\n",color.a);

    // sphere
    int id1 = world.primitives_list[1].id;
    char *type1 = world.primitives_list[1].type;
    float diameter = world.primitives_list[1].diameter;
    t_tuple pos = world.primitives_list[1].position;
    t_tuple color1 = world.primitives_list[1].color;

    printf("\nSPHERE 'sp 0.0,0.0,20.6 12.6 10,0,255':\n");
    printf("id: %i\n", id1);
    printf("type: %s\n", type1);
    printf("x: %f\n",pos.x);
    printf("y: %f\n",pos.y);
    printf("z: %f\n",pos.z);
    printf("w: %f\n",pos.w);

    printf("diameter: %f\n",diameter);

    printf("R: %f\n",color1.r);
    printf("G: %f\n",color1.g);
    printf("B: %f\n",color1.b);
    printf("A: %f\n",color1.a);
}

