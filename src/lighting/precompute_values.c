#include "minirt.h"

/**
 * @brief Sets the first refraction index (n1) for the current intersection,
 * based on the object containers the ray is inside at that point.
 *
 * @param container_count number of active containers (objects ray is inside)
 * @param comps pointer to precomputed values struct
 * @param containers array of object pointers representing the current containers
 */
void	set_first_refraction_index(int container_count, t_comps *comps,
		t_primitive **containers)
{
	if (container_count == 0)
		comps->n1 = 1.0;
	else
		comps->n1 = containers[container_count - 1]->material.refraction;
}

/**
 * @brief Determines the refractive indices n1 and n2 for the point 
 * of intersection.
 *
 * @param comps pointer to precomputed values struct
 * @param ray pointer to the ray being processed
 * @param i current index in the ray's intersection list
 * @param container_count current number of active containers
 */
void	find_refractive_indeces(t_comps *comps, t_ray *ray, uint8_t i,
		int container_count)
{
	t_primitive			*containers[MAX_CONTAINERS];
	t_intersec_point	*ix;

	ft_memset(containers, 0, sizeof(containers));
	while (i < ray->intersections.counter)
	{
		ix = &ray->intersections.intersec_list[i];
		if (ix->value == ray->hit.value)
			set_first_refraction_index(container_count, comps, containers);
		if (containers_includes(containers, container_count, ix->object))
			containers_remove(containers, &container_count, ix->object);
		else
			containers_append(containers, &container_count, ix->object);
		if (ix->value == ray->hit.value)
		{
			if (container_count == 0)
				comps->n2 = 1.0;
			else
				comps->n2 = containers[container_count
					- 1]->material.refraction;
			break ;
		}
		i++;
	}
}

/**
 * @brief Calculates the normal vector at the point of intersection and
 * checks if the intersection occurs from inside the object.
 *
 * @param comps pointer to precomputed values struct
 */
void	precompute_normals_check_if_inside(t_comps *comps)
{
	if (comps->object->type == PLANE)
		create_vector(&comps->v_normal, comps->object->norm_vector.x,
			comps->object->norm_vector.y, comps->object->norm_vector.z);
	else if (comps->object->type == SPHERE)
		get_normal_at(&comps->v_normal, comps->object, comps->position);
	else if (comps->object->type == CYLINDER)
		get_cylinder_normal_at(&comps->v_normal, comps->object,
			comps->position);
	if (dot_product(comps->v_normal, comps->v_eye) < 0)
	{
		comps->inside = true;
		negate_tuple(&comps->v_normal);
	}
	else
		comps->inside = false;
}

/**
 * @brief Precomputes intersection-related data for shading, such as
 * position, normal, eye vector, reflection vector, and refraction indices.
 *
 * @param comps pointer to precomputed values struct
 * @param ray pointer to the intersecting ray
 */
void	precompute_values(t_comps *comps, t_ray *ray)
{
	t_tuple	temp;
	t_tuple	temp2;

	comps->value = ray->hit.value;
	comps->object = ray->hit.object;
	comps->shadow_factor = 1.0f;
	get_position(&comps->position, ray, comps->value);
	create_vector(&comps->v_eye, ray->direction.x, ray->direction.y,
		ray->direction.z);
	negate_tuple(&comps->v_eye);
	normalize_vector(&comps->v_eye);
	precompute_normals_check_if_inside(comps);
	create_vector(&temp, comps->v_normal.x, comps->v_normal.y,
		comps->v_normal.z);
	mult_tuple(&temp, SHADOW_BIAS);
	add_tuples(&comps->over_pos, comps->position, temp);
	create_vector(&temp2, comps->v_normal.x, comps->v_normal.y,
		comps->v_normal.z);
	mult_tuple(&temp2, EPSILON);
	sub_tuples(&comps->under_pos, comps->position, temp);
	reflect_vec(&comps->v_reflection, ray->direction, comps->v_normal);
	comps->n1 = 1.0;
	comps->n2 = 1.0;
	find_refractive_indeces(comps, ray, 0, 0);
}
