#include "minirt.h"


//NEED TO CHANGE TO T_PRIMITIVE INSTEAD OF T_LIGHT
void    create_point_light(t_primitive *light, t_tuple position, float brighness, t_tuple color)
{
    create_point(&light->position, position.x, position.y, position.z);
    light->brightness = brighness;
    create_color(&light->color, position.r, position.g, position.b);
}

void    create_material(t_primitive *object, t_tuple color)
{
    create_color(&object->material.color, color.r, color.g, color.b);
    object->material.ambient = 0.2;
    object->material.diffuse = 0.9;
    object->material.specular = 0.1;
    object->material.shininess = 50;
    //FOR NOW JUST ASSIGN HARD VALUE. MIGHT WANT TO SWITCH IT
}

//NEED TO CHANGE TO T_PRIMITIVE INSTEAD OF T_LIGHT + REPLACE EYE_VECTOR + REFACTOR
void    lighting(t_tuple *color, t_primitive *object, t_primitive light, t_ray ray)
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

    create_color(&effective_color,object->material.color.r, object->material.color.g, object->material.color.b);
    mult_tuple(&effective_color, light.brightness);
    get_position(&point, ray, ray.hit.value);
    get_normal_at(&normal, object, point);
    sub_tuples(&light_v, light.position, point);
    normalize_vector(&light_v);
    create_color(&ambient, effective_color.r, effective_color.g, effective_color.b);
    mult_tuple(&ambient, object->material.ambient);
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
        mult_tuple(&specular, (light.brightness * object->material.specular * pow(reflect_dot_eye, object->material.shininess)));
        }
    }
    add_tuples(color, ambient, diffuse);
    add_tuples(color, *color, specular);
}
