export module tuple;
import std;
export namespace tuple
{
class tuple
{
  public:
    std::array<float, 4> data{};
    tuple(const std::array<float, 4> &input_data) : data{input_data}
    {
    }
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
    float &operator[](const int i)
    {
        return data[i];
    }

    float operator[](const int i) const
    {
        return data[i];
    }
};
template <typename... Ts> constexpr tuple point(Ts... args)
{
    const std::array<float, 3> input_data = {static_cast<float>(args)...};
    std::array<float, 4> output{};
    for (int i{0}; i < 3; ++i)
    {
        output[i] = input_data[i];
    }
    output[3] = 1.0F;
    return tuple{output};
}
template <typename... Ts> constexpr tuple vector(Ts... args)
{
    const std::array<float, 3> input_data = {static_cast<float>(args)...};
    std::array<float, 4> output{};
    for (int i{0}; i < 3; ++i)
    {
        output[i] = input_data[i];
    }
    output[3] = 0.0F;
    return tuple{output};
}

bool operator==(const tuple &ls_tuple, const tuple &rs_tuple)
{
    for (int i{0}; i < 4; ++i)
    {
        if (std::abs(ls_tuple[i] - rs_tuple[i]) > 1e-5)
        {
            return false;
        }
    }
    return true;
}
tuple operator+(const tuple &ls_tuple, const tuple &rs_tuple)
{
    tuple result = ls_tuple;
    for (int i{0}; i < 4; ++i)
    {
        result[i] += rs_tuple[i];
    }
    return result;
}
tuple operator-(const tuple &ls_tuple, const tuple &rs_tuple)
{
    tuple result = ls_tuple;
    for (int i{0}; i < 4; ++i)
    {
        result[i] -= rs_tuple[i];
    }
    return result;
}
tuple operator*(const tuple &ls_tuple, const float num)
{
    tuple result = ls_tuple;
    for (int i{0}; i < 4; ++i)
    {
        result[i] *= num;
    }
    return result;
}
tuple operator/(const tuple &ls_tuple, const float num)
{
    tuple result = ls_tuple;
    for (int i{0}; i < 4; ++i)
    {
        result[i] /= num;
    }
    return result;
}
float magnitude(const tuple &in_tuple)
{
    float sum{0};
    for (int i{0}; i < 4; ++i)
    {
        sum += std::pow(in_tuple[i], 2);
    }
    return std::sqrt(sum);
}
tuple normalize(const tuple &in_tuple)
{
    float tuple_magnitude{magnitude(in_tuple)};
    tuple output{in_tuple};
    for (int i{0}; i < 4; ++i)
    {
        output[i] /= tuple_magnitude;
    }
    return output;
}
float dot_product(const tuple &ls_tuple, const tuple &rs_tuple)
{
    float sum{};
    for (int i{0}; i < 4; ++i)
    {
        sum += ls_tuple[i] * rs_tuple[i];
    }
    return sum;
}
tuple cross_product(const tuple &ls_tuple, const tuple &rs_tuple)
{
    tuple result = ls_tuple;
    result[0] = ls_tuple[1] * rs_tuple[2] - ls_tuple[2] * rs_tuple[1];
    result[1] = ls_tuple[2] * rs_tuple[0] - ls_tuple[0] * rs_tuple[2];
    result[2] = ls_tuple[0] * rs_tuple[1] - ls_tuple[1] * rs_tuple[0];
    return result;
}
} // namespace tuple
