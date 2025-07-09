#include "minirt.h"

/**
 * @brief Multiply RGB components of a color tuple by a scalar.
 *
 * Scales the red, green, and blue components of the given tuple.
 *
 * @param tuple The color tuple (uses .r, .g, .b aliases of t_tuple).
 * @param scalar The multiplier value.
 */
void	mult_color(t_tuple *tuple, float scalar)
{
	tuple->r *= scalar;
	tuple->g *= scalar;
	tuple->b *= scalar;
}
