#include "minirt.h"

void parse_rgb(t_tuple *color, const char *str)
{
    int value = 0;
    int i = 0;

    while (*str && i < 3)
    {
        if (*str >= '0' && *str <= '9')
        {
            value = value * 10 + (*str - '0');
        }
        else if (*str == ',' || *str == '\0')
        {
            if (i == 0) color->r = (float)value;
            else if (i == 1) color->g = (float)value;
            else if (i == 2) color->b = (float)value;
            value = 0;
            i++;
        }
        str++;
    }

    if (i == 2)
        color->b = (float)value; // ensure final component is captured
}
