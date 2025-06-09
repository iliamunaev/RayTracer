#include "minirt.h"


int	main(void)
{
    t_matrix matrix;

    create_identity_matrix(&matrix, 2);

    printf("INIT\n");

    print_matrix(matrix);


    float data[2] = {
        1, 2
    };

    fillup_matrix(&matrix, data);

    printf("Res\n");


    print_matrix(matrix);

    return (0);
}
