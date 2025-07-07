#ifndef VALIDATION_H
# define VALIDATION_H

// validation_1.c
bool	is_line_valid(const t_token *tokens, t_validation_state *vstate);

// validation_2.c
bool	has_too_many_tokens(const t_token *tokens);
bool	is_identifier_valid(const char *id);

// validation_3.c
bool	validate_ambient(const t_token *tokens, t_validation_state *v);
bool	validate_camera(const t_token *tokens, t_validation_state *v);
bool	validate_light(const t_token *tokens, t_validation_state *v);

//validate_primitives.c
bool is_validate_sphere(t_token *token);
bool is_validate_plane(t_token *token);
bool is_validate_cylinder(t_token *token);

//validate_cam_light.c
bool is_validate_ambient(t_token *token);
bool is_validate_camera(t_token *token);
bool is_validate_light(t_token *token);

//validation_utils.c
bool is_float_in_range(const char *s, float min, float max);
bool is_vec3_unbounded(const char *s);
bool is_vec3_normalized(const char *s);
bool is_color_rgb(const char *s);


// bool is_map_valid(char *map);

# endif // VALIDATION_H
