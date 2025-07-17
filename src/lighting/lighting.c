#include "minirt.h"

/**
 * @brief basic lighting consistent of albedo, reflection, specular + shadow
 *
 * @param color the final color of 1 pixel
 * @param world the main struct
 * @param comps precomputed relevant struct to compute color 
 * (e.g intersection point and object, ray, materials, etc.)
 * @param in_shadow checks if point is in shadow
 * @param light the relevant light in the scene to check
 * 
 */
void	lighting(t_tuple *color, t_comps *comps, bool in_shadow, t_light light)
{
	t_shading	shading;

	if (comps->object->bonus_type == CHECKER)
		create_checkerboard(&shading.eff_col, comps, light);
	else
		mult_colors(&shading.eff_col, comps->object->color,
			light.color_component);
	if (in_shadow == true && comps->shadow_factor < 0.04)
		return (create_color(color, 0, 0, 0));
	create_color(&shading.diffuse, 0, 0, 0);
	create_color(&shading.specular, 0, 0, 0);
	find_diffuse_specular(&shading, comps, light);
	add_tuples(color, shading.diffuse, shading.specular);
	if (in_shadow == true && comps->shadow_factor > 0.04)
		mult_color_scal(color, comps->shadow_factor);
}

/**
 * @brief initializes the phong reflection model to calculate surface color
 *
 * @param color the final color of 1 pixel
 * @param world the main struct
 * @param comps precomputed relevant struct to compute color 
 * (e.g intersection point and object, ray, materials, etc.)
 * 
 */
void	phong_model(t_tuple *color, t_rt *world, t_comps *comps)
{
	t_tuple	light_contrib;
	bool	is_shaded;
	int		i;

	i = 0;
	create_color(&light_contrib, 0, 0, 0);
	while (i < world->lightcount)
	{
		is_shaded = check_shadow(world, comps->over_pos, comps,
				world->lights[i]);
		lighting(&light_contrib, comps, is_shaded, world->lights[i]);
		add_tuples(color, *color, light_contrib);
		i++;
	}
}

/**
 * @brief finds the color at an object point intersected by the ray
 *
 * @param color the final color of 1 pixel
 * @param world the main struct
 * @param comps precomputed relevant struct to compute color 
 * (e.g intersection point and object, ray, materials, etc.)
 * @param remaining_depth recursion depth for refraction and refraction
 * 
 */
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

/**
 * @brief initiates the intersection with 1 ray and the scene objects
 * to find the value of 1 pixel
 *
 * @param color the final color of 1 pixel
 * @param world the main struct
 * @param ray the ray from the camera to spefified pixel on screen
 * @param remaining_depth recursion depth for refraction and refraction
 * 
 */
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
