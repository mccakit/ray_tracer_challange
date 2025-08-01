export module ray_sphere_intersections;
import std;
import tuple;
import matrix;
import light_and_shading;

export namespace ray_sphere_intersections
{
/**
* @brief Represents a ray in 3D space with an origin and direction.
*/
class ray
{
  public:
    tuple::tuple<4> origin{};
    tuple::tuple<4> direction{};
    /**
     * @brief Constructs a ray given an origin and direction.
     */
    ray(tuple::tuple<4> origin, tuple::tuple<4> direction) : origin{origin}, direction{direction}
    {
    }
    tuple::tuple<4> position(float time)
    {
        return origin + direction * time;
    }
    ray transform(const matrix::matrix<4, 4> &in_matrix) const
    {
        return ray(in_matrix * origin, in_matrix * direction);
    }
};
class sphere;
class intersection
{
  public:
    float time{};
    std::reference_wrapper<sphere> object;
    /**
     * @brief Constructs an intersection given time and the intersected sphere.
     */
    intersection(float time, sphere &object) : time{time}, object{object}
    {
    }
};

class sphere
{
  public:
    int id{};
    tuple::tuple<4> origin{tuple::point(0, 0, 0)};
    float radious{1};
    matrix::matrix<4, 4> transform;
    light_and_shading::material material{};
    sphere(int id) : id{id}, transform(matrix::identity_matrix())
    {
    }
    /**
     * @brief Sets the transformation matrix for the sphere.
     */
    void set_transform(const matrix::matrix<4,4>& t)
    {
        transform = t;
    }
    /**
     * @brief Computes intersections of a ray with this sphere.
     * Transforms the ray into object space and solves the quadratic equation.ns
     */
    std::vector<intersection> intersect(const ray &ray)
    {
        auto transformed_ray {ray.transform(transform.inverse())};
        tuple::tuple<4> sphere_to_ray{transformed_ray.origin - origin};
        float a{tuple::dot_product(transformed_ray.direction, transformed_ray.direction)};
        float b{2 * tuple::dot_product(transformed_ray.direction, sphere_to_ray)};
        float c{tuple::dot_product(sphere_to_ray, sphere_to_ray) - 1};
        float discriminant{static_cast<float>(std::pow(b, 2)) - 4 * a * c};
        if (discriminant < 0)
        {
            return {};
        }
        else
        {
            float t1{(-b - std::sqrt(discriminant)) / (2 * a)};
            float t2{(-b + std::sqrt(discriminant)) / (2 * a)};
            return {{t1, *this}, {t2, *this}};
        }
    }
    tuple::tuple<4> normal_at(tuple::tuple<4> point)
    {
        auto object_point = transform.inverse() * point;
        auto object_normal = object_point - tuple::point(0, 0, 0);
        auto world_normal = transform.inverse().transpose() * object_normal;
        world_normal[3] = 0.0f;
        return tuple::normalize(world_normal);
    }
};
bool operator==(const sphere &ls_sphere, const sphere &rs_sphere)
{
    return ls_sphere.id == rs_sphere.id;
}
bool operator==(const intersection &lhs, const intersection &rhs)
{
    return lhs.time == rhs.time && lhs.object.get() == rhs.object.get();
}
/**
 * @brief Combines multiple intersections and returns them sorted by time.
 */
template <typename... Ts> std::vector<intersection> intersections(const Ts &...args)
{
    std::array<std::reference_wrapper<const intersection>, sizeof...(args)> refs{args...};
    std::sort(refs.begin(), refs.end(), [](const intersection &a, const intersection &b) { return a.time < b.time; });
    std::vector<intersection> output;
    output.reserve(sizeof...(args));
    for (const auto &ref : refs)
    {
        output.push_back(ref.get());
    }
    return output;
}
/**
 * @brief Finds the hit (closest non-negative intersection) from a list of intersections passed as arguments.
 * @tparam Ts Variadic template parameter pack of intersections
 * @param args Intersection objects to evaluate
 * @return Optional intersection if a valid hit exists, nullopt otherwise
 */
template <typename... Ts> std::optional<intersection> hit(Ts &...args)
{
    std::array<std::reference_wrapper<intersection>, sizeof...(args)> arguments{args...};
    int output_index{-1};
    float compare_time{std::numeric_limits<float>::max()};
    for (int i{0}; i < arguments.size(); ++i)
    {
        if (arguments[i].get().time >= 0 && arguments[i].get().time < compare_time)
        {
            output_index = i;
            compare_time = arguments[i].get().time;
        }
    }
    if (output_index == -1)
        return std::nullopt;
    return arguments[output_index];
}
/**
 * @brief Finds the hit (closest non-negative intersection) from a vector of intersections.
 * @param intersections Vector of intersections to evaluate
 * @return Optional intersection if a valid hit exists, nullopt otherwise
 */
std::optional<intersection> hit(std::vector<intersection> &intersections)
{
    int output_index{-1};
    float compare_time{std::numeric_limits<float>::max()};
    for (int i{0}; i < intersections.size(); ++i)
    {
        if (intersections[i].time >= 0 && intersections[i].time < compare_time)
        {
            output_index = i;
            compare_time = intersections[i].time;
        }
    }
    if (output_index == -1)
    {
        return std::nullopt;
    }
    return intersections[output_index];
}
} // namespace ray_sphere_intersections
