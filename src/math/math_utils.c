#include "minirt.h"
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
