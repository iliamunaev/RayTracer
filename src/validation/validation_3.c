#include "minirt.h"

bool	validate_ambient(const t_token *tokens, t_validation_state *v)
{
	if (v->seen_ambient || !is_validate_ambient(tokens))
	{
		err("Error: Duplicate ambient detected");
		return (false);
	}
	v->seen_ambient = true;
	return (true);
}

bool	validate_camera(const t_token *tokens, t_validation_state *v)
{
	if (v->seen_camera || !is_validate_camera(tokens))
	{
		err("Error: Duplicate camera detected");
		return (false);
	}
	v->seen_camera = true;
	return (true);
}

bool	validate_light(const t_token *tokens, t_validation_state *v)
{
	if (v->seen_light || !is_validate_light(tokens))
	{
		err("Error: Duplicate light detected");
		return (false);
	}
	v->seen_light = true;
	return (true);
}
