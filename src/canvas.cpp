export module canvas;
import std;
import color;
/**
 * @brief Namespace for 2D drawing canvas functionality.
 */
export namespace canvas
{

/**
 * @brief Fixed-size 2D canvas storing pixel colors and exporting to PPM format.
 *
 * Template parameters:
 * - `w`: width of the canvas in pixels
 * - `h`: height of the canvas in pixels
 *
 * Internally stores pixel data as an array of `color::color`.
 * Provides methods to write pixels, read pixels, and export the canvas as a PPM image string.
 */
template <std::size_t w, std::size_t h> class canvas
{
  public:
    static constexpr std::size_t width{w};
    static constexpr std::size_t height{h};

    std::array<color::color, width * height> pixels{};
    std::array<char, (width * height * 11) + 30> ppm_string{};

    /**
     * @brief Sets the pixel color at (x, y).
     */
    void write_pixel(const std::size_t x, const std::size_t y, color::color input_color)
    {
        pixels[(y * width) + x] = input_color;
    }

    /**
     * @brief Returns the pixel color at (x, y).
     */
    const color::color &pixel_at(const std::size_t x, const std::size_t y)
    {
        return pixels[(y * width) + x];
    }

    /**
     * @brief Converts the canvas pixel data to a PPM image string.
     *
     * The returned string contains the PPM header and pixel RGB values.
     */
    const std::array<char, (width * height * 11) + 30> &to_ppm()
    {
        std::size_t pos = 0;
        std::array<char, 30> header_buffer{};
        std::snprintf(header_buffer.data(), header_buffer.size(), "P3\n%zu %zu\n255\n", width, height);
        std::string_view header_view(header_buffer.data());
        std::copy(header_view.begin(), header_view.end(), ppm_string.begin());
        pos += header_view.size();
        std::array<char, 16> buffer{};
        for (const auto &color : pixels)
        {
            for (std::size_t i = 0; i < color.channels.size(); ++i)
            {
                int clamped_number{std::clamp(static_cast<int>(std::round(color.channels[i] * 255.0F)), 0, 255)};
                std::snprintf(buffer.data(), buffer.size(), "%d", clamped_number);
                std::string_view channel_str(buffer.data());
                std::copy(channel_str.begin(), channel_str.end(), ppm_string.begin() + pos);
                pos += channel_str.size();
                if (i < color.channels.size() - 1)
                {
                    ppm_string[pos++] = ' ';
                }
            }
            ppm_string[pos++] = '\n';
        }

        return ppm_string;
    }
};
} // namespace canvas
