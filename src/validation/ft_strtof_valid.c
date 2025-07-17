#include "minirt.h"

/**
 * @brief Skips leading whitespace characters in a string.
 *
 * @param s The input C-string.
 * @return A pointer to the first non-space character.
 */
static inline const char	*skip_whitespace(const char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

/**
 * @brief Parses an optional sign (+/-) at the beginning of the string.
 *
 * If the character is '-', sets *sign to -1. If '+', sign remains 1.
 *
 * @param s The input C-string.
 * @param sign A pointer to an int to store the parsed sign.
 * @return A pointer to the next character after the sign (if any).
 */
static inline const char	*parse_sign(const char *s, int *sign)
{
	if (*s == '-')
	{
		*sign = -1;
		return (s + 1);
	}
	else if (*s == '+')
		return (s + 1);
	return (s);
}

/**
 * @brief Parses the integer part of a float number from a string.
 *
 * Accumulates digits into `result` and sets `has_digits` 
 * to true if digits are found.
 *
 * @param s The input string.
 * @param result Pointer to store the parsed integer part.
 * @param has_digits Pointer to a flag indicating if at least 
 * one digit was parsed.
 * @return A pointer to the character after the last digit.
 */
static inline const char	*parse_integer_part(const char *s,
	float *result, bool *has_digits)
{
	while (*s >= '0' && *s <= '9')
	{
		*result = *result * 10.0f + (*s - '0');
		s++;
		*has_digits = true;
	}
	return (s);
}

/**
 * @brief Parses the fractional part of a float number from a string.
 *
 * Accumulates digits after a decimal point into `fraction` and sets 
 * `has_digits` to true if digits are found.
 *
 * @param s The input string.
 * @param fraction Pointer to store the fractional part.
 * @param has_digits Pointer to a flag indicating if at least 
 * one digit was parsed.
 * @return A pointer to the character after the last digit.
 */
static inline const char	*parse_fractional_part(const char *s,
	float *fraction, bool *has_digits)
{
	float	divider;

	divider = 10.0f;
	while (*s >= '0' && *s <= '9')
	{
		*fraction += (*s - '0') / divider;
		divider *= 10.0f;
		s++;
		*has_digits = true;
	}
	return (s);
}

/**
 * @brief Validates that the string represents a valid float.
 *
 * Parses and validates a floating-point number (without exponent support).
 * Will exit with an error if the string is invalid or contains 
 * garbage after the number.
 *
 * @param s The input string to validate.
 * @param has_digits A pointer to a flag set to true if the input 
 * contained valid digits.
 */
void	ft_strtof_valid(const char *s, bool *has_digits)
{
	float	result;
	float	fraction;
	int		sign;

	result = 0.0f;
	fraction = 0.0f;
	sign = 1;
	if (!s || !has_digits)
		err("Error\nnull input");
	*has_digits = false;
	s = skip_whitespace(s);
	s = parse_sign(s, &sign);
	s = parse_integer_part(s, &result, has_digits);
	if (*s == '.')
		s = parse_fractional_part(s + 1, &fraction, has_digits);
	s = skip_whitespace(s);
	if (!(*has_digits) || *s != '\0')
	{
		*has_digits = false;
		err("Error\ninvalid format");
	}
}
