export module tuple;
import std;
/**
 * @brief Namespace containing 3D tuple math types and operations.
 */
export namespace tuple
{
/**
* @brief A 4D tuple representing either a point or vector in 3D space.
*
* The 4th element distinguishes point (w=1.0) from vector (w=0.0).
*
* Use `point(x, y, z)` and `vector(x, y, z)` to create tuples.
*/
template <int N>
class tuple
{
  public:
    std::array<float, N> data{};
    /**
     * @brief Constructs a tuple from a float array.
     */
    tuple(const std::array<float, N> &input_data) : data{input_data}
    {
    }
    /**
     * @brief Constructs a tuple from an initializer list
     */
    tuple(const std::initializer_list<float> &input_data)
    {
        std::copy(input_data.begin(), input_data.end(), data.begin());
    }
    constexpr bool is_point()
    {
        return data[3] == 1.0F;
    }
    constexpr bool is_vector()
    {
        return data[3] == 0.0F;
    }
    constexpr float x()
    {
        return data[0];
    }
    constexpr float y()
    {
        return data[1];
    }
    constexpr float z()
    {
        return data[2];
    }
    constexpr float w()
    {
        return data[3];
    }
    /**
     * @brief returns a reference to coordinate
     */
    float &operator[](const int i)
    {
        return data[i];
    }
    /**
     * @brief returns the copy of the coordinate
     */
    float operator[](const int i) const
    {
        return data[i];
    }
};
/**
 * @brief Creates a tuple representing a 3D point.
 * @param args X, Y, Z coordinates.
 * @return A tuple with w = 1.0.
 */
template <typename... Ts> constexpr tuple<4> point(Ts... args)
{
    const std::array<float, 3> input_data = {static_cast<float>(args)...};
    std::array<float, 4> output{};
    for (int i{0}; i < 3; ++i)
    {
        output[i] = input_data[i];
    }
    output[3] = 1.0F;
    return tuple<4>{output};
}
/**
 * @brief Creates a tuple representing a 3D vector.
 * @param args X, Y, Z coordinates.
 * @return A tuple with w = 0.0.
 */
template <typename... Ts> constexpr tuple<4> vector(Ts... args)
{
    const std::array<float, 3> input_data = {static_cast<float>(args)...};
    std::array<float, 4> output{};
    for (int i{0}; i < 3; ++i)
    {
        output[i] = input_data[i];
    }
    output[3] = 0.0F;
    return tuple<4>{output};
}
/**
 * @brief Compares two tuples with epsilon 1e-5
 */
template <int N>
bool operator==(const tuple<N> &ls_tuple, const tuple<N> &rs_tuple)
{
    for (int i{0}; i < N; ++i)
    {
        if (std::abs(ls_tuple[i] - rs_tuple[i]) > 1e-5)
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief Adds two tuples
 */
template <int N>
tuple<N> operator+(const tuple<N> &ls_tuple, const tuple<N> &rs_tuple)
{
    tuple result = ls_tuple;
    for (int i{0}; i < N; ++i)
    {
        result[i] += rs_tuple[i];
    }
    return result;
}
/**
 * @brief Subtracts two tuples
 */
template <int N>
tuple<N> operator-(const tuple<N> &ls_tuple, const tuple<N> &rs_tuple)
{
    tuple result = ls_tuple;
    for (int i{0}; i < N; ++i)
    {
        result[i] -= rs_tuple[i];
    }
    return result;
}
/**
 * @brief Multiply a tuple with a scalar
 */
template <int N>
tuple<N> operator*(const tuple<N> &ls_tuple, const float num)
{
    tuple result = ls_tuple;
    for (int i{0}; i < 4; ++i)
    {
        result[i] *= num;
    }
    return result;
}
/**
 * @brief Divide a tuple with a scalar
 */
template <int N>
tuple<N> operator/(const tuple<N> &ls_tuple, const float num)
{
    tuple result = ls_tuple;
    for (int i{0}; i < 4; ++i)
    {
        result[i] /= num;
    }
    return result;
}
/**
 * @brief Returns the magnitude of a tuple
 */
template <int N>
float magnitude(const tuple<N> &in_tuple)
{
    float sum{0};
    for (int i{0}; i < N; ++i)
    {
        sum += std::pow(in_tuple[i], 2);
    }
    return std::sqrt(sum);
}
/**
 * @brief Returns the normalized version of the tuple
 */
template <int N>
tuple<N> normalize(const tuple<N> &in_tuple)
{
    float tuple_magnitude{magnitude(in_tuple)};
    tuple<N> output{in_tuple};
    for (int i{0}; i < N; ++i)
    {
        output[i] /= tuple_magnitude;
    }
    return output;
}
/**
 * @brief Computes the dot product of two tuples.
 */
template <int N>
float dot_product(const tuple<N> &ls_tuple, const tuple<N> &rs_tuple)
{
    float sum{};
    for (int i{0}; i < N; ++i)
    {
        sum += ls_tuple[i] * rs_tuple[i];
    }
    return sum;
}
/**
 * @brief Computes the cross product of two tuples.
 */
tuple<4> cross_product(const tuple<4> &ls_tuple, const tuple<4> &rs_tuple)
{
    tuple result = ls_tuple;
    result[0] = ls_tuple[1] * rs_tuple[2] - ls_tuple[2] * rs_tuple[1];
    result[1] = ls_tuple[2] * rs_tuple[0] - ls_tuple[0] * rs_tuple[2];
    result[2] = ls_tuple[0] * rs_tuple[1] - ls_tuple[1] * rs_tuple[0];
    return result;
}
} // namespace tuple
