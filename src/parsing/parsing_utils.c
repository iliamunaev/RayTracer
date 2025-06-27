#include "minirt.h"

void parse_rgb(t_tuple *color, const char *str)
{
    int rgb[3] = {0};
    int i = 0;

    while (*str && i < 3)
    {
        // Skip spaces
        while (*str == ' ')
            str++;

        rgb[i] = 0;
        while (*str >= '0' && *str <= '9')
        {
            rgb[i] = rgb[i] * 10 + (*str - '0');
            str++;
        }
        // Skip spaces before comma
        while (*str == ' ')
            str++;
        if (*str == ',')
            str++;
        i++;
    }

    color->r = rgb[0] / 255.0f;
    color->g = rgb[1] / 255.0f;
    color->b = rgb[2] / 255.0f;
    color->a = 1.0f;
}

void parse_coordinates(t_tuple *position, const char *str)
{
    int i;
    float vals[3];
    const char *p = str;

    for (i = 0; i < 3; i++)
    {
        // Skip leading spaces
        while (*p == ' ')
            p++;
        vals[i] = ft_strtof(p);

        // Move pointer to next comma or end
        while (*p && *p != ',')
            p++;
        if (*p == ',')
            p++;
    }
    position->x = vals[0];
    position->y = vals[1];
    position->z = vals[2];
    position->w = 1.0f;
}


void vectorToEuler(t_tuple *angles, t_tuple normal_vector)
{
    const t_tuple world_up_vector;

    t_tuple forward_vec = normal_vector;
    t_tuple right_vec;
    t_tuple new_up_vec;
    float dot_prod;

    normalize_vector(&forward_vec);
    create_vector(&world_up_vector, 0.0f, 1.0f, 0.0f);
    dot_prod = dot_product(forward_vec, world_up_vector);
    if (fabs(dot_prod) > (1.0f - EPSILON))
    {
        right_vec = (t_tuple){1.0f, 0.0f, 0.0f};
        cross_product(&new_up_vec, right_vec, forward_vec);
    }
    else
    {
        cross_product(&right_vec, forward_vec, world_up_vector);
        normalize_vector(&right_vec);
        cross_product(&new_up_vec, right_vec, forward_vec);
    }
    
    angles->x = atan2(forward_vec.x, forward_vec.z);

    float xy_magnitude = sqrtf(forward_vec.x * forward_vec.x + forward_vec.z * forward_vec.z);
    angles->y = atan2(-forward_vec.y, xy_magnitude);

    angles->z = atan2(right_vec.y, new_up_vec.y);
    angles->w = 0;
}