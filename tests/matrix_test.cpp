import boost.ut;
import matrix;
import tuple;

auto main() -> int
{
    using namespace boost::ut;
    "initialization"_test = [] {
        matrix::matrix<4, 4> matrix_0{{1, 5.5, 9, 13.5}, {2, 6.5, 10, 14.5}, {3, 7.5, 11, 15.5}, {4, 8.5, 12, 16.5}};
        expect(matrix_0(0, 0) == 1);
        expect(matrix_0(0, 3) == 4);
        expect(matrix_0(1, 0) == 5.5);
        expect(matrix_0(1, 2) == 7.5);
        expect(matrix_0(2, 2) == 11);
        expect(matrix_0(3, 0) == 13.5);
        expect(matrix_0(3, 2) == 15.5);

        matrix::matrix<2, 2> matrix_1{{-3, 1}, {5, -2}};
        expect(matrix_1(0, 0) == -3);
        expect(matrix_1(0, 1) == 5);
        expect(matrix_1(1, 0) == 1);
        expect(matrix_1(1, 1) == -2);

        matrix::matrix<3, 3> matrix_2{{-3, 1, 0}, {5, -2, 1}, {0, -7, 1}};
        expect(matrix_2(0, 0) == -3);
        expect(matrix_2(1, 1) == -2);
        expect(matrix_2(2, 2) == 1);
    };

    "operations"_test = [] {
        "equality"_test = [] {
            matrix::matrix<4, 4> matrix_0{{1, 5, 9, 5}, {2, 6, 8, 4}, {3, 7, 7, 3}, {4, 8, 6, 2}};
            matrix::matrix<4, 4> matrix_1{{1, 5, 9, 5}, {2, 6, 8, 4}, {3, 7, 7, 3}, {4, 8, 6, 2}};
            expect(matrix_0 == matrix_1);
            matrix::matrix<4, 4> matrix_2{{1, 5, 9, 5}, {2, 6, 8, 4}, {3, 7, 7, 3}, {4, 8, 6, 2}};
            matrix::matrix<4, 4> matrix_3{{2, 6, 8, 4}, {3, 7, 7, 3}, {4, 8, 6, 2}, {5, 9, 5, 1}};
            expect(matrix_2 != matrix_3);
        };
        "matrix_vector_multiplication"_test = [] {
            matrix::matrix<4, 4> test_matrix{{2, 0, 0, 0}, {0, 3, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 4}};
            tuple::tuple<4> test_vector{5, 2, 8, 1};
            tuple::tuple<4> expected_result{10, 6, 8, 4};
            expect(test_matrix * test_vector == expected_result);
        };
        "matrix_matrix_multiplication"_test = [] {
            matrix::matrix<4, 4> matrix_4{{1, 5, 9, 5}, {2, 6, 8, 4}, {3, 7, 7, 3}, {4, 8, 6, 2}};
            matrix::matrix<4, 4> matrix_5{{-2, 3, 4, 1}, {1, 2, 3, 2}, {2, 1, 6, 7}, {3, -1, 5, 8}};
            matrix::matrix<4, 4> matrix_6{{20, 44, 40, 16}, {22, 54, 58, 26}, {50, 114, 110, 46}, {48, 108, 102, 42}};
            expect(matrix_4 * matrix_5 == matrix_6);
        };
        "identity_matrix"_test = [] {
            matrix::matrix<4, 4> matrix_7{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
            expect(matrix_7 == matrix::identity_matrix());
        };
        "transpose"_test = [] {
            matrix::matrix<4, 4> matrix_8{{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}};
            matrix::matrix<4, 4> matrix_9{{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}};
            expect(matrix_8.transpose() == matrix_9);
            matrix::matrix<2, 4> matrix_10{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
            matrix::matrix<4, 2> matrix_11{{1, 3, 5, 7}, {2, 4, 6, 8}};
            expect(matrix_10.transpose() == matrix_11);
        };
        "submatrix"_test = [] {
            matrix::matrix<3, 3> matrix_12{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};
            matrix::matrix<2, 2> matrix_13{{-3, 2}, {0, 6}};
            expect(matrix_12.submatrix(0, 2) == matrix_13);
            matrix::matrix<4, 4> matrix_14{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}};
            matrix::matrix<3, 3> matrix_15{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}};
            expect(matrix_14.submatrix(2, 1) == matrix_15);
        };
        "determinant_2x2"_test = [] {
            matrix::matrix<3, 3> matrix_16{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
            matrix::matrix<2, 2> matrix_17 = matrix_16.submatrix(1, 0);
            expect(matrix_17.determinant() == 25);
            expect(matrix_16.minor(1, 0) == 25);
        };
        "cofactor_3x3"_test = [] {
            matrix::matrix<3, 3> matrix_A{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
            expect(matrix_A.minor(0, 0) == -12);
            expect(matrix_A.cofactor(0, 0) == -12);
            expect(matrix_A.minor(1, 0) == 25);
            expect(matrix_A.cofactor(1, 0) == -25);
        };
        "determinant_3x3"_test = [] {
            matrix::matrix<3, 3> matrix_B{{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}};
            expect(matrix_B.cofactor(0, 0) == 56);
            expect(matrix_B.cofactor(0, 1) == 12);
            expect(matrix_B.cofactor(0, 2) == -46);
            expect(matrix_B.determinant() == -196);
        };
        "determinant_4x4"_test = [] {
            matrix::matrix<4, 4> matrix_C{{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}};
            expect(matrix_C.cofactor(0, 0) == 690);
            expect(matrix_C.cofactor(0, 1) == 447);
            expect(matrix_C.cofactor(0, 2) == 210);
            expect(matrix_C.cofactor(0, 3) == 51);
            expect(matrix_C.determinant() == -4071);
        };
        "invertible_matrix"_test = [] {
            matrix::matrix<4, 4> matrix_A{{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}};
            expect(matrix_A.determinant() == -2120);
            expect(matrix_A.invertible());
        };
        "noninvertible_matrix"_test = [] {
            matrix::matrix<4, 4> matrix_A{{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}};
            expect(matrix_A.determinant() == 0);
            expect(!matrix_A.invertible());
        };
        "matrix_inverse"_test = [] {
            matrix::matrix<4, 4> matrix_0{{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}};
            matrix::matrix<4, 4> matrix_1 = matrix_0.inverse();

            expect(matrix_0.determinant() == 532);
            expect(matrix_0.cofactor(2, 3) == -160);
            expect(matrix_1[3][2] == -160.0F / 532.0F);
            expect(matrix_0.cofactor(3, 2) == 105);
            expect(matrix_1[2][3] == 105.0F / 532.0F);

            matrix::matrix<4, 4> matrix_3{{0.21805, 0.45113F, 0.24060, -0.04511},
                                          {-0.80827, -1.45677, -0.44361, 0.52068},
                                          {-0.07895, -0.22368, -0.05263, 0.19737},
                                          {-0.52256, -0.81391, -0.30075, 0.30639}};
            expect(matrix_1 == matrix_3);
            matrix::matrix<4, 4> matrix_4{{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}};
            matrix::matrix<4, 4> matrix_5 = matrix_4.inverse();

            matrix::matrix<4, 4> matrix_6{{-0.15385, -0.15385, -0.28205, -0.53846},
                                          {-0.07692, 0.12308, 0.02564, 0.03077},
                                          {0.35897, 0.35897, 0.43590, 0.92308},
                                          {-0.69231, -0.69231, -0.76923, -1.92308}};
            expect(matrix_5 == matrix_6);
            matrix::matrix<4, 4> matrix_7{{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}};
            matrix::matrix<4, 4> matrix_8 = matrix_7.inverse();

            matrix::matrix<4, 4> matrix_9{{-0.04074, -0.07778, 0.14444, -0.22222},
                                          {-0.07778, 0.03333, 0.36667, -0.33333},
                                          {-0.02901, -0.14630, -0.10926, 0.12963},
                                          {0.17778, 0.06667, -0.26667, 0.33333}};
            expect(matrix_8 == matrix_9);
        };
        "matrix_product_inverse_test"_test = [] {
            matrix::matrix<4, 4> matrix_0{{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}};
            matrix::matrix<4, 4> matrix_1{{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}};
            matrix::matrix<4, 4> matrix_2 = matrix_0 * matrix_1;
            expect(matrix_2 * matrix_1.inverse() == matrix_0);
        };
    };
}
