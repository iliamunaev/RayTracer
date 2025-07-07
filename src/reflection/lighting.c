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


void    lighting(t_tuple *color, t_primitive *object, t_light light, t_tuple point, t_tuple v_eye, t_tuple v_normal, bool in_shadow, t_amb amb)
{
    t_tuple effective_color;
    t_tuple light_v;
    t_tuple ambient;
    t_tuple diffuse;
    t_tuple specular;
    t_tuple reflect_v;
    t_tuple negated_light_v;
    t_tuple checker_color2;
    float   light_dot_normal;
    float   reflect_dot_eye;
    float   factor;

    if (object->type == PLANE)
    {
        if ((int)(floorf(point.x) + floorf(point.y) + floorf(point.z)) % 2 == 0)
            mult_colors(&effective_color, object->color, light.color_component);
        else
        {
            checker_color2.r = fmax(0.0f, fmin(1.0f, object->color.r * 0.9 + object->color.g * 0.1));
            checker_color2.g = fmax(0.0f, fmin(1.0f, object->color.g * 0.9 + object->color.b * 0.1));
            checker_color2.b = fmax(0.0f, fmin(1.0f, object->color.b * 0.9 + object->color.r * 0.1));

            checker_color2.r *= 0.85;
            checker_color2.g *= 0.85;
            checker_color2.b *= 0.85;
            mult_colors(&effective_color, checker_color2, light.color_component);

        }
    }
    else
        mult_colors(&effective_color, object->color, light.color_component);
    mult_colors(&ambient, effective_color, amb.amb_component);
    sub_tuples(&light_v, light.position, point);
    normalize_vector(&light_v);
    if (in_shadow == true)
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
        mult_tuple(&specular, (light.brightness * object->material.specular * pow(reflect_dot_eye, object->material.shininess)));
        }
    }
    add_tuples(color, ambient, diffuse);
    add_tuples(color, *color, specular);
}

bool    check_shadow(t_rt *world, t_tuple point)
{
    t_tuple v_shadow;
    t_ray   r_shadow;
    float   distance;
    t_tuple direction;

    sub_tuples(&v_shadow, world->light.position, point);
    distance = magnitude_vector(v_shadow);
    create_vector(&direction, v_shadow.x, v_shadow.y, v_shadow.z);
    normalize_vector(&direction);
    create_ray(&r_shadow, point, direction);
    get_ray_intersections(&r_shadow, world);
    get_hit(&r_shadow);
    if(r_shadow.is_hit == true && r_shadow.hit.value < distance)
        return (true);
    else
        return (false);
}

void    refracted_color(t_tuple *refract_col, t_rt *world, t_comps *comps, uint8_t remaining_depth)
{
    float cos_t;
    float n_ratio;
    float cos_i;
    float sin2_t;
    t_tuple direction_term1;
    t_tuple direction_term2;
    t_tuple refract_direction;
    t_ray refract_ray;

    if (remaining_depth <= 0 || comps->object->material.transparency <= 0.001)
    {
        create_color(refract_col, 0, 0, 0);
        return;
    }
    n_ratio = comps->n1 / comps->n2;
    cos_i = dot_product(comps->v_eye, comps->v_normal);
    sin2_t = n_ratio * n_ratio * (1.0 - cos_i * cos_i);

    if (sin2_t > 1.0)
    {
        create_color(refract_col, 0, 0, 0);
        return;
    }

    cos_t = sqrtf(1.0 - sin2_t);

    create_vector(&direction_term1, comps->v_normal.x, comps->v_normal.y, comps->v_normal.z);
    mult_color(&direction_term1, (n_ratio * cos_i - cos_t));
    create_vector(&direction_term2, comps->v_eye.x, comps->v_eye.y, comps->v_eye.z);
    mult_color(&direction_term2, n_ratio);
    sub_tuples(&refract_direction, direction_term1, direction_term2);

    create_ray(&refract_ray, comps->under_pos, refract_direction);
    color_at(refract_col, world, &refract_ray, remaining_depth - 1);
    mult_color(refract_col, comps->object->material.transparency);
}

void    schlick(float *reflectance, t_comps *comps)
{
    float cos;
    float n;
    float sin2_t;
    float cos_t;
    float r0;

    cos = dot_product(comps->v_eye, comps->v_normal);
    if (comps->n1 > comps->n2)
    {
        n = comps->n1 / comps->n2;
        sin2_t = (n * n) * (1.0 - (cos * cos));
        if (sin2_t > 1.0)
        {
            *reflectance = 1.0;
            return;
        }
        cos_t = sqrtf(1.0 - sin2_t);
        cos = cos_t;
    }
    r0 = ((comps->n1 - comps->n2) / (comps->n1 + comps->n2)) * ((comps->n1 - comps->n2) / (comps->n1 + comps->n2));
    *reflectance = powf(r0 + (1 - r0) * (1 - cos), 5);
}

void    reflection( t_tuple *reflect_col, t_rt *world, t_comps *comps, uint8_t remaining_depth)
{
    t_ray reflect_ray;


    if (remaining_depth <= 0 || comps->object->material.reflection == 0)
    {
        create_color(reflect_col, 0, 0, 0);
        return ;
    }
    create_ray(&reflect_ray, comps->over_pos, comps->v_reflection);
    color_at(reflect_col, world, &reflect_ray, remaining_depth - 1);
    mult_color(reflect_col, comps->object->material.reflection);
}

void    shade_hit(t_tuple *color, t_rt *world, t_comps *comps, t_ray *ray, uint8_t remaining_depth)
{
    bool    is_shaded;
    t_tuple reflect_col;
    t_tuple refract_col;
    float   reflectance;
    
    create_color(&reflect_col, 0, 0 ,0);
    create_color(&refract_col, 0, 0 ,0);
    is_shaded = check_shadow(world, comps->over_pos);
    lighting(color, comps->object, world->light, comps->position, comps->v_eye, comps->v_normal, is_shaded, world->amb);
    mult_color(color, 1.0f - comps->object->material.transparency);
    reflection(&reflect_col, world, comps, remaining_depth);
    refracted_color(&refract_col, world, comps, remaining_depth);
    if (comps->object->material.reflection > 0 && comps->object->material.transparency > 0)
    {
        schlick(&reflectance, comps);
        mult_color(&reflect_col, reflectance);
        mult_color(&refract_col, 1.0 - reflectance);       
    }
    add_colors(color, *color, reflect_col);
    add_colors(color, *color, refract_col);
 
}

void    color_at(t_tuple *color, t_rt *world, t_ray *ray, uint8_t remaining_depth)
{
    t_comps comps;

    get_ray_intersections(ray, world);
    get_hit(ray);
    if (ray->is_hit == false)
        return;
    precompute_values(&comps, ray);
    shade_hit(color, world, &comps, ray, remaining_depth);
}