#include "minirt.h"

int main(void)
{
    t_sphere sph_1;

    create_sphere(&sph_1);
    printf("sphere 1 id = %i\n", sph_1.id);

    t_sphere sph_2;

    create_sphere(&sph_2);
    printf("sphere 2 id = %i\n", sph_2.id);
}