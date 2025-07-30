export module color;
import std;
export namespace color
{
class color
{
  public:
    std::array<float, 3> channels{};
    color(const std::array<float, 3> &input_data) : channels{input_data}
    {
    }
    color(const std::initializer_list<float> &input_data)
    {
        std::copy(input_data.begin(), input_data.end(), channels.begin());
    }
    float &operator[](const int i)
    {
        return channels[i];
    }

    float operator[](const int i) const
    {
        return channels[i];
    }
};

bool operator==(const color &ls_color, const color &rs_color)
{
    for (int i{0}; i < 3; ++i)
    {
        if (std::abs(ls_color[i] - rs_color[i]) > 1e-5)
        {
            return false;
        }
    }
    return true;
}
color operator+(const color &ls_color, const color &rs_color)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
    {
        result[i] += rs_color[i];
    }
    return result;
}
color operator-(const color &ls_color, const color &rs_color)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
    {
        result[i] -= rs_color[i];
    }
    return result;
}
color operator*(const color &ls_color, const float num)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
    {
        result[i] *= num;
    }
    return result;
}
color operator/(const color &ls_color, const float num)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
    {
        result[i] /= num;
    }
    return result;
}
color operator*(const color &ls_color, const color &rs_color)
{
    color output {ls_color};
    for (int i{0}; i < 3; ++i)
    {
        output[i] *= rs_color[i];
    }
    return output;
}
} // namespace color
