import boost.ut;
import tuple;

auto main() -> int
{
    using namespace boost::ut;

    "tuples"_test = [] {
        "initialization"_test = [] {
            tuple::tuple tuple_0{4.3F, -4.2F, 3.1F, 1.0F};
            expect(tuple_0.x() == 4.3F and tuple_0.y() == -4.2F and tuple_0.z() == 3.1F and tuple_0.w() == 1.0F and
                   tuple_0.is_point() and !tuple_0.is_vector());
            tuple::tuple tuple_1{4.3F, -4.2F, 3.1F, 0.0F};
            expect(tuple_1.x() == 4.3F and tuple_1.y() == -4.2F and tuple_1.z() == 3.1F and tuple_1.w() == 0.0F and
                   !tuple_1.is_point() and tuple_1.is_vector());
        };

        "factory functions"_test = [] {
            tuple::tuple tuple_2{tuple::point(4, -4, 3)};
            expect(tuple_2.x() == 4.0F and tuple_2.y() == -4.0F and tuple_2.z() == 3.0F and tuple_2.w() == 1.0F);
            tuple::tuple tuple_3{tuple::vector(4, -4, 3)};
            expect(tuple_3.x() == 4.0F and tuple_3.y() == -4.0F and tuple_3.z() == 3.0F and tuple_3.w() == 0.0F);
        };
    };

    "operations"_test = [] {
        "addition"_test = [] {
            tuple::tuple tuple_0{3.0F, -2.0F, 5.0F, 1.0F};
            tuple::tuple tuple_1{-2.0F, 3.0F, 1.0F, 0.0F};
            tuple::tuple tuple_2{1.0F, 1.0F, 6.0F, 1.0F};
            expect(tuple_0 + tuple_1 == tuple_2);
        };

        "subtraction"_test = [] {
            tuple::tuple tuple_3{tuple::point(3, 2, 1)};
            tuple::tuple tuple_4{tuple::point(5, 6, 7)};
            tuple::tuple tuple_5{tuple::vector(-2, -4, -6)};
            expect(tuple_3 - tuple_4 == tuple_5);
        };

        "negation"_test = [] {
            tuple::tuple tuple_6{1, -2, 3, -4};
            tuple::tuple tuple_7{-1, 2, -3, 4};
            expect(tuple_6 * -1 == tuple_7);
        };

        "scalar multiplication"_test = [] {
            tuple::tuple tuple_8{1, -2, 3, -4};
            tuple::tuple tuple_9{3.5, -7, 10.5, -14};
            expect(tuple_8 * 3.5 == tuple_9);
        };

        "scalar division"_test = [] {
            tuple::tuple tuple_10{1, -2, 3, -4};
            tuple::tuple tuple_11{0.5, -1, 1.5, -2};
            expect(tuple_10 / 2 == tuple_11);
        };

        "magnitude"_test = [] {
            tuple::tuple tuple_12{tuple::vector(-1, -2, -3)};
            expect(std::abs(tuple::magnitude(tuple_12) - std::sqrt(14)) < 1e-5);
        };

        "normalization"_test = [] {
            tuple::tuple tuple_13{tuple::vector(1, 2, 3)};
            tuple::tuple tuple_14{tuple::vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14))};
            expect(tuple::normalize(tuple_13) == tuple_14);
        };

        "dot product"_test = [] {
            tuple::tuple tuple_15{tuple::vector(1, 2, 3)};
            tuple::tuple tuple_16{tuple::vector(2, 3, 4)};
            expect(tuple::dot_product(tuple_15, tuple_16) == 20.0F);
        };

        "cross product"_test = [] {
            tuple::tuple tuple_17{tuple::vector(1, 2, 3)};
            tuple::tuple tuple_18{tuple::vector(2, 3, 4)};
            tuple::tuple tuple_19{tuple::vector(-1, 2, -1)};
            expect(tuple::cross_product(tuple_17, tuple_18) == tuple_19);
        };
    };
    return 0;
}
