#ifndef PRIMITIVES_H
# define PRIMITIVES_H

/*------FORWARD DECLARATIONS-----------------------------------------*/
typedef struct s_rt		t_rt;
typedef struct s_ray	t_ray;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}						t_type;

typedef enum e_bonus
{
	GLASS,
	CHECKER,
	DEFAULT
}						t_bonus;

typedef struct s_material
{
	t_tuple				color;
	float				ambient;
	float				diffuse;
	float				specular;
	float				shininess; // between 10 and 200
	float				reflection;
	float				transparency;
	float				refraction;
}						t_material;

typedef struct s_primitive
{
	int					id;
	t_type				type;
	t_bonus				bonus_type;
	t_tuple				position;
	t_tuple				norm_vector;
	t_tuple				color;
	float				cylinder_min;
	float				cylinder_max;
	float				diameter;
	float				height;
	t_material			material;
	t_matrix			matrix;
	t_matrix			inv_matrix;
	t_matrix			tran_matrix;
}						t_primitive;

typedef struct s_amb
{
	float				brightness;
	t_tuple				color;
	t_tuple				amb_component;
	t_matrix			matrix;
}						t_amb;

typedef struct s_cam
{
	t_tuple				position;
	t_tuple				norm_vector;
	float				fov;
	float				pix_size;
	float				half_width;
	float				half_height;
	float				half_view;
	t_matrix			matrix;
	t_matrix			inv_matrix;
}						t_cam;

typedef struct s_light
{
	t_tuple				position;
	float				brightness;
	t_tuple				color;
	t_tuple				color_component;
	t_matrix			matrix;
}						t_light;

// transform_cam_view.c
void					transform_cam_view(t_rt *rt, t_tuple from, t_tuple to,
							t_tuple up);
void					rebuild_camera(t_rt *rt);

// CAMERA
// bool is_zero_vector(t_tuple v);
float					get_half_view(t_rt *rt);
float					get_half_height(t_rt *rt);
float					get_half_width(t_rt *rt);
float					get_pixel_size(t_rt *rt);

void					ray_for_pixel(t_ray *ray, t_cam *cam, float px,
							float py);

// primitive_intersections.c
void					intersect_plane(t_ray *ray, t_primitive *plane);
void					intersect_caps(t_ray *ray, t_primitive *cylinder);
void					intersect_cylinder(t_ray *ray, t_primitive *cylinder);

// SPHERE

#endif // PRIMITIVES_H
