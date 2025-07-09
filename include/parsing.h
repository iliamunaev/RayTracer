#ifndef PARSING_H
# define PARSING_H

# define MAX_NUM_TOKENS 9
# define MAX_TOKEN_LENGTH 32

typedef struct s_validation_state {
	bool seen_ambient;
	bool seen_camera;
	bool seen_light;
}   t_validation_state;


typedef struct s_token
{
    char token[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];
	t_validation_state vstate;
} t_token;

// typedef struct s_pars
// {
//     t_primitive *element;
//     int count;
// } t_pars;

// parsing.c
int parse(const char *map_file, t_rt *world);


// parsing_utils_1.c
void parse_rgb(t_tuple *color, const char *str);
void parse_coordinates(t_tuple *position, const char *str);
void	skip_spaces(char **line);
bool	is_line_empty(const char *line);

// parsing_utils_2.c
int	read_file(const char *map_file);
void	copy_token(char *dest, const char *src, size_t len);

// init_world.c
void    init_world(t_rt *world);

// setup_mlx.c
void    setup_mlx(t_rt *world);

// create_matireal.c
void	create_material(t_rt *rt);

//parse_primitives.c
void	parse_sphere(t_rt *rt, t_token *token, int j);
void	parse_plane(t_rt *rt, t_token *token, int j);
void	parse_cylinder(t_rt *rt, t_token *token, int j);

//parse_cam_light.c
void	parse_ambient(t_rt *rt, t_token *token);
void	parse_camera(t_rt *rt, t_token *token);
void	parse_light(t_rt *rt, t_token *token);

// fillup_world.c
void fillup_world(t_rt *world, t_token *token, int j);

// void vector_to_euler(t_tuple *rotation, t_tuple normal);
#endif // PARSING_H
