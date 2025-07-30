import boost.ut;
import color;

auto main() -> int
{
    using namespace boost::ut;
    "color addition"_test = [] {
        color::color color_0{0.9F, 0.6F, 0.75F};
        color::color color_1{0.7F, 0.1F, 0.25F};
        color::color color_2{1.6F, 0.7F, 1.0F};
        expect(color_0 + color_1 == color_2);
    };
    "color subtraction"_test = [] {
        color::color color_0{0.9F, 0.6F, 0.75F};
        color::color color_1{0.7F, 0.1F, 0.25F};
        color::color color_2{0.2F, 0.5F, 0.5F};
        expect(color_0 - color_1 == color_2);
    };
    "color scalar multiplication"_test = [] {
        color::color color_0{0.2F, 0.3F, 0.4F};
        color::color color_1{0.4F, 0.6F, 0.8F};
        expect(color_0 * 2 == color_1);
    };
    "color component-wise multiplication"_test = [] {
        color::color color_0 {1.0F, 0.2F, 0.4F};
        color::color color_1 {0.9F, 1.0F, 0.1F};
        color::color color_2 {0.9F, 0.2F, 0.04F};
        expect(color_0 * color_1 == color_2);
    };
}
