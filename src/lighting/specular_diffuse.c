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

void	find_diffuse_specular(t_shading *shading, t_comps *comps, t_light light)
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
