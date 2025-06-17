#include "minirt.h"

int main()
{
    char map = 
    {'A',    0.2,           255,255,255};

    t_rt world;

    parse(&map, &world);

    printf("id: %c\n", world.amb_light.id);
    printf("R: %f\n", world.amb_light.color[0]);
    printf("G: %f\n", world.amb_light.color[1]);
    printf("B: %f\n", world.amb_light.color[2]);

    return 0;
}