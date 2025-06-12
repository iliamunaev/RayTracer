#include "minirt.h"


/* void	ray_transform(t_ray *ray, t_transform transform)
{
	
    t_matrix tmp_m;

    // Rotation
    rotate(&tmp_m, transform.rotate);
    mult_matrix_by_tuple(&ray->origin, tmp_m, ray->origin);
    mult_matrix_by_tuple(&ray->direction, tmp_m, ray->direction);

    // Scaling
    scale(&tmp_m, transform.scale);
    mult_matrix_by_tuple(&ray->origin, tmp_m, ray->origin);
    mult_matrix_by_tuple(&ray->direction, tmp_m, ray->direction);

    // Translation
    translate(&tmp_m, transform.translate);
    mult_matrix_by_tuple(&ray->origin, tmp_m, ray->origin);
    mult_matrix_by_tuple(&ray->direction, tmp_m, ray->direction);

} */

int main() {

    t_ray   ray;
    t_tuple     ray_position = {1, 2, 3, 1};
    t_tuple     ray_vector = {0, 1, 0, 0};

    t_transform transf_val = {
        {0, 0, 0, 1},
        {2, 3, 4, 1},
        {0, 0, 0, 1}
    };
    

    create_ray(&ray, ray_position, ray_vector);

    ray_transform(&ray, transf_val);
    
    printf("position= %f, %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.origin.w);
    printf("direction= %f, %f, %f, %f\n", ray.direction.x, ray.direction.y, ray.direction.z, ray.direction.w);

    return 0;
}