export module canvas;
import std;
import color;
export namespace canvas
{
template <std::size_t w, std::size_t h> class canvas
{
  public:
    static constexpr std::size_t width{w};
    static constexpr std::size_t height{h};
    std::array<color::color, width * height> pixels{};
    std::array<char, (width * height * 11) + 30> ppm_string{};
    void write_pixel(const std::size_t x, const std::size_t y, color::color input_color)
    {
        pixels[(y * width) + x] = input_color;
    }
    const color::color &pixel_at(const std::size_t x, const std::size_t y)
    {
        return pixels[(y * width) + x];
    }
    const std::array<char, (width * height * 11) + 30>& to_ppm()
    {
        std::size_t pos = 0;
        std::string_view header = std::format("P3\n{} {}\n255\n", width, height);
        std::copy(header.begin(), header.end(), ppm_string.begin());
        pos += header.size();

        std::array<char, 16> buffer{};
        for (const auto& color : pixels)
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
}; // namespace canvas
