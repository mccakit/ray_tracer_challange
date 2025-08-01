import std;
import tuple;
import matrix;
import color;
import canvas;
import matrix_transformations;
import ray_sphere_intersections;

auto main() -> int
{
    constexpr float wall_size{7.0};
    constexpr float wall_z = 10.0f;
    constexpr int canvas_pixels{100};
    constexpr float pixel_size{wall_size / static_cast<float>(canvas_pixels)};
    constexpr float half{wall_size / 2};
    canvas::canvas<canvas_pixels, canvas_pixels> canvas{};
    color::color red{1, 0, 0};
    ray_sphere_intersections::ray ray{tuple::point(0, 0, -5), tuple::vector(1, 0, 0)};
    ray_sphere_intersections::sphere shape{0};
    shape.set_transform(matrix_transformations::scaling(1, 0.5, 1) *
                        matrix_transformations::rotation_z(std::numbers::pi / 4) *
                        matrix_transformations::shearing(1, 0, 0, 0, 0, 0));
    float world_y{};
    float world_x{};
    for (int row{0}; row < canvas.height; ++row)
    {
        world_y = half - (pixel_size * static_cast<float>(row));
        for (int col{0}; col < canvas.width; ++col)
        {
            world_x = half - (pixel_size * static_cast<float>(col));
            ray_sphere_intersections::ray r{ray.origin,
                                            tuple::normalize(tuple::point(world_x, world_y, wall_z) - ray.origin)};
            auto xs = shape.intersect(r);
            bool hit_found = false;
            for (const auto &intersection : xs)
            {
                if (intersection.time >= 0)
                {
                    hit_found = true;
                    break;
                }
            }
            if (hit_found)
            {
                canvas.write_pixel(col, row, red);
            }
        }
    }
    auto ppm_data = canvas.to_ppm();
    std::ofstream ofs("output.ppm", std::ios::binary);
    ofs.write(ppm_data.data(), ppm_data.size());
    ofs.close();

    return 0;
}
