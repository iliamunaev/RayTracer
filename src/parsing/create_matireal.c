
#include "minirt.h"

void	create_material(t_rt *rt)
{
	int		i;
	float	amb_light;

	amb_light = rt->amb.brightness;
	i = 0;
	while (i < rt->obj_counted)
	{
		rt->primitives_list[i].material.ambient = amb_light;
		rt->primitives_list[i].material.diffuse = 0.9;
		rt->primitives_list[i].material.specular = 0.1;
		rt->primitives_list[i].material.shininess = 50;
		if (rt->primitives_list[i].type == PLANE)
		{
			rt->primitives_list[i].material.reflection = 0.7;
			rt->primitives_list[i].material.transparency = 0;
			rt->primitives_list[i].material.refraction = 1;
		}
		else if (rt->primitives_list[i].type == SPHERE)
		{
			rt->primitives_list[i].material.reflection = 0.7;
			rt->primitives_list[i].material.transparency = 1;
			rt->primitives_list[i].material.refraction = 1.52;
		}
		else
		{
			rt->primitives_list[i].material.reflection = 0;
			rt->primitives_list[i].material.transparency = 0;
			rt->primitives_list[i].material.refraction = 1;
		}
		i++;
	}
}
