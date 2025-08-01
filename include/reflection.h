#ifndef REFLECTION_H
# define REFLECTION_H

# define MAX_CONTAINERS 10

// # include "minirt.h"
/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_primitive	t_primitive;
typedef struct s_light		t_light;
typedef struct s_ray		t_ray;

typedef struct s_comps
{
	t_primitive	*object;
	float		value;
	float		n1;
	float		n2;
	float		shadow_factor;
	uint8_t		depth_counter;
	t_tuple		position;
	t_tuple		over_pos;
	t_tuple		under_pos;
	t_tuple		v_eye;
	t_tuple		v_normal;
	t_tuple		v_reflection;
	bool		inside;
}	t_comps;

typedef struct s_refrac_terms
{
	float	cos_t;
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
}	t_refrac_terms;

typedef struct s_shading
{
	t_tuple	eff_col;
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
}	t_shading;

void	get_normal_at(t_tuple *normal, t_primitive *object,
			t_tuple world_point);
void	get_cylinder_normal_at(t_tuple *normal, t_primitive *object,
			t_tuple world_point);
void	reflect_vec(t_tuple *reflected, t_tuple vector_in, t_tuple normal);
void	lighting(t_tuple *color, t_comps *comps, bool in_shadow, t_light light);
void	precompute_values(t_comps *comps, t_ray *ray);
void	color_at(t_tuple *color, t_rt *world, t_ray *ray,
			uint8_t remaining_depth);

// refraction containers
bool	containers_includes(t_primitive **containers, int count,
			t_primitive *obj);
void	containers_remove(t_primitive **containers, int *count,
			t_primitive *obj);
void	containers_append(t_primitive **containers, int *count,
			t_primitive *obj);

// reflection_refraction_shadow_checker

void	create_checkerboard(t_tuple *effective_color, t_comps *comps,
			t_light light);
bool	check_shadow(t_rt *world, t_tuple point, t_comps *comps, t_light light);
void	refracted_color(t_tuple *refract_col, t_rt *world, t_comps *comps,
			uint8_t remaining_depth);
void	schlick(float *reflectance, t_comps *comps);
void	reflection(t_tuple *reflect_col, t_rt *world, t_comps *comps,
			uint8_t remaining_depth);

//specular_diffuse.c
void	fill_specular(t_shading *shading, t_comps *comps, t_light light,
			float reflect_dot_eye);
void	find_diffuse_specular(t_shading *shading, t_comps *comps,
			t_light light);

#endif