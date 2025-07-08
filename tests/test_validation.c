#include "minirt.h"

int	main(int argc, char **argv)
{

    t_rt world;

	if (!validate_input_args(argc, argv))
		return (EXIT_FAILURE);

	if (parse(argv[1], &world) == EXIT_FAILURE)
    {
        err("Error: parse");
		return (EXIT_FAILURE);
    }





    return (EXIT_SUCCESS);
}
