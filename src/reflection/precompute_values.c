#include "minirt.h"

void precompute_values(t_comps *comps, t_ray *ray)
{
    t_tuple temp;

    comps->value = ray->hit.value;
    comps->object = ray->hit.object;
    get_position(&comps->position, ray, comps->value);
    create_vector(&comps->v_eye, ray->direction.x, ray->direction.y, ray->direction.z);
    negate_tuple(&comps->v_eye);
    normalize_vector(&comps->v_eye);
    if (comps->object->type == PLANE)
        create_vector(&comps->v_normal, comps->object->norm_vector.x, comps->object->norm_vector.y, comps->object->norm_vector.z);
    else if (comps->object->type == SPHERE)
        get_normal_at(&comps->v_normal, comps->object, comps->position);
    else if (comps->object->type == CYLINDER)
        get_cylinder_normal_at(&comps->v_normal, comps->object, comps->position);
    if (dot_product(comps->v_normal, comps->v_eye) < 0)
    {
        comps->inside = true;
        negate_tuple(&comps->v_normal);
    }
    else
        comps->inside = false;
    create_vector(&temp, comps->v_normal.x, comps->v_normal.y, comps->v_normal.z);
    mult_tuple(&temp, EPSILON);
    add_tuples(&comps->over_pos, comps->position, temp);
    reflect_vec(&comps->v_reflection,ray->direction, comps->v_normal);
}

