export module color;
import std;
/**
 * @brief Namespace containing color-related types and operations.
 */
export namespace color
{
/**
 * @brief RGB color with three float channels.
 *
 * Stores color as an array of three floats representing
 * red, green, and blue components.
 */
class color
{
  public:
    std::array<float, 3> channels{};

    /**
     * @brief Construct from array of 3 floats.
     */
    color(const std::array<float, 3> &input_data) : channels{input_data} {}

    /**
     * @brief Construct from initializer list of floats.
     */
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
    void print() const
    {
        std::cout << "color(" << channels[0] << ", " << channels[1] << ", " << channels[2] << ")\n";
    }
};

/**
 * @brief Compares two colors with epsilon 1e-5
 */
bool operator==(const color &ls_color, const color &rs_color)
{
    for (int i{0}; i < 3; ++i)
    {
        if (std::abs(ls_color[i] - rs_color[i]) > 1e-3)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Component-wise addition.
 */
color operator+(const color &ls_color, const color &rs_color)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
        result[i] += rs_color[i];
    return result;
}

/**
 * @brief Component-wise subtraction.
 */
color operator-(const color &ls_color, const color &rs_color)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
        result[i] -= rs_color[i];
    return result;
}

/**
 * @brief Multiply color by scalar.
 */
color operator*(const color &ls_color, const float num)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
        result[i] *= num;
    return result;
}

/**
 * @brief Divide color by scalar.
 */
color operator/(const color &ls_color, const float num)
{
    color result = ls_color;
    for (int i{0}; i < 3; ++i)
        result[i] /= num;
    return result;
}

/**
 * @brief Component-wise multiplication of two colors.
 */
color operator*(const color &ls_color, const color &rs_color)
{
    color output{ls_color};
    for (int i{0}; i < 3; ++i)
        output[i] *= rs_color[i];
    return output;
}

} // namespace color
