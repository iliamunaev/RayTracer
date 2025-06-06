#include "minirt.h"

int main(void)
{
    t_tuple color;
    t_tuple color2;
    t_tuple color3;

    create_color(&color, 0, 0, 1);
    create_color(&color2, 0, 0.5, 1);
    mult_colors(&color3, color, color2);
    printf("color2 r = %f, g = %f, b = %f\n", color2.r, color2.g, color2.b);

    printf("color3 r = %f, g = %f, b = %f\n", color3.r, color3.g, color3.b);
    return (0);
}