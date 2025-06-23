#include "minirt.h"

void parse_rgb(t_tuple *color, const char *str)
{
    int rgb[3] = {0};
    int i;

    i = 0;
    while (*str && i < 3)
    {
        rgb[i] = 0;
        while (*str >= '0' && *str <= '9')
        {
            rgb[i] = rgb[i] * 10 + (*str - '0');
            str++;
        }
        if (*str == ',') str++;
        i++;
    }

    color->r = rgb[0] / 255.0f;
    color->g = rgb[1] / 255.0f;
    color->b = rgb[2] / 255.0f;
}
