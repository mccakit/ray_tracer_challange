#include <numbers>
import boost.ut;
import matrix_transformations;
import matrix;
import tuple;

auto main() -> int
{
    using namespace boost::ut;
    "Multiplying by a translation matrix"_test = [] {
        matrix::matrix<4,4> transform {matrix_transformations::translation(5, -3, 2)};
        tuple::tuple<4> p {tuple::point(-3, 4, 5)};
        expect(transform * p == tuple::point(2, 1, 7));
    };
    "Multiplying by the inverse of a translation matrix"_test = [] {
        matrix::matrix<4,4> transform {matrix_transformations::translation(5, -3, 2)};
        matrix::matrix<4,4> inv {transform.inverse()};
        tuple::tuple<4> p {tuple::point(-3, 4, 5)};
        expect(inv * p == tuple::point(-8, 7, 3));
    };
    "Translation does not affect vectors"_test = [] {
        matrix::matrix<4,4> transform {matrix_transformations::translation(5, -3, 2)};
        tuple::tuple<4> v {tuple::vector(-3, 4, 5)};
        expect(transform * v == v);
    };
    "A scaling matrix applied to a vector"_test = [] {
        matrix::matrix<4,4> transform {matrix_transformations::scaling(2, 3, 4)};
        matrix::matrix<4,4> inv {transform.inverse()};
        tuple::tuple<4> v {tuple::vector(-4, 6, 8)};
        expect(inv * v == tuple::vector(-2, 2, 2));
    };
    "Multiplying by the inverse of a scaling matrix"_test = [] {
        matrix::matrix<4, 4> transform{ matrix_transformations::scaling(2, 3, 4) };
        matrix::matrix<4, 4> inv{ transform.inverse() };

        tuple::tuple<4> v{ tuple::vector(-4, 6, 8) };

        expect(inv * v == tuple::vector(-2, 2, 2));
    };
    "Reflection is scaling by a negative value"_test = [] {
        matrix::matrix<4, 4> transform{ matrix_transformations::scaling(-1, 1, 1) };

        tuple::tuple<4> p{ tuple::point(2, 3, 4) };

        expect(transform * p == tuple::point(-2, 3, 4));
    };
    "A rotation matrix around the X axis and its inverse"_test = [] {
        tuple::tuple<4> p = tuple::point(0, 1, 0);
        matrix::matrix<4, 4> half_quarter = matrix_transformations::rotation_x(std::numbers::pi / 4);
        matrix::matrix<4, 4> inv = half_quarter.inverse();
        tuple::tuple<4> expected = tuple::point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
        expect(inv * p == expected);
    };
    "A point rotated around the y axis"_test = [] {
        tuple::tuple<4> p = tuple::point(0, 0, 1);
        matrix::matrix<4,4> half_quarter = matrix_transformations::rotation_y(std::numbers::pi_v<float> / 4);
        matrix::matrix<4,4> full_quarter = matrix_transformations::rotation_y(std::numbers::pi_v<float> / 2);

        expect(half_quarter * p == tuple::point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
        expect(full_quarter * p == tuple::point(1, 0, 0));
    };
    "A point rotated around the z axis"_test = [] {
        tuple::tuple<4> p = tuple::point(0, 1, 0);
        matrix::matrix<4,4> half_quarter = matrix_transformations::rotation_z(std::numbers::pi_v<float> / 4);
        matrix::matrix<4,4> full_quarter = matrix_transformations::rotation_z(std::numbers::pi_v<float> / 2);

        expect(half_quarter * p == tuple::point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
        expect(full_quarter * p == tuple::point(-1, 0, 0));
    };
    "shearing moves x in proportion to y"_test = [] {
        const auto transform = matrix_transformations::shearing(1, 0, 0, 0, 0, 0);
        const auto p = tuple::point(2, 3, 4);
        expect(transform * p == tuple::point(5, 3, 4));
    };

    "shearing moves x in proportion to z"_test = [] {
        const auto transform = matrix_transformations::shearing(0, 1, 0, 0, 0, 0);
        const auto p = tuple::point(2, 3, 4);
        expect(transform * p == tuple::point(6, 3, 4));
    };

    "shearing moves y in proportion to x"_test = [] {
        const auto transform = matrix_transformations::shearing(0, 0, 1, 0, 0, 0);
        const auto p = tuple::point(2, 3, 4);
        expect(transform * p == tuple::point(2, 5, 4));
    };

    "shearing moves y in proportion to z"_test = [] {
        const auto transform = matrix_transformations::shearing(0, 0, 0, 1, 0, 0);
        const auto p = tuple::point(2, 3, 4);
        expect(transform * p == tuple::point(2, 7, 4));
    };

    "shearing moves z in proportion to x"_test = [] {
        const auto transform = matrix_transformations::shearing(0, 0, 0, 0, 1, 0);
        const auto p = tuple::point(2, 3, 4);
        expect(transform * p == tuple::point(2, 3, 6));
    };

    "shearing moves z in proportion to y"_test = [] {
        const auto transform = matrix_transformations::shearing(0, 0, 0, 0, 0, 1);
        const auto p = tuple::point(2, 3, 4);
        expect(transform * p == tuple::point(2, 3, 7));
    };
    "individual transformations applied in sequence"_test = [] {
        tuple::tuple<4> p = tuple::point(1, 0, 1);
        matrix::matrix<4,4> a = matrix_transformations::rotation_x(std::numbers::pi / 2);
        matrix::matrix<4,4> b = matrix_transformations::scaling(5, 5, 5);
        matrix::matrix<4,4> c = matrix_transformations::translation(10, 5, 7);
        tuple::tuple<4> p2 = a * p;
        expect(p2 == tuple::point(1, -1, 0));
        tuple::tuple<4> p3 = b * p2;
        expect(p3 == tuple::point(5, -5, 0));
        tuple::tuple<4> p4 = c * p3;
        expect(p4 == tuple::point(15, 0, 7));
    };

    "chained transformations applied in reverse order"_test = [] {
        tuple::tuple<4> p = tuple::point(1, 0, 1);
        matrix::matrix<4,4> a = matrix_transformations::rotation_x(std::numbers::pi / 2);
        matrix::matrix<4,4> b = matrix_transformations::scaling(5, 5, 5);
        matrix::matrix<4,4> c = matrix_transformations::translation(10, 5, 7);

        matrix::matrix<4,4> t = a * b * c;
        expect(t * p == tuple::point(15, 0, 7));
    };
}
