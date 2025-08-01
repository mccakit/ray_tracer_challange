export module light_and_shading;
import std;
import tuple;
import color;

export namespace light_and_shading
{
tuple::tuple<4> reflect(const tuple::tuple<4> &in_vec, const tuple::tuple<4> &normal)
{
    return in_vec - normal * 2 * tuple::dot_product(in_vec, normal);
}
class light
{
  public:
    color::color intensity{};
    tuple::tuple<4> position{};
    light(const color::color &intensity, const tuple::tuple<4> &position) : intensity{intensity}, position{position}
    {
    }
};
class material
{
  public:
    color::color color{1, 1, 1};
    float ambient{0.1};
    float diffuse{0.9};
    float specular{0.9};
    float shininess{200.0};
    material() = default;
    material(color::color &color, float ambient, float diffuse, float specular, float shininess)
        : color{color}, ambient{ambient}, diffuse{diffuse}, specular{specular}, shininess{shininess}
    {
    }
};
bool operator==(const material &a, const material &b)
{
    return a.color == b.color && a.ambient == b.ambient && a.diffuse == b.diffuse && a.specular == b.specular &&
           a.shininess == b.shininess;
}
color::color lighting(const material &material, const light &light, const tuple::tuple<4> &point,
                      const tuple::tuple<4> &eyev, const tuple::tuple<4> &normalv)
{
    auto effective_color{material.color * light.intensity};
    auto lightv{tuple::normalize(light.position - point)};
    auto ambient{effective_color * material.ambient};
    auto light_dot_normal{tuple::dot_product(lightv, normalv)};
    color::color diffuse{};
    color::color specular{};
    if (light_dot_normal < 0)
    {
        diffuse = color::color{0, 0, 0};
        specular = color::color{0, 0, 0};
    }
    else
    {
        diffuse = effective_color * material.diffuse * light_dot_normal;
        auto reflectv{reflect(lightv * -1, normalv)};
        auto reflect_dot_eye{tuple::dot_product(reflectv, eyev)};
        if (reflect_dot_eye < 0)
        {
            specular = color::color{0, 0, 0};
        }
        else
        {
            float factor {std::pow(reflect_dot_eye, material.shininess)};
            specular = light.intensity * material.specular * factor;
        }
    }
    return ambient + diffuse + specular;
}

} // namespace light_and_shading
