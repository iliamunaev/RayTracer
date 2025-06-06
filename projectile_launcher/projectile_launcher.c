#include "minirt.h"

typedef struct s_projectile
{
    t_tuple pos;
    t_tuple vel;
}   t_projectile;

typedef struct s_environment
{
    t_tuple grav;
    t_tuple wind;
}   t_environment;

void    tick(t_projectile *proj, const t_environment env)
{
    proj->pos.x += proj->vel.x;
    proj->pos.y += proj->vel.y;
    proj->pos.z += proj->vel.z;

    proj->vel.x += env.grav.x + env.wind.x;
    proj->vel.y += env.grav.y + env.wind.y;
    proj->vel.z += env.grav.z + env.wind.z;
    printf("projectile pos: x = %f, y = %f, z = %f\n", proj->pos.x, proj->pos.y, proj->pos.z);
}

int main(void)
{
    t_projectile proj;
    t_environment env;

    // create projectile
    create_point (&proj.pos, 0, 1, 0);
    create_vector(&proj.vel, 1, 1, 0);
    normalize_vector(&proj.vel);
    mult_tuple(&proj.vel, 3); // multiply the velocity to shoot further

    //create environment
    create_vector(&env.grav, 0, -0.1, 0);
    create_vector(&env.wind, -0.01, 0, 0);

    //as long as projectile did not hit the ground (y = 0)
    while (proj.pos.y > 0)
        tick(&proj, env);

    printf("landing spot is: x = %f, y = %f, z = %f\n", proj.pos.x, proj.pos.y, proj.pos.z);
    return (0);
}