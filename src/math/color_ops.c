#include "minirt.h"

/**
 * @brief Multiply RGB components of a color tuple by a scalar.
 *
 * Scales the red, green, and blue components of the given tuple.
 *
 * @param tuple The color tuple (uses .r, .g, .b aliases of t_tuple).
 * @param scalar The multiplier value.
 */
void	mult_color_scal(t_tuple *tuple, float scalar)
{
	tuple->r *= scalar;
	tuple->g *= scalar;
	tuple->b *= scalar;
}


/**
 * @brief Add two colors component-wise.
 *
 * @param c Output color (result of a + b).
 * @param a First input color.
 * @param b Second input color.
 */
void	add_colors(t_tuple *c, const t_tuple a, const t_tuple b)
{
	c->r = a.r + b.r;
	c->g = a.g + b.g;
	c->b = a.b + b.b;
}

/**
 * @brief Subtract one color from another component-wise.
 *
 * @param c Output color (result of a - b).
 * @param a First input color.
 * @param b Second input color to subtract.
 */
void	sub_colors(t_tuple *c, const t_tuple a, const t_tuple b)
{
	c->r = a.r - b.r;
	c->g = a.g - b.g;
	c->b = a.b - b.b;
}

/**
 * @brief Multiply two colors component-wise.
 *
 * Often used for blending or applying material effects.
 *
 * @param tuple Output color (result of a * b).
 * @param a First input color.
 * @param b Second input color.
 */
void	mult_colors(t_tuple *tuple, const t_tuple a, const t_tuple b)
{
	tuple->r = a.r * b.r;
	tuple->g = a.g * b.g;
	tuple->b = a.b * b.b;
}

/**
 * @brief Convert a color from float [0,1] format to packed 32-bit RGBA.
 *
 * Clamps and scales each component to [0, 255] and packs as: 0xRRGGBBAA
 *
 * @param color Input color with float r, g, b, a ∈ [0.0, 1.0].
 * @return 32-bit unsigned int representing packed RGBA.
 */
uint32_t	float_to_hex(const t_tuple color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (uint8_t)(fminf(fmaxf(color.r, 0.0f), 1.0f) * 255.0f);
	g = (uint8_t)(fminf(fmaxf(color.g, 0.0f), 1.0f) * 255.0f);
	b = (uint8_t)(fminf(fmaxf(color.b, 0.0f), 1.0f) * 255.0f);
	a = (uint8_t)(fminf(fmaxf(color.a, 0.0f), 1.0f) * 255.0f);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/**
 * @brief Create a new color from RGB values (alpha set to 1.0).
 *
 * @param color Output tuple to populate.
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void	create_color(t_tuple *color, float r, float g, float b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 1.0f;
}
