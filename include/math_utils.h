#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# define EPSILON 0.00002f
# define SHADOW_BIAS 0.0001f
# define DEG_TO_RAD 0.01745329252f

typedef struct s_tuple
{
	union
	{
		float	x;
		float	r;
	};
	union
	{
		float	y;
		float	g;
	};
	union
	{
		float	z;
		float	b;
	};
	union
	{
		float	w;
		float	a;
	};
}	t_tuple;

// color_ops.c
void		mult_color_scal(t_tuple *tuple, float scalar);
void		add_colors(t_tuple *c, const t_tuple a, const t_tuple b);
void		sub_colors(t_tuple *c, const t_tuple a, const t_tuple b);
void		mult_colors(t_tuple *tuple, const t_tuple a, const t_tuple b);
uint32_t	float_to_hex(const t_tuple color);
void		create_color(t_tuple *color, float r, float g, float b);

// vector_math.c
float		magnitude_vector(const t_tuple vector);
void		normalize_vector(t_tuple *vector);
float		dot_product(const t_tuple a, const t_tuple b);
void		cross_product(t_tuple *product, const t_tuple a, const t_tuple b);

// tuple_ops.c
void		add_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void		sub_tuples(t_tuple *c, const t_tuple a, const t_tuple b);
void		negate_tuple(t_tuple *tuple);
void		mult_tuple(t_tuple *tuple, float scalar);

// ft_strtof.c
float		ft_strtof(const char *start);

#endif // MATH_UTILS_H
