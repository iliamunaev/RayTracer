#include "minirt.h"

bool	has_too_many_tokens(const t_token *tokens)
{
	if (tokens->token[6][0] != '\0')
	{
		err("Too many tokens in a line (max is 6)");
		return (true);
	}
	return (false);
}

bool	is_identifier_valid(const char *id)
{
	if (!id || id[0] == '\0')
	{
		err("Empty identifier");
		return (false);
	}
	return (true);
}
