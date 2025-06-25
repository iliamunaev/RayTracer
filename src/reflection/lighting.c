#include "minirt.h"

//NEED TO CHANGE TO T_PRIMITIVE INSTEAD OF T_LIGHT + REPLACE EYE_VECTOR + REFACTOR
/* void    lighting(t_tuple *color, t_primitive *object, t_primitive *light, t_ray ray)
{
    t_tuple normal;
    t_tuple point;
    t_tuple effective_color;
    t_tuple light_v;
    t_tuple ambient;
    t_tuple diffuse;
    t_tuple specular;
    t_tuple reflect_v;
    t_tuple eye_v;
    t_tuple negated_light_v;
    float   light_dot_normal;
    float   reflect_dot_eye;

    create_color(&effective_color,object->color.r, object->color.g, object->color.b);
    mult_tuple(&effective_color, light->brightness);
    get_position(&point, ray, ray.hit.value);
    get_normal_at(&normal, object, point);
    sub_tuples(&light_v, light->position, point);
    normalize_vector(&light_v);
    create_color(&ambient, effective_color.r, effective_color.g, effective_color.b);
    mult_tuple(&ambient, object->material.ambient);
    if (check_shadow == true)
    {
        color->r = ambient.r;
        color->g = ambient.g;
        color->b = ambient.b;
        return;
    }
    light_dot_normal = dot_product(light_v, normal);
    if (light_dot_normal < 0)
    {
        create_color(&diffuse, 0, 0, 0);
        create_color(&specular, 0, 0, 0);
    }
    else
    {
        create_color(&diffuse, effective_color.r, effective_color.g, effective_color.b);
        mult_tuple(&diffuse, (object->material.diffuse * light_dot_normal));
        create_vector(&negated_light_v, light_v.x, light_v.y, light_v.z);
        negate_tuple(&negated_light_v);
        reflect_vec(&reflect_v, negated_light_v, normal);
        create_vector(&eye_v, ray.direction.x, ray.direction.y, ray.direction.z);
        negate_tuple(&eye_v);
        normalize_vector(&eye_v);
        reflect_dot_eye = dot_product(reflect_v, eye_v);
        if (reflect_dot_eye <= 0)
            create_color(&specular, 0, 0, 0);
        else
        {
        create_color(&specular, effective_color.r, effective_color.g, effective_color.b);
        mult_tuple(&specular, (light->brightness * object->material.specular * pow(reflect_dot_eye, object->material.shininess)));
        }
    }
    add_tuples(color, ambient, diffuse);
    add_tuples(color, *color, specular);
} */


void    lighting(t_tuple *color, t_primitive *object, t_primitive *light, t_tuple point, t_tuple v_eye, t_tuple v_normal)
{
    t_tuple effective_color;
    t_tuple light_v;
    t_tuple ambient;
    t_tuple diffuse;
    t_tuple specular;
    t_tuple reflect_v;
    t_tuple negated_light_v;
    float   light_dot_normal;
    float   reflect_dot_eye;

    create_color(&effective_color,object->color.r, object->color.g, object->color.b);
    mult_tuple(&effective_color, light->brightness);
    sub_tuples(&light_v, light->position, point);
    normalize_vector(&light_v);
    create_color(&ambient, effective_color.r, effective_color.g, effective_color.b);
    mult_tuple(&ambient, object->material.ambient);
    if (check_shadow == true)
    {
        color->r = ambient.r;
        color->g = ambient.g;
        color->b = ambient.b;
        return;
    }
    light_dot_normal = dot_product(light_v, v_normal);
    if (light_dot_normal < 0)
    {
        create_color(&diffuse, 0, 0, 0);
        create_color(&specular, 0, 0, 0);
    }
    else
    {
        create_color(&diffuse, effective_color.r, effective_color.g, effective_color.b);
        mult_tuple(&diffuse, (object->material.diffuse * light_dot_normal));
        create_vector(&negated_light_v, light_v.x, light_v.y, light_v.z);
        negate_tuple(&negated_light_v);
        reflect_vec(&reflect_v, negated_light_v, v_normal);
        reflect_dot_eye = dot_product(reflect_v, v_eye);
        if (reflect_dot_eye <= 0)
            create_color(&specular, 0, 0, 0);
        else
        {
        create_color(&specular, effective_color.r, effective_color.g, effective_color.b);
        mult_tuple(&specular, (light->brightness * object->material.specular * pow(reflect_dot_eye, object->material.shininess)));
        }
    }
    add_tuples(color, ambient, diffuse);
    add_tuples(color, *color, specular);
}

void    shade_hit(t_tuple *color, t_rt *world, t_comps *comps)
{
    lighting(color, comps->object, world.light, comps->position, comps->v_eye, comps->v_normal);
}