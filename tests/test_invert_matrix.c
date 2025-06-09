#include "minirt.h"


// void	invert_matrix(t_matrix *inverted, const t_matrix matrix)

int	main(void)
{
    t_matrix inverted;
    t_matrix m_a;
    t_matrix m_b;
    t_matrix m_c;
    t_matrix result;


    float data[16] = {
        3, -9, 7, 3,
        3, -8, 2, -9,
        -4, 4, 4, 1,
        -6, 5, -1, 1
    };
    float data_2[16] = {
        8, 2, 2, 2,
        3, -1, 7, 0,
        7, 0, 5, 4,
        6, -2, 0, 5
    };





    create_matrix_4x4(&m_a, data);
    printf("Res\n");
    print_matrix(m_a);

    printf("\n");

    create_matrix_4x4(&m_b, data_2);
    printf("Res_2\n");
    print_matrix(m_b);

    printf("\n");


    mult_matxs(&m_c, m_a, m_b);


    invert_matrix(&inverted, m_b);

    mult_matxs(&result, m_c, inverted);


    printf(" result = \n");
    print_matrix(result);

    return (0);
}
