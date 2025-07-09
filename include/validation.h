#ifndef VALIDATION_H
# define VALIDATION_H

// validation_1.c
bool	is_line_valid(t_token *tokens, t_validation_state *vstate);

// validation_2.c
bool	validate_ambient(t_token *tokens, t_validation_state *v);
bool	validate_camera(t_token *tokens, t_validation_state *v);
bool	validate_light(t_token *tokens, t_validation_state *v);

// validate_file.c
bool	validate_input_args(int argc, char **argv);

//validate_primitives.c
bool	is_validate_sphere(t_token *token);
bool	is_validate_plane(t_token *token);
bool	is_validate_cylinder(t_token *token);

//validate_cam_light.c
bool	is_validate_ambient(t_token *token);
bool	is_validate_camera(t_token *token);
bool	is_validate_light(t_token *token);

//validation_utils.c
bool	is_float_in_range(char *s, float min, float max);
bool	is_vec3_unbounded(char *s);
bool	is_vec3_normalized(char *s);
bool	is_color_rgb(char *s);

#endif // VALIDATION_H