#include "minirt.h"

void	sort_intersec_list(t_intersec_point *intersec_list, int count)
{
	uint8_t				i;
	int8_t				j;
	t_intersec_point	key;

	i = 1;
	while (i < count)
	{
		key = intersec_list[i];
		j = i - 1;
		while (j >= 0 && intersec_list[j].value > key.value)
		{
			intersec_list[j + 1] = intersec_list[j];
			j--;
		}
		intersec_list[j + 1] = key;
		i++;
	}
}

void	get_ray_intersections(t_ray *ray, t_rt *minirt)
{
	uint8_t	i;

	ray->intersections.counter = 0;
	i = 0;
	while (i < minirt->obj_counted)
	{
		if (minirt->primitives_list[i].type == SPHERE)
			get_obj_intersec(ray, &minirt->primitives_list[i], 0, 0);
		else if (minirt->primitives_list[i].type == PLANE)
			intersect_plane(ray, &minirt->primitives_list[i]);
		else if (minirt->primitives_list[i].type == CYLINDER)
		{
			intersect_cylinder(ray, &minirt->primitives_list[i]);
			intersect_caps(ray, &minirt->primitives_list[i]);
		}
		i++;
	}
	sort_intersec_list(ray->intersections.intersec_list,
		ray->intersections.counter);
}

void	get_obj_intersec(t_ray *ray, t_primitive *obj, float a, float b)
{
	float	c;
	float	discriminant;
	t_tuple	sphere_to_ray;
	t_ray	inv_ray;
	t_tuple	zero_pos;

	create_point(&zero_pos, 0, 0, 0);
	create_ray(&inv_ray, ray->origin, ray->direction);
	ray_transform(&inv_ray, obj->inv_matrix);
	a = dot_product(inv_ray.direction, inv_ray.direction);
	sub_tuples(&sphere_to_ray, inv_ray.origin, zero_pos);
	b = 2 * dot_product(inv_ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return ;
	ray->intersections.intersec_list[ray->intersections.counter].object = obj;
	ray->intersections.intersec_list[ray->intersections.counter].value = ((-b
				- sqrtf(discriminant)) / (2 * a));
	ray->intersections.counter++;
	ray->intersections.intersec_list[ray->intersections.counter].object = obj;
	ray->intersections.intersec_list[ray->intersections.counter].value = ((-b
				+ sqrtf(discriminant)) / (2 * a));
	ray->intersections.counter++;
}

void	get_hit(t_ray *ray)
{
	uint8_t	i;

	i = 0;
	ray->is_hit = false;
	ray->hit.value = -1.0f;
	while (i < ray->intersections.counter)
	{
		if (ray->intersections.intersec_list[i].value >= 0)
		{
			ray->hit = ray->intersections.intersec_list[i];
			ray->is_hit = true;
			return ;
		}
		i++;
	}
}
