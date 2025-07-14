#include "minirt.h"

/**
 * @brief Add two tuples component-wise and store the result.
 *
 * Adds each component of tuple `a` and `b`, stores result in `c`.
 * The `w` component is capped at 1 if it exceeds 1.
 *
 * @param c Resulting tuple.
 * @param a First operand.
 * @param b Second operand.
 */
void	add_tuples(t_tuple *c, const t_tuple a, const t_tuple b)
{
	c->x = a.x + b.x;
	c->y = a.y + b.y;
	c->z = a.z + b.z;
	c->w = a.w + b.w;
	if (c->w > 1)
		c->w = 1;
}

/**
 * @brief Subtract tuple `b` from tuple `a` component-wise and store the result.
 *
 * @param c Resulting tuple.
 * @param a Minuend.
 * @param b Subtrahend.
 */
void	sub_tuples(t_tuple *c, const t_tuple a, const t_tuple b)
{
	c->x = a.x - b.x;
	c->y = a.y - b.y;
	c->z = a.z - b.z;
	c->w = a.w - b.w;
}

/**
 * @brief Negate a tuple (reverse its direction).
 *
 * Multiplies the x, y, and z components by -1.
 *
 * @param tuple The tuple to negate.
 */
void	negate_tuple(t_tuple *tuple)
{
	tuple->x *= -1;
	tuple->y *= -1;
	tuple->z *= -1;
}

/**
 * @brief Multiply a tuple by a scalar.
 *
 * Scales the x, y, and z components.
 *
 * @param tuple Tuple to scale.
 * @param scalar Value to scale with.
 */
void	mult_tuple(t_tuple *tuple, float scalar)
{
	tuple->x *= scalar;
	tuple->y *= scalar;
	tuple->z *= scalar;
}
