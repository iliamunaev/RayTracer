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
