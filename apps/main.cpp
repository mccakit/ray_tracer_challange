import std;
import matrix;

auto main() -> int
{
    matrix::matrix<4, 4> matrix_8{{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}};
    matrix_8.print();
    std::cout << "\n";
    matrix::matrix<4, 4> matrix_9{{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}};
    matrix_8.transpose().print();
    return 0;
}
