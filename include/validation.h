#ifndef VALIDATION_H
# define VALIDATION_H

# ifdef BONUS
#  define MAX_NUM_TOKENS_SP 5
#  define MAX_NUM_TOKENS_PL 5
#  define MAX_NUM_TOKENS_CY 7
# else
#  define MAX_NUM_TOKENS_SP 4
#  define MAX_NUM_TOKENS_PL 4
#  define MAX_NUM_TOKENS_CY 6
# endif

# define MAX_NUM_TOKENS_C 4
# define MAX_NUM_TOKENS_L 4
# define MAX_NUM_TOKENS_A 3

// validation_1.c
bool	is_line_valid(t_token *tokens);

// validation_2.c
bool	validate_ambient(t_token *tokens);
bool	validate_camera(t_token *tokens);
bool	validate_light(t_token *tokens);
bool	is_max_num_tokens_valid(char *id, t_token *tokens);

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