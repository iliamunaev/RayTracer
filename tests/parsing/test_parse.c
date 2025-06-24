# include "minirt.h"
/*
typedef struct s_primitive
{
    int         id;
    char        type[3];

    t_tuple    position;
    t_tuple    norm_vector;

    float       brightness;
    float       brightness;

    t_tuple     color;
    float       diameter;
    float       height;
    float       fov;
    t_material  material;

    t_matrix    matrix;
} t_primitive;
*/

static void print_brightness (float brightness)
{
    printf("brightness: %f\n", brightness);
}

static void print_color(t_tuple color)
{
    printf("R: %f\n",color.r);
    printf("G: %f\n",color.g);
    printf("B: %f\n",color.b);
    printf("A: %f\n",color.a);
}

static void print_position(t_tuple pos)
{
    printf("X: %f\n",pos.x);
    printf("Y: %f\n",pos.y);
    printf("Z: %f\n",pos.z);
    printf("W: %f\n",pos.w);
}

static void print_norm_vec(t_tuple nv)
{
    printf("Vec X: %f\n",nv.x);
    printf("Vec Y: %f\n",nv.y);
    printf("Vec Z: %f\n",nv.z);
    printf("Vec W: %f\n",nv.w);
}


int main(int c, char **av)
{

    // printf("in main: %f\n", ft_strtof("0.2"));  // should print 0.200000

    t_rt    world;

    if (parse(av[1], &world) == EXIT_FAILURE)
    {
        err("Error");
		return (EXIT_FAILURE);
    }


    int i = 0;
    t_primitive p;

    while(i < world.obj_counted)
    {
        p = world.primitives_list[i];
        printf("---------- \n");
        printf("id: %i\n", p.id);
        printf("type: %s\n", p.type);
        if (ft_strcmp(p.type, "A") == 0)
        {
            printf("AMBIENT\n");

            print_brightness(p.brightness);
            print_color(p.color);

        }
        else if (ft_strcmp(p.type, "C") == 0)
        {
            printf("CAMERA\n");
            print_position(p.position);
            print_norm_vec(p.norm_vector);
            printf("FOV: %f\n",p.fov);
        }
        else if (ft_strcmp(p.type, "L") == 0)
        {
            printf("LIGHT\n");
            print_position(p.position);
            print_brightness(p.brightness);
            print_color(p.color);

        }
        else if (ft_strcmp(p.type, "sp") == 0)
        {
            printf("SPHERE\n");
            print_position(p.position);
            printf("Diameter: %f\n",p.diameter);
            print_color(p.color);
        }
        else if (ft_strcmp(p.type, "pl") == 0)
        {
            print_position(p.position);
            print_norm_vec(p.norm_vector);
            print_color(p.color);
        }
        else if (ft_strcmp(p.type, "cy") == 0)
        {
            printf("CYLINDER\n");
            print_position(p.position);
            print_norm_vec(p.norm_vector);
            printf("Diameter: %f\n",p.diameter);
            printf("Hight: %f\n",p.height);
            print_color(p.color);
        }
        i++;
    }
    return 0;
}

