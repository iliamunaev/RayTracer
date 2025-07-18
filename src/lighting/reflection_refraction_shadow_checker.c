#include "minirt.h"

/**
 * @brief Applies checkerboard pattern to compute the effective color
 * of a surface based on its position in space.
 *
 * @param effective_color output resulting color after applying checker pattern
 * @param comps pointer to precomputed values struct
 * @param light the current light source used for shading
 */
void	create_checkerboard(t_tuple *effective_color, t_comps *comps,
		t_light light)
{
	t_tuple	checker_color2;

	if ((int)(floorf(comps->position.x) + floorf(comps->position.y)
		+ floorf(comps->position.z)) % 2 == 0)
		mult_colors(effective_color, comps->object->color,
			light.color_component);
	else
	{
		checker_color2.r = fmax(0.0f, fmin(1.0f, comps->object->color.r * 0.9
					+ comps->object->color.g * 0.1));
		checker_color2.g = fmax(0.0f, fmin(1.0f, comps->object->color.g * 0.9
					+ comps->object->color.b * 0.1));
		checker_color2.b = fmax(0.0f, fmin(1.0f, comps->object->color.b * 0.9
					+ comps->object->color.r * 0.1));
		checker_color2.r *= 0.85;
		checker_color2.g *= 0.85;
		checker_color2.b *= 0.85;
		mult_colors(effective_color, checker_color2, light.color_component);
	}
}

/**
 * @brief Checks whether a point is in shadow by casting a ray toward the light.
 * Accounts for transparent objects in the shadow path.
 *
 * @param world pointer to the scene
 * @param point the world-space point being shaded
 * @param comps pointer to precomputed values struct
 * @param light the current light source
 * @return true if the point is in shadow, false otherwise
 */
bool	check_shadow(t_rt *world, t_tuple point, t_comps *comps, t_light light)
{
	t_tuple	v_shadow;
	t_ray	r_shadow;
	float	distance;
	t_tuple	direction;

	sub_tuples(&v_shadow, light.position, point);
	distance = magnitude_vector(v_shadow);
	create_vector(&direction, v_shadow.x, v_shadow.y, v_shadow.z);
	normalize_vector(&direction);
	create_ray(&r_shadow, point, direction);
	get_ray_intersections(&r_shadow, world);
	get_hit(&r_shadow);
	if (r_shadow.is_hit == true && r_shadow.hit.value < distance)
	{
		if (r_shadow.hit.object->material.transparency < 0.97)
			comps->shadow_factor = r_shadow.hit.object->material.transparency;
		return (true);
	}
	else
		return (false);
}

/**
 * @brief Computes the color contribution from refraction at a point,
 * based on Snell's law and recursive tracing through transparent objects.
 *
 * @param refract_col output color due to refraction
 * @param world pointer to the scene
 * @param comps pointer to precomputed values struct
 * @param remaining_depth how many recursive refraction/reflection steps remain
 */
void	refracted_color(t_tuple *refract_col, t_rt *world, t_comps *comps,
		uint8_t remaining_depth)
{
	t_refrac_terms	refrac;
	t_tuple			dir_t1;
	t_tuple			dir_t2;
	t_tuple			refract_direction;
	t_ray			refract_ray;

	if (remaining_depth <= 0 || comps->object->material.transparency <= 0.001)
		return (create_color(refract_col, 0, 0, 0));
	refrac.n_ratio = comps->n1 / comps->n2;
	refrac.cos_i = dot_product(comps->v_eye, comps->v_normal);
	refrac.sin2_t = refrac.n_ratio * refrac.n_ratio * (1.0 - refrac.cos_i
			* refrac.cos_i);
	if (refrac.sin2_t > 1.0)
		return (create_color(refract_col, 0, 0, 0));
	refrac.cos_t = sqrtf(1.0 - refrac.sin2_t);
	create_vector(&dir_t1, comps->v_normal.x, comps->v_normal.y,
		comps->v_normal.z);
	mult_color_scal(&dir_t1, (refrac.n_ratio * refrac.cos_i - refrac.cos_t));
	create_vector(&dir_t2, comps->v_eye.x, comps->v_eye.y, comps->v_eye.z);
	mult_color_scal(&dir_t2, refrac.n_ratio);
	sub_tuples(&refract_direction, dir_t1, dir_t2);
	create_ray(&refract_ray, comps->under_pos, refract_direction);
	color_at(refract_col, world, &refract_ray, remaining_depth - 1);
	mult_color_scal(refract_col, comps->object->material.transparency);
}

/**
 * @brief Estimates the reflectance at an intersection using 
 * Schlick’s approximation, which depends on the angle and refractive indices.
 *
 * @param reflectance output reflectance coefficient (0–1)
 * @param comps pointer to precomputed values struct
 */
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

/**
 * @brief Computes the color contribution from reflection at a point,
 * recursively tracing the reflected ray and attenuating based on reflectivity.
 *
 * @param reflect_col output color due to reflection
 * @param world pointer to the scene
 * @param comps pointer to precomputed values struct
 * @param remaining_depth how many recursive reflection steps remain
 */
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
	mult_color_scal(reflect_col, comps->object->material.reflection);
}
