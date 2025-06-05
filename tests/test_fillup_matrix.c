#include "minirt.h"


int	main(void)
{
    t_matrix matrix;
    create_matrix(&matrix, 4);

    float data[16] = {
        1, 2, 3, 4,
        5.5, 6.5, 7.5, 8.5,
        9, 10, 11, 12,
        13.5, 14.5, 15.5, 16.5
    };

    fillup_matrix(&matrix, data);
    printf("0.0 = %f\n", matrix.rows[0].cols[0]);
    printf("0.1 = %f\n", matrix.rows[0].cols[1]);
    printf("0.2 = %f\n", matrix.rows[0].cols[2]);
    printf("0.3 = %f\n", matrix.rows[0].cols[3]);

    printf("1.0 = %f\n", matrix.rows[1].cols[0]);
    printf("1.1 = %f\n", matrix.rows[1].cols[1]);
    printf("1.2 = %f\n", matrix.rows[1].cols[2]);
    printf("1.3 = %f\n", matrix.rows[1].cols[3]);

    printf("2.0 = %f\n", matrix.rows[2].cols[0]);
    printf("2.1 = %f\n", matrix.rows[2].cols[1]);
    printf("2.2 = %f\n", matrix.rows[2].cols[2]);
    printf("2.3 = %f\n", matrix.rows[2].cols[3]);

    printf("3.0 = %f\n", matrix.rows[3].cols[0]);
    printf("3.1 = %f\n", matrix.rows[3].cols[1]);
    printf("3.2 = %f\n", matrix.rows[3].cols[2]);
    printf("3.3 = %f\n", matrix.rows[3].cols[3]);

    return (0);
}
