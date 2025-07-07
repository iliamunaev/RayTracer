#include "minirt.h"

int	main(int argc, char **argv)
{

    // remove on production
    (void)argc;

    t_rt world;

    /* validation stage */
    // validate num of arguments, file name, file extention

	if (parse(argv[1], &world) == EXIT_FAILURE)
    {
        err("Error: parse");
		return (EXIT_FAILURE);
    }





    return (EXIT_SUCCESS);
}
