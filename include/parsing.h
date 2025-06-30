#ifndef PARSING_H
#define PARSING_H

#define MAX_NUM_TOKENS 6
#define MAX_TOKEN_LENGTH 32

typedef struct s_pars
{
    t_primitive *element;
    int count;
} t_pars;

typedef struct s_token
{
    char token[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];
} t_token;

// parsing.c

void    init_world(t_rt *world);
int parse(const char *map_file, t_rt *world);
void fillup_world(t_rt *world, t_token *token, int j);
void    create_material(t_rt *rt);


// //parsing_utils.c
void parse_rgb(t_tuple *color, const char *str);
void parse_coordinates(t_tuple *position, const char *str);
void vector_to_euler(t_tuple *rotation, t_tuple normal);


#endif // PARSING_H
