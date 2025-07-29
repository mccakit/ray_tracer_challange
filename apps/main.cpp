import std;
import boost.ut;

auto main() -> int
{
    using namespace boost::ut;
    "2 equals 2"_test = [] {
        expect(2_i == 2);
    };
}
