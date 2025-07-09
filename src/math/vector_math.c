#include "minirt.h"

/**
 * @brief Compute the dot product of two 3D vectors.
 *
 * Ignores the `w` component of the tuples.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return The scalar dot product.
 */
float	dot_product(const t_tuple a, const t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Compute the cross product of two 3D vectors.
 *
 * The result is stored in the `product` tuple.
 *
 * @param product Pointer to the result vector.
 * @param a First vector.
 * @param b Second vector.
 */
void	cross_product(t_tuple *product, const t_tuple a, const t_tuple b)
{
	product->x = a.y * b.z - a.z * b.y;
	product->y = a.z * b.x - a.x * b.z;
	product->z = a.x * b.y - a.y * b.x;
}

/**
 * @brief Compute the magnitude (length) of a 3D vector.
 *
 * @param v The vector whose magnitude is to be computed.
 * @return The length of the vector.
 */
float	magnitude_vector(const t_tuple v)
{
	return (sqrtf(dot_product(v, v)));
}

/**
 * @brief Normalize a 3D vector to unit length.
 *
 * Divides each component of the vector by its magnitude.
 *
 * @param vector Pointer to the vector to normalize.
 */
void	normalize_vector(t_tuple *vector)
{
	float	m;

	m = magnitude_vector(*vector);
	vector->x /= m;
	vector->y /= m;
	vector->z /= m;
}
