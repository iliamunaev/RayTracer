#include "minirt.h"

/* void precompute_values(t_comps *comps, t_ray *ray)
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
    mult_tuple(&temp, EPSILON * 2);
    add_tuples(&comps->over_pos, comps->position, temp);
    reflect_vec(&comps->v_reflection, ray->direction, comps->v_normal);
}
 */

 bool containers_includes(t_primitive **containers, int count, t_primitive *obj)
{
    int i;
    
    i = 0;
    while (i < count)
    {
        if (containers[i] == obj)
            return true;
        i++;
    }
    return false;
}

void containers_remove(t_primitive **containers, int *count, t_primitive *obj)
{
    int i;
    int j
;
    i = 0;
    while (i < *count)
    {
        if (containers[i] == obj)
            break;
        i++;
    }
    j = i;
    while (j < *count - 1)
    {
        containers[j] = containers[j + 1];
        j++;
    }
    --(*count);
}

void containers_append(t_primitive **containers, int *count, t_primitive *obj)
{
    if (*count < MAX_CONTAINERS)
    {
        containers[*count] = obj;
        ++(*count);
    }
    else
    {
        // Handle error: too many nested containers
    }
}


 void precompute_values(t_comps *comps, t_ray *ray)
{
    t_tuple temp;
    t_primitive *containers[MAX_CONTAINERS];
    t_intersec_point *ix;
    int container_count;
    int i;
    
    container_count = 0;
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
    mult_tuple(&temp, EPSILON * 2);
    add_tuples(&comps->over_pos, comps->position, temp);
    sub_tuples(&comps->under_pos, comps->position, temp);
    reflect_vec(&comps->v_reflection, ray->direction, comps->v_normal);
    i = 0;
    while (i < MAX_CONTAINERS)
    {
        containers[i] = NULL;
        i++;
    }

    i = 0;
    comps->n1 = 1.0;
    comps->n2 = 1.0;

    while (i < ray->intersections.counter)
    {
        ix = &ray->intersections.intersec_list[i];
        if (ix->value == ray->hit.value)
        {
            if (container_count == 0)
                comps->n1 = 1.0;
            else
                comps->n1 = containers[container_count - 1]->material.refraction;
        }
        if (containers_includes(containers, container_count, ix->object))
            containers_remove(containers, &container_count, ix->object);
        else
            containers_append(containers, &container_count, ix->object);
        if (ix->value == ray->hit.value)
        {
            if (container_count == 0)
                comps->n2 = 1.0;
            else
                comps->n2 = containers[container_count - 1]->material.refraction;
            break;
        }

        i++;
    }

}
