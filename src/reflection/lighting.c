#include "minirt.h"

void	create_checkerboard(t_tuple *effective_color, t_tuple point,
		t_primitive *object, t_light light)
{
	t_tuple	checker_color2;

	if ((int)(floorf(point.x) + floorf(point.y) + floorf(point.z)) % 2 == 0)
		mult_colors(effective_color, object->color, light.color_component);
	else
	{
		checker_color2.r = fmax(0.0f, fmin(1.0f, object->color.r * 0.9
					+ object->color.g * 0.1));
		checker_color2.g = fmax(0.0f, fmin(1.0f, object->color.g * 0.9
					+ object->color.b * 0.1));
		checker_color2.b = fmax(0.0f, fmin(1.0f, object->color.b * 0.9
					+ object->color.r * 0.1));
		checker_color2.r *= 0.85;
		checker_color2.g *= 0.85;
		checker_color2.b *= 0.85;
		mult_colors(effective_color, checker_color2, light.color_component);
	}
}

void	find_diffuse_secular(t_tuple *diffuse, t_tuple *specular,
		t_comps *comps, t_tuple *eff_col, t_rt *world)
{
	float	l_dot;
	float	reflect_dot_eye;
	t_tuple	light_v;
	t_tuple	reflect_v;
	t_tuple	negated_light_v;

	sub_tuples(&light_v, world->light.position, comps->position);
	normalize_vector(&light_v);
	l_dot = dot_product(light_v, comps->v_normal);
	if (l_dot >= 0)
	{
		create_color(diffuse, eff_col->r, eff_col->g, eff_col->b);
		mult_tuple(diffuse, (comps->object->material.diffuse * l_dot));
		create_vector(&negated_light_v, light_v.x, light_v.y, light_v.z);
		negate_tuple(&negated_light_v);
		reflect_vec(&reflect_v, negated_light_v, comps->v_normal);
		reflect_dot_eye = dot_product(reflect_v, comps->v_eye);
		if (reflect_dot_eye <= 0)
			return ;
		else
		{
			create_color(specular, eff_col->r, eff_col->g, eff_col->b);
			mult_tuple(specular, (world->light.brightness
					* comps->object->material.specular * pow(reflect_dot_eye,
						comps->object->material.shininess)));
		}
	}
}

void	lighting(t_tuple *color, t_comps *comps, t_rt *world, bool in_shadow)
{
	t_tuple	effective_color;
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	float	factor;

	if (comps->object->bonus_type == CHECKER)
		create_checkerboard(&effective_color, comps->position, comps->object,
			world->light);
	else
		mult_colors(&effective_color, comps->object->color,
			world->light.color_component);
	mult_colors(&ambient, effective_color, world->amb.amb_component);
	// glass comps->objects less shadow?
	if (in_shadow == true)
		return (create_color(color, ambient.r, ambient.g, ambient.b));
	create_color(&diffuse, 0, 0, 0);
	create_color(&specular, 0, 0, 0);
	find_diffuse_secular(&diffuse, &specular, comps, &effective_color, world);
	add_tuples(color, ambient, diffuse);
	add_tuples(color, *color, specular);
}

bool	check_shadow(t_rt *world, t_tuple point)
{
	t_tuple	v_shadow;
	t_ray	r_shadow;
	float	distance;
	t_tuple	direction;

	sub_tuples(&v_shadow, world->light.position, point);
	distance = magnitude_vector(v_shadow);
	create_vector(&direction, v_shadow.x, v_shadow.y, v_shadow.z);
	normalize_vector(&direction);
	create_ray(&r_shadow, point, direction);
	get_ray_intersections(&r_shadow, world);
	get_hit(&r_shadow);
	if (r_shadow.is_hit == true && r_shadow.hit.value < distance)
		return (true);
	else
		return (false);
}

void	refracted_color(t_tuple *refract_col, t_rt *world, t_comps *comps,
		uint8_t remaining_depth)
{
	float	cos_t;
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
	t_tuple	direction_term1;
	t_tuple	direction_term2;
	t_tuple	refract_direction;
	t_ray	refract_ray;

	if (remaining_depth <= 0 || comps->object->material.transparency <= 0.001)
		return (create_color(refract_col, 0, 0, 0));
	n_ratio = comps->n1 / comps->n2;
	cos_i = dot_product(comps->v_eye, comps->v_normal);
	sin2_t = n_ratio * n_ratio * (1.0 - cos_i * cos_i);
	if (sin2_t > 1.0)
		return (create_color(refract_col, 0, 0, 0));
	cos_t = sqrtf(1.0 - sin2_t);
	create_vector(&direction_term1, comps->v_normal.x, comps->v_normal.y,
		comps->v_normal.z);
	mult_color(&direction_term1, (n_ratio * cos_i - cos_t));
	create_vector(&direction_term2, comps->v_eye.x, comps->v_eye.y,
		comps->v_eye.z);
	mult_color(&direction_term2, n_ratio);
	sub_tuples(&refract_direction, direction_term1, direction_term2);
	create_ray(&refract_ray, comps->under_pos, refract_direction);
	color_at(refract_col, world, &refract_ray, remaining_depth - 1);
	mult_color(refract_col, comps->object->material.transparency);
}

void	schlick(float *reflectance, t_comps *comps)
{
	float	cos;
	float	n;
	float	sin2_t;
	float	cos_t;
	float	r0;

	cos = dot_product(comps->v_eye, comps->v_normal);
	if (comps->n1 > comps->n2)
	{
		n = comps->n1 / comps->n2;
		sin2_t = (n * n) * (1.0 - (cos * cos));
		if (sin2_t > 1.0)
		{
			*reflectance = 1.0;
			return ;
		}
		cos_t = sqrtf(1.0 - sin2_t);
		cos = cos_t;
	}
	r0 = ((comps->n1 - comps->n2) / (comps->n1 + comps->n2)) * ((comps->n1
				- comps->n2) / (comps->n1 + comps->n2));
	*reflectance = powf(r0 + (1 - r0) * (1 - cos), 5);
}

void	reflection(t_tuple *reflect_col, t_rt *world, t_comps *comps,
		uint8_t remaining_depth)
{
	t_ray	reflect_ray;

	if (remaining_depth <= 0 || comps->object->material.reflection == 0)
	{
		create_color(reflect_col, 0, 0, 0);
		return ;
	}
	create_ray(&reflect_ray, comps->over_pos, comps->v_reflection);
	color_at(reflect_col, world, &reflect_ray, remaining_depth - 1);
	mult_color(reflect_col, comps->object->material.reflection);
}

void	shade_hit(t_tuple *color, t_rt *world, t_comps *comps, t_ray *ray,
		uint8_t remaining_depth)
{
	bool	is_shaded;
	t_tuple	reflect_col;
	t_tuple	refract_col;
	float	reflectance;

	create_color(&reflect_col, 0, 0, 0);
	create_color(&refract_col, 0, 0, 0);
	is_shaded = check_shadow(world, comps->over_pos);
	lighting(color, comps, world, is_shaded);
	reflection(&reflect_col, world, comps, remaining_depth);
	refracted_color(&refract_col, world, comps, remaining_depth);
	if (comps->object->material.reflection > 0
		&& comps->object->material.transparency > 0)
	{
		schlick(&reflectance, comps);
		mult_color(&reflect_col, reflectance);
		mult_color(&refract_col, 1.0 - reflectance);
	}
	add_colors(color, *color, reflect_col);
	add_colors(color, *color, refract_col);
}

void	color_at(t_tuple *color, t_rt *world, t_ray *ray,
		uint8_t remaining_depth)
{
	t_comps comps;

	get_ray_intersections(ray, world);
	get_hit(ray);
	if (ray->is_hit == false)
		return ;
	precompute_values(&comps, ray);
	shade_hit(color, world, &comps, ray, remaining_depth);
}