#include "minirt.h"

void	fill_specular(t_shading *shading, t_comps *comps, t_rt *world,
		float reflect_dot_eye)
{
	create_color(&shading->specular, shading->eff_col.r, shading->eff_col.g,
		shading->eff_col.b);
	mult_tuple(&shading->specular, (world->light.brightness
			* comps->object->material.specular * pow(reflect_dot_eye,
				comps->object->material.shininess)));
}

void	find_diffuse_specular(t_shading *shading, t_comps *comps, t_rt *world)
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
		create_color(&shading->diffuse, shading->eff_col.r, shading->eff_col.g,
			shading->eff_col.b);
		mult_tuple(&shading->diffuse, (comps->object->material.diffuse
				* l_dot));
		create_vector(&negated_light_v, light_v.x, light_v.y, light_v.z);
		negate_tuple(&negated_light_v);
		reflect_vec(&reflect_v, negated_light_v, comps->v_normal);
		reflect_dot_eye = dot_product(reflect_v, comps->v_eye);
		if (reflect_dot_eye <= 0)
			return ;
		else
			fill_specular(shading, comps, world, reflect_dot_eye);
	}
}

void	lighting(t_tuple *color, t_comps *comps, t_rt *world, bool in_shadow)
{
	t_shading	shading;

	if (comps->object->bonus_type == CHECKER)
		create_checkerboard(&shading.eff_col, comps, world->light);
	else
		mult_colors(&shading.eff_col, comps->object->color,
			world->light.color_component);
	mult_colors(&shading.ambient, shading.eff_col, world->amb.amb_component);
	if (in_shadow == true && comps->shadow_factor < 0.04)
		return (create_color(color, shading.ambient.r, shading.ambient.g,
				shading.ambient.b));
	create_color(&shading.diffuse, 0, 0, 0);
	create_color(&shading.specular, 0, 0, 0);
	find_diffuse_specular(&shading, comps, world);
	add_tuples(color, shading.ambient, shading.diffuse);
	add_tuples(color, *color, shading.specular);
	if (in_shadow == true && comps->shadow_factor > 0.04)
		mult_color_scal(color, comps->shadow_factor);
}

void	shade_hit(t_tuple *color, t_rt *world, t_comps *comps,
		uint8_t remaining_depth)
{
	bool	is_shaded;
	t_tuple	reflect_col;
	t_tuple	refract_col;
	float	reflectance;

	create_color(&reflect_col, 0, 0, 0);
	create_color(&refract_col, 0, 0, 0);
	is_shaded = check_shadow(world, comps->over_pos, comps);
	lighting(color, comps, world, is_shaded);
	reflection(&reflect_col, world, comps, remaining_depth);
	refracted_color(&refract_col, world, comps, remaining_depth);
	if (comps->object->material.reflection > 0
		&& comps->object->material.transparency > 0)
	{
		schlick(&reflectance, comps);
		mult_color_scal(&reflect_col, reflectance);
		mult_color_scal(&refract_col, 1.0 - reflectance);
	}
	add_colors(color, *color, reflect_col);
	add_colors(color, *color, refract_col);
}

void	color_at(t_tuple *color, t_rt *world, t_ray *ray,
		uint8_t remaining_depth)
{
	t_comps	comps;

	get_ray_intersections(ray, world);
	get_hit(ray);
	if (ray->is_hit == false)
		return ;
	precompute_values(&comps, ray);
	shade_hit(color, world, &comps, remaining_depth);
}
