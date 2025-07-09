#ifndef VALIDATION_H
# define VALIDATION_H

// validation_1.c
bool	is_line_valid(t_token *tokens);

// validation_2.c
bool	validate_ambient(t_token *tokens);
bool	validate_camera(t_token *tokens);
bool	validate_light(t_token *tokens);

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
bool	is_float_in_range(const char *s, float min, float max);
bool	is_vec3_unbounded(const char *s);
bool	is_vec3_normalized(const char *s);
bool	is_color_rgb(const char *s);

#endif // VALIDATION_H