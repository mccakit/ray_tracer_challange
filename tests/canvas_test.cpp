import boost.ut;
import canvas;
import color;

std::string get_line(const std::string& text, int lineNumber) {

    std::istringstream iss(text);
    std::string line;
    int currentLineCount = 0;
    while (std::getline(iss, line)) {
        currentLineCount++;
        if (currentLineCount == lineNumber) {
            return line;
        }
    }
    return "";
}

auto main() -> int
{
    using namespace boost::ut;
    "initialization"_test = [] {
        canvas::canvas<10, 20> canvas_0{};
        expect(canvas_0.width == 10 and canvas_0.height == 20);
        expect(canvas_0.pixels[0] == color::color{0, 0, 0});
    };
    "write_color"_test = [] {
        canvas::canvas<10, 20> canvas_0{};
        color::color red {1, 0, 0};
        canvas_0.write_pixel(2, 3, red);
        expect(canvas_0.pixel_at(2, 3) == red);
    };
    "ppm construction"_test = [] {
        canvas::canvas<5, 3> canvas_0{};
        color::color color_0 {1.5, 0, 0};
        color::color color_1 {0, 0.5, 0};
        color::color color_2 {-0.5, 0, 1};
        canvas_0.write_pixel(0, 0, color_0);
        canvas_0.write_pixel(2, 1, color_1);
        canvas_0.write_pixel(4, 2, color_2);
        int line0 {(0 * 5) + 0 + 4};
        expect(get_line(canvas_0.to_ppm().data(), line0) == "255 0 0");
        int line1 {(1 * 5) + 2 + 4};
        expect(get_line(canvas_0.to_ppm().data(), line1) == "0 128 0");
        int line2 {(2 * 5) + 4 + 4};
        expect(get_line(canvas_0.to_ppm().data(), line2) == "0 0 255");
    };
}
