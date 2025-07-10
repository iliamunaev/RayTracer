#include "minirt.h"

void	intersect_plane(t_ray *ray, t_primitive *plane)
{
	t_ray	inv_ray;
	float	t;

	create_ray(&inv_ray, ray->origin, ray->direction);
	ray_transform(&inv_ray, plane->inv_matrix);
	if (fabsf(inv_ray.direction.y) < EPSILON)
		return ;
	t = -inv_ray.origin.y / inv_ray.direction.y;
	if (t < EPSILON)
		return ;
	ray->intersections.intersec_list[ray->intersections.counter].object = plane;
	ray->intersections.intersec_list[ray->intersections.counter].value = t;
	ray->intersections.counter++;
}

static float	check_caps(t_ray inv_ray, float t)
{
	return (pow((inv_ray.origin.x + t * inv_ray.direction.x), 2)
		+ pow((inv_ray.origin.z + t * inv_ray.direction.z), 2));
}

void	intersect_caps(t_ray *ray, t_primitive *c)
{
	t_ray	inv_ray;
	float	t0;
	float	t1;

	create_ray(&inv_ray, ray->origin, ray->direction);
	ray_transform(&inv_ray, c->inv_matrix);
	if (fabs(inv_ray.direction.y) < EPSILON)
		return ;
	t0 = (c->cylinder_min - inv_ray.origin.y) / inv_ray.direction.y;
	if (check_caps(inv_ray, t0) <= 1)
	{
		ray->intersections.intersec_list[ray->intersections.counter].object = c;
		ray->intersections.intersec_list[ray->intersections.counter].value = t0;
		ray->intersections.counter++;
	}
	t1 = (c->cylinder_max - inv_ray.origin.y) / inv_ray.direction.y;
	if (check_caps(inv_ray, t1) <= 1)
	{
		ray->intersections.intersec_list[ray->intersections.counter].object = c;
		ray->intersections.intersec_list[ray->intersections.counter].value = t1;
		ray->intersections.counter++;
	}
}

void	assign_cylinder_hits(t_tuple ab_dis, t_primitive *c, t_ray *ray,
		t_ray inv_ray)
{
	float	t0;
	float	t1;
	float	y0;
	float	y1;

	t0 = (float)((-ab_dis.y - sqrt(ab_dis.z)) / (2 * ab_dis.x));
	y0 = inv_ray.origin.y + t0 * inv_ray.direction.y;
	if (c->cylinder_min < y0 && y0 < c->cylinder_max)
	{
		ray->intersections.intersec_list[ray->intersections.counter].object = c;
		ray->intersections.intersec_list[ray->intersections.counter].value = t0;
		ray->intersections.counter++;
	}
	t1 = (float)((-ab_dis.y + sqrt(ab_dis.z)) / (2 * ab_dis.x));
	y1 = inv_ray.origin.y + t1 * inv_ray.direction.y;
	if (c->cylinder_min < y1 && y1 < c->cylinder_max)
	{
		ray->intersections.intersec_list[ray->intersections.counter].object = c;
		ray->intersections.intersec_list[ray->intersections.counter].value = t1;
		ray->intersections.counter++;
	}
}

void	intersect_cylinder(t_ray *ray, t_primitive *cylinder)
{
	float	a;
	float	b;
	float	discriminant;
	t_tuple	ab_dis;
	t_ray	inv_ray;

	create_ray(&inv_ray, ray->origin, ray->direction);
	ray_transform(&inv_ray, cylinder->inv_matrix);
	a = inv_ray.direction.x * inv_ray.direction.x + inv_ray.direction.z
		* inv_ray.direction.z;
	if (a < EPSILON)
		return ;
	b = 2 * inv_ray.origin.x * inv_ray.direction.x + 2 * inv_ray.origin.z
		* inv_ray.direction.z;
	discriminant = pow(b, 2) - 4 * a * (inv_ray.origin.x * inv_ray.origin.x
			+ inv_ray.origin.z * inv_ray.origin.z - 1);
	if (discriminant < 0)
		return ;
	create_point(&ab_dis, a, b, discriminant);
	assign_cylinder_hits(ab_dis, cylinder, ray, inv_ray);
}
