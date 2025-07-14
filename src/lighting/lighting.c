#include "minirt.h"

void	fill_specular(t_shading *shading, t_comps *comps, t_light light,
		float reflect_dot_eye)
{
	create_color(&shading->specular, shading->eff_col.r, shading->eff_col.g,
		shading->eff_col.b);
	mult_tuple(&shading->specular, (light.brightness
			* comps->object->material.specular * pow(reflect_dot_eye,
				comps->object->material.shininess)));
}

void	find_diffuse_specular(t_shading *shading, t_comps *comps ,t_light light)
{
	float	l_dot;
	float	reflect_dot_eye;
	t_tuple	light_v;
	t_tuple	reflect_v;
	t_tuple	negated_light_v;

	sub_tuples(&light_v, light.position, comps->position);
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
			fill_specular(shading, comps, light, reflect_dot_eye);
	}
}

void	lighting(t_tuple *color, t_comps *comps, bool in_shadow, t_light light)
{
	t_shading	shading;

	if (comps->object->bonus_type == CHECKER)
		create_checkerboard(&shading.eff_col, comps, light);
	else
		mult_colors(&shading.eff_col, comps->object->color,
			light.color_component);
	//mult_colors(&shading.ambient, shading.eff_col, world->amb.amb_component);
	if (in_shadow == true && comps->shadow_factor < 0.04)
		return (create_color(color, 0, 0, 0));
	create_color(&shading.diffuse, 0, 0, 0);
	create_color(&shading.specular, 0, 0, 0);
	find_diffuse_specular(&shading, comps, light);
	//add_tuples(color, shading.ambient, shading.diffuse);
	add_tuples(color, shading.diffuse, shading.specular);
	 if (in_shadow == true && comps->shadow_factor > 0.04)
		mult_color_scal(color, comps->shadow_factor); 
}

void	phong_model(t_tuple *color, t_rt *world, t_comps *comps)
{
	t_tuple light_contrib;
	bool	is_shaded;
	int		i;

	i = 0;
	create_color(&light_contrib, 0, 0, 0);

	while (i < world->lightcount)
	{
		is_shaded = check_shadow(world, comps->over_pos, comps, world->lights[i]);
		lighting(&light_contrib, comps, is_shaded, world->lights[i]);
		add_tuples(color, *color, light_contrib);
		i++;
	}
}

void	shade_hit(t_tuple *color, t_rt *world, t_comps *comps,
		uint8_t remaining_depth)
{
	t_tuple	reflect_col;
	t_tuple	refract_col;
	t_tuple	ambient;
	float	reflectance;

	create_color(color, 0, 0, 0);
	create_color(&reflect_col, 0, 0, 0);
	create_color(&refract_col, 0, 0, 0);
	mult_colors(&ambient, comps->object->color, world->amb.amb_component);
	add_tuples(color, *color, ambient);
	phong_model(color, world, comps);
	reflection(&reflect_col, world, comps, remaining_depth);
	refracted_color(&refract_col, world, comps, remaining_depth);
	if (comps->object->material.reflection > 0
		&& comps->object->material.transparency > 0)
	{
		schlick(&reflectance, comps);
		mult_color_scal(&reflect_col, reflectance);
		mult_color_scal(&refract_col, 1.0 - reflectance);
	}
	add_tuples(color, *color, reflect_col);
	add_tuples(color, *color, refract_col);
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
