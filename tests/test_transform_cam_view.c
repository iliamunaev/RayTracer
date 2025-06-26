# include "minirt.h"

int main(int c, char **av)
{

    t_rt    rt;

    if (parse(av[1], &rt) == EXIT_FAILURE)
    {
        err("Error");
		return (EXIT_FAILURE);
    }

    t_tuple from = {0, 0, 0, 1};
    t_tuple to = {4, -2, 8, 1};
    t_tuple up = {1, 1, 0, 1};


    transform_cam_view(&rt, from, to, up);

    print_matrix(rt.primitives_list[0].matrix);

    return 0;
}

