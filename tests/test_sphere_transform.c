#include "minirt.h"


int main(void)
{    
    t_transform transf_val = {
        {0, 0, 0, 1},
        {5, 5, 5, 1},
        {10, 5, 7, 1}
    };

    t_primitive sphere;
    t_tuple sp_position = {0, 0, 0, 1};
    create_sphere(&sphere, sp_position);
    
    transform(&sphere.matrix, transf_val);
        
    printf("Final composed matrix:\n");
    print_matrix(sphere.matrix);
    
    // Transform point
/*     t_tuple result;
    t_tuple point = {1, 0, 1, 1};
    mult_matrix_by_tuple(&result, transformed_m, point);

    printf("\nTransformed point: point(%f, %f,%f)\n", result.x, result.y, result.z); */
    return 0;
}
