#include "minirt.h"

/**
 * @brief Set the default/base material properties for a primitive.
 *
 * This includes general ambient, diffuse, specular, shininess,
 * and sets the primitive to be opaque and non-reflective by default.
 *
 * @param world Pointer to the world scene structure.
 * @param i     Index of the primitive in the scene list.
 */
static inline void	set_base_material(t_rt *world, int i)
{
	world->primitives_list[i].material.ambient = world->amb.brightness;
	world->primitives_list[i].material.diffuse = 0.9;
	world->primitives_list[i].material.specular = 0.1;
	world->primitives_list[i].material.shininess = 50;
	world->primitives_list[i].material.reflection = 0.0;
	world->primitives_list[i].material.transparency = 0;
	world->primitives_list[i].material.refraction = 1;
}

/**
 * @brief Override the material with glass-like properties.
 *
 * Sets high specular reflection, high shininess,
 * partial transparency, and refraction index for glass.
 *
 * @param world Pointer to the world scene structure.
 * @param i     Index of the primitive to update.
 */
static inline void	set_glass_material(t_rt *world, int i)
{
	world->primitives_list[i].material.diffuse = 0.1;
	world->primitives_list[i].material.ambient = 0.1;
	world->primitives_list[i].material.specular = 3.0;
	world->primitives_list[i].material.shininess = 250;
	world->primitives_list[i].material.reflection = 0.95;
	world->primitives_list[i].material.transparency = 0.8;
	world->primitives_list[i].material.refraction = 1.52;
}

/**
 * @brief Assign material settings to each primitive in the scene.
 *
 * Starts by applying base material to all objects, then modifies
 * properties based on bonus types (e.g., GLASS, CHECKER).
 *
 * @param obj_count Pointer to total number of primitives in the scene.
 * @param world     Pointer to world structure containing all scene data.
 */
void	set_material(int *obj_count, t_rt *world)
{
	int	i;

	i = 0;
	while (i < *obj_count)
	{
		set_base_material(world, i);
		if (world->primitives_list[i].bonus_type == GLASS)
			set_glass_material(world, i);
		if (world->primitives_list[i].bonus_type == CHECKER)
			world->primitives_list[i].material.reflection = 0.4;
		i++;
	}
}
