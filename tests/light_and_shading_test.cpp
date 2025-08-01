import boost.ut;
import ray_sphere_intersections;
import tuple;
import matrix;
import matrix_transformations;
import light_and_shading;
import color;

auto main() -> int
{
    using namespace boost::ut;
    "The normal on a sphere at a point on the x axis"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.normal_at(tuple::point(1, 0, 0)) == tuple::vector(1, 0, 0));
    };
    "The normal on a sphere at a point on the y axis"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.normal_at(tuple::point(0, 1, 0)) == tuple::vector(0, 1, 0));
    };
    "The normal on a sphere at a point on the z axis"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        expect(sphere.normal_at(tuple::point(0, 0, 1)) == tuple::vector(0, 0, 1));
    };
    "The normal on a sphere at a nonaxial point"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        float val = std::sqrt(3.0f) / 3.0f;
        expect(sphere.normal_at(tuple::point(val, val, val)) == tuple::vector(val, val, val));
    };
    "The normal is a normalized vector"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        float val = std::sqrt(3.0f) / 3.0f;
        auto n = sphere.normal_at(tuple::point(val, val, val));
        expect(n == tuple::normalize(n));
    };
    "Computing the normal on a translated sphere"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        sphere.set_transform(matrix_transformations::translation(0, 1, 0));
        auto n = sphere.normal_at(tuple::point(0, 1.70711f, -0.70711f));
        expect(n == tuple::vector(0, 0.70711f, -0.70711f));
    };

    "Computing the normal on a transformed sphere"_test = [] {
        ray_sphere_intersections::sphere sphere{0};
        auto m = matrix_transformations::rotation_z(float(std::numbers::pi) / 5) *
                 matrix_transformations::scaling(1, 0.5F, 1);
        sphere.set_transform(m);
        float val = std::sqrt(2.0F) / 2.0F;
        auto n = sphere.normal_at(tuple::point(0, val, -val));
        auto expected = tuple::vector(0, 0.970F, -0.242F);
        expect(n == expected);
    };
    "Reflecting a vector approaching at 45 degrees"_test = [] {
        auto v = tuple::vector(1, -1, 0);
        auto n = tuple::vector(0, 1, 0);
        auto r = light_and_shading::reflect(v, n);
        auto expected = tuple::vector(1, 1, 0);
        expect(r == expected);
    };
    "Reflecting a vector off a slanted surface"_test = [] {
        auto v = tuple::vector(0, -1, 0);
        float val = std::sqrt(2.0F) / 2.0F;
        auto n = tuple::vector(val, val, 0);
        auto r = light_and_shading::reflect(v, n);
        auto expected = tuple::vector(1, 0, 0);
        expect(r == expected);
    };
    "A point light has a position and intensity"_test = [] {
        color::color intensity{1, 1, 1};
        auto position = tuple::point(0, 0, 0);
        light_and_shading::light light_source{intensity, position};
        expect(light_source.position == position);
        expect(light_source.intensity == intensity);
    };
    "The default material"_test = [] {
        light_and_shading::material m{};
        expect(m.color == color::color{1, 1, 1});
        expect(m.ambient == 0.1f);
        expect(m.diffuse == 0.9f);
        expect(m.specular == 0.9f);
        expect(m.shininess == 200.0f);
    };
    "A sphere has a default material"_test = [] {
        ray_sphere_intersections::sphere s{0};
        auto sm = s.material;
        light_and_shading::material m{};
        expect(sm == light_and_shading::material{});
    };
    "A sphere may be assigned a material"_test = [] {
        ray_sphere_intersections::sphere s{0};
        light_and_shading::material m{};
        m.ambient = 1.0f;
        s.material = m;
        expect(s.material == m);
    };
    "Lighting with the eye between the light and the surface"_test = [] {
        light_and_shading::material m{};
        auto position {tuple::point(0, 0, 0)};
        auto eyev {tuple::vector(0, 0, -1)};
        auto normalv {tuple::vector(0, 0, -1)};
        light_and_shading::light light {color::color {1, 1, 1}, tuple::point(0, 0, -10)};
        auto result {lighting(m, light, position, eyev, normalv)};
        expect(result == color::color{1.9, 1.9, 1.9});
    };
    "Lighting with the eye between light and surface, eye offset 45°"_test = [] {
        light_and_shading::material m{};
        auto position {tuple::point(0, 0, 0)};
        auto eyev {tuple::vector(0, std::sqrt(2)/2, -std::sqrt(2)/2)};
        auto normalv {tuple::vector(0, 0, -1)};
        light_and_shading::light light {color::color {1, 1, 1}, tuple::point(0, 0, -10)};
        auto result {lighting(m, light, position, eyev, normalv)};
        expect(result == color::color{1.0, 1.0, 1.0});
    };
    "Lighting with eye opposite surface, light offset 45°"_test = [] {
        light_and_shading::material m{};
        auto position {tuple::point(0, 0, 0)};
        auto eyev {tuple::vector(0, 0, -1)};
        auto normalv {tuple::vector(0, 0, -1)};
        light_and_shading::light light {color::color {1, 1, 1}, tuple::point(0, 10, -10)};
        auto result {lighting(m, light, position, eyev, normalv)};
        expect(result == color::color{0.7364F, 0.7364F, 0.7364F});
    };
    "Lighting with eye in the path of the reflection vector"_test = [] {
        light_and_shading::material m{};
        auto position {tuple::point(0, 0, 0)};
        auto eyev {tuple::vector(0, -std::sqrt(2)/2, -std::sqrt(2)/2)};
        auto normalv {tuple::vector(0, 0, -1)};
        light_and_shading::light light {color::color {1, 1, 1}, tuple::point(0, 10, -10)};
        auto result {lighting(m, light, position, eyev, normalv)};
        expect(result == color::color{1.6364, 1.6364, 1.6364});
    };
    "Lighting with the light behind the surface"_test = [] {
        light_and_shading::material m{};
        auto position {tuple::point(0, 0, 0)};
        auto eyev {tuple::vector(0, 0, -1)};
        auto normalv {tuple::vector(0, 0, -1)};
        light_and_shading::light light {color::color{1, 1, 1}, tuple::point(0, 0, 10)};
        auto result {lighting(m, light, position, eyev, normalv)};
        expect(result == color::color{0.1, 0.1, 0.1});
    };

}
