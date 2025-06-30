#include "minirt.h"
#include <stdio.h>

void print_tuple(const char *name, t_tuple t)
{
    printf("%s: (%.2f, %.2f, %.2f, %.2f)\n",
        name, t.x, t.y, t.z, t.w);
}


void print_primitive(const t_primitive *p, int index)
{
    printf("Primitive #%d\n", index);
    printf("  id: %d\n", p->id);
    printf("  type: '%c%c'\n", p->type[0], p->type[1]);
    print_tuple("  position", p->position);
    print_tuple("  norm_vector", p->norm_vector);
    printf("  diameter: %.2f\n", p->diameter);
    printf("  height: %.2f\n", p->height);
    print_tuple("  color", p->color);
    printf("  material ambient: %.2f\n", p->material.ambient);
    print_tuple("  material color", p->material.color);
    printf("  matrix:\n");
    print_matrix(p->matrix);
}

void print_world(const t_rt *world)
{
    printf("=== World ===\n");
    printf("mlx pointer: %p\n", (void*)world->mlx);
    printf("scene pointer: %p\n", (void*)world->scene);
    printf("obj_counted: %u\n", world->obj_counted);

    printf("\n-- Amb --\n");
    printf("amb brightness: %.2f\n", world->amb.brightness);
    print_tuple("amb color", world->amb.color);
    print_tuple("amb component", world->amb.amb_component);
    printf("amb matrix:\n");
    print_matrix(world->amb.matrix);

    printf("\n-- Cam --\n");
    print_tuple("cam position", world->cam.position);
    print_tuple("cam norm_vector", world->cam.norm_vector);
    printf("cam fov: %.2f\n", world->cam.fov);
    printf("cam pix_size: %.2f\n", world->cam.pix_size);
    printf("cam half_width: %.2f\n", world->cam.half_width);
    printf("cam half_height: %.2f\n", world->cam.half_height);
    printf("cam half_view: %.2f\n", world->cam.half_view);
    printf("cam matrix:\n");
    print_matrix(world->cam.matrix);
    printf("cam inv_matrix:\n");
    print_matrix(world->cam.inv_matrix);

    printf("\n-- Light --\n");
    print_tuple("light position", world->light.position);
    printf("light brightness: %.2f\n", world->light.brightness);
    print_tuple("light color", world->light.color);
    print_tuple("light color_component", world->light.color_component);
    printf("light matrix:\n");
    print_matrix(world->light.matrix);

    printf("\n-- Primitives --\n");
    for (int i = 0; i < MAX_PRIMITIVES; i++)
    {
        print_primitive(&world->primitives_list[i], i);
    }
}


int	main(int argc, char **argv)
{

    // setup world
    (void)argc;
    t_rt rt;
    init_world(&rt);
    print_world(&rt);
    

    return (EXIT_SUCCESS);
} 
