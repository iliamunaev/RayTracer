#include "minirt.h"


int main(void)
{    
    t_rt minirt;
    minirt.obj_counted = 1;

    t_ray ray;
    t_tuple origin = {0,0,-5,1};
    t_tuple direction = {0,0,1,0};

    create_ray(&ray, origin, direction);


    t_transform transf_val = {
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {5, 0, 0, 1}
    };

    
    t_primitive sphere;
    t_tuple sp_position = {0, 0, 0, 1};
    create_sphere(&sphere, sp_position);    
    transform(&sphere.matrix, transf_val);
    printf("Final matrix:\n");
    print_matrix(sphere.matrix);

    minirt.primitives_list[0] = sphere;

    t_matrix inverse_matrix;
    invert_matrix(&inverse_matrix, minirt.primitives_list[0].matrix);

    ray_transform(&ray, inverse_matrix);
    get_ray_intersections(&ray, minirt);
    printf("counter = %f\n", ray.intersections.counter);
    printf("instersection 1 = %f\n", ray.intersections.intersec_list[0].value);
    printf("instersection 2 = %f\n", ray.intersections.intersec_list[1].value);

    return 0;
}
