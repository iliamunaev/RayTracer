#include "minirt.h"


// void	invert_matrix(t_matrix *inverted, const t_matrix matrix)

int	main(void)
{
    t_matrix inverted;
    t_matrix matrix;

        float data[16] = {
        -5, 2, 6, -8,
        1, -5, 1, 8,
        7, 7, -6, -7,
        1, -3, 7, 4
    };





    create_matrix_4x4(&matrix, data);
    printf("Res\n");
    print_matrix(matrix);

    
    printf("\n");

    invert_matrix(&inverted, matrix);

      print_matrix(inverted);


    return (0);
}
