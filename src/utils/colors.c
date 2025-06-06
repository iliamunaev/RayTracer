#include "minirt.h"

uint32_t float_to_hex(const t_tuple color)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    r = (uint8_t)(color.r * 255.0f);
    g = (uint8_t)(color.g * 255.0f);
    b = (uint8_t)(color.b * 255.0f);
    a = color.a;
    return ((r << 24) | (g << 16) | (b << 8) | (a));
}

void    create_color(t_tuple *color, float r, float g, float b)
{
    // Clamping colors not needed yet
   /*  if (r < 0)
        r = 0;
    if (r > 1)
        r = 1;
    if (g < 0)
        g = 0;
    if (g > 1)
        g = 1;
    if (b < 0)
        b = 0;
    if (b > 1)
        b = 1;
    if (a < 0)
        a = 0;
    if (a > 1)
        a = 1; */
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = 255;
}
