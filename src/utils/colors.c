#include "minirt.h"

#include <stdint.h>
#include <math.h>  // for fminf and fmaxf

uint32_t float_to_hex(const t_tuple color)
{
    uint8_t r = (uint8_t)(fminf(fmaxf(color.r, 0.0f), 1.0f) * 255.0f);
    uint8_t g = (uint8_t)(fminf(fmaxf(color.g, 0.0f), 1.0f) * 255.0f);
    uint8_t b = (uint8_t)(fminf(fmaxf(color.b, 0.0f), 1.0f) * 255.0f);
    uint8_t a = (uint8_t)(fminf(fmaxf(color.a, 0.0f), 1.0f) * 255.0f);
    return ((r << 24) | (g << 16) | (b << 8) | a);

}


void    create_color(t_tuple *color, float r, float g, float b)
{
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = 1.0f;
}