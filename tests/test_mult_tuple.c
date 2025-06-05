#include "minirt.h"

int	main(void)
{
    t_tuple tuple = {1, 1, 1, 1};

    mult_tuple(&tuple, 3.4);
    printf("tuple x = %f\n", tuple.x);
    printf("tuple y = %f\n", tuple.y);
    printf("tuple z = %f\n", tuple.z);

       t_tuple tuple_2= {1, 1, 1, 1};


    mult_tuple(&tuple_2, 0);
    printf("tuple x = %f\n", tuple_2.x);
    printf("tuple y = %f\n", tuple_2.y);
    printf("tuple z = %f\n", tuple_2.z);

        t_tuple tuple_3 = {1, 1, 1, 1};

    
    mult_tuple(&tuple_3, 1);
    printf("tuple x = %f\n", tuple_3.x);
    printf("tuple y = %f\n", tuple_3.y);
    printf("tuple z = %f\n", tuple_3.z);

    t_tuple tuple_4 = {1, 1, 1, 1};


    mult_tuple(&tuple_4, 2);
    printf("tuple_4 x = %f\n", tuple_4.x);
    printf("tuple_4 y = %f\n", tuple_4.y);
    printf("tuple_4 z = %f\n", tuple_4.z);

    t_tuple tuple_5 = {1, 1, 1, 1};


    mult_tuple(&tuple_5, -1);
    printf("tuple_5 x = %f\n", tuple_5.x);
    printf("tuple_5 y = %f\n", tuple_5.y);
    printf("tuple_5 z = %f\n", tuple_5.z);


    return (0);
}