#include "minirt.h"

/**
 * @brief Skips leading whitespace and parses optional sign.
 *
 * Advances the string pointer past any leading spaces and checks
 * for a '+' or '-' sign to determine the number's sign.
 *
 * @param s The input string.
 * @param sign Pointer to an int where the sign will be stored.
 *             Set to -1 for negative numbers, 1 otherwise.
 * @return Pointer to the next character after sign.
 */
static inline const char	*skip_whitespace_and_sign(
	const char *s, int *sign)
{
	while (*s == ' ')
		s++;
	if (*s == '-')
	{
		*sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	return (s);
}

/**
 * @brief Parses the integer part of the number.
 *
 * Scans digit characters and accumulates them into the integer part.
 *
 * @param s The input string starting at the first digit.
 * @param int_part Pointer to float where the integer part is stored.
 * @return Pointer to the next character after the last digit.
 */
static inline const char	*parse_integer_part(
	const char *s, float *int_part)
{
	while (*s >= '0' && *s <= '9')
	{
		*int_part = *int_part * 10.0f + (*s - '0');
		s++;
	}
	return (s);
}

/**
 * @brief Parses the fractional (decimal) part of the number.
 *
 * Scans digit characters after the dot and accumulates the fractional part.
 *
 * @param s The input string starting after the dot.
 * @param frac_part Pointer to float where the fraction will be accumulated.
 */
static inline void	parse_fractional_part(
	const char *s, float *frac_part)
{
	float	divider;

	divider = 10.0f;
	while (*s >= '0' && *s <= '9')
	{
		*frac_part += (*s - '0') / divider;
		divider *= 10.0f;
		s++;
	}
}

/**
 * @brief Parses both integer and fractional parts from the string.
 *
 * Combines integer and fractional parsing logic. If a dot is found,
 * the fractional part will be parsed as well.
 *
 * @param s The input string after sign processing.
 * @param int_part Pointer to float for storing integer value.
 * @param frac_part Pointer to float for storing fractional value.
 */
static inline void	extract_parts(
	const char *s, float *int_part, float *frac_part)
{
	s = parse_integer_part(s, int_part);
	if (*s == '.')
		parse_fractional_part(s + 1, frac_part);
}

/**
 * @brief Converts a string to a floating-point number.
 *
 * This function parses a C string containing a decimal number
 * and returns its float representation. Handles optional whitespace
 * and sign. Does not support exponent notation.
 *
 * @param start Pointer to the input string.
 * @return The float value parsed from the string.
 */
float	ft_strtof(const char *start)
{
	float	result;
	float	fraction;
	int		sign;

	result = 0.0f;
	fraction = 0.0f;
	sign = 1;
	start = skip_whitespace_and_sign(start, &sign);
	extract_parts(start, &result, &fraction);
	return (sign * (result + fraction));
}
