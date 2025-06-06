#include "minirt.h"

int main(void)
{
    t_tuple color;
    uint32_t hex;

    create_color(&color, 0, 0, 1, 1);
    hex = float_to_hex(color);
    printf("color hex = %08x\n", hex);
    return (0);
}