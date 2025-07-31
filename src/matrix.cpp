export module matrix;
import std;
import tuple;
/**
 * @brief Namespace containing matrix types and operations.
 */
export namespace matrix
{
/**
* @brief A generic matrix class supporting various dimensions.
* @tparam X The number of columns in the matrix.
* @tparam Y The number of rows in the matrix.
* Each tuple are columns not rowss
*/
template <int X, int Y> class matrix
{
  public:
    std::array<tuple::tuple<X>, Y> tuples{};
    /**
     * @brief Constructs a matrix from an array of tuples.
     */
    matrix(const std::array<tuple::tuple<X>, Y> &input_data) : tuples{input_data}
    {
    }
    /**
     * @brief Constructs a matrix from an initializer list of tuples.
     */
    matrix(const std::initializer_list<tuple::tuple<X>> &input_data)
    {
        std::copy(input_data.begin(), input_data.end(), tuples.begin());
    }
    tuple::tuple<X> &operator[](const int index)
    {
        return tuples[index];
    }
    tuple::tuple<X> operator[](const int index) const
    {
        return tuples[index];
    }
    float &operator[](const int tuple, const int element)
    {
        return tuples[element][tuple];
    }
    float operator[](const int tuple, const int element) const
    {
        return tuples[element][tuple];
    }
    int size()
    {
        return tuples.size();
    }
    /**
     * @brief Tranposes a matrix
     */
    matrix<Y, X> transpose()
    {
        matrix<Y, X> result{};
        for (int col{0}; col < Y; ++col)
        {
            for (int row{0}; row < X; ++row)
            {
                result[col][row] = tuples[row][col];
            }
        }
        return result;
    }
    /**
     * @brief Prints a matrix + new line
     */
    void print() const
    {
        for (int row = 0; row < Y; ++row)
        {
            std::cout << "| ";
            for (int col = 0; col < X; ++col)
            {
                std::cout << tuples[row][col] << " ";
            }
            std::cout << "|\n";
        }
    }
    /**
     * @brief Returns the submatrix of a matrix
     */
    matrix<X - 1, Y - 1> submatrix(const int ignore_row, const int ignore_col)
    {
        matrix<X - 1, Y - 1> result{};
        for (int row{0}; row < X; ++row)
        {
            for (int col{0}; col < Y; ++col)
            {
                if (row == ignore_row || col == ignore_col)
                {
                    continue;
                }
                result[(row > ignore_row) ? row - 1 : row][(col > ignore_col) ? col - 1 : col] = tuples[row][col];
            }
        }
        return result;
    }
    /**
     * @brief Returns the determinant of a matrix with cofactor expansion
     */
    float determinant()
    {
        if constexpr (X == 1)
        {
            return tuples[0][0];
        }
        else if (this->size() == 2)
        {
            return (tuples[0][0] * tuples[1][1]) - (tuples[0][1] * tuples[1][0]);
        }
        else
        {
            float result{0};
            for (int col{0}; col < Y; ++col)
            {
                result += this->cofactor(0, col) * tuples[0][col];
            }
            return result;
        }
    }
    /**
     * @brief Returns the minor of a matrix
     */
    float minor(const int ignore_row, const int ignore_col)
    {
        return this->submatrix(ignore_row, ignore_col).determinant();
    }
    /**
     * @brief Returns the cofactor of a matrix
     */
    float cofactor(const int ignored_row, const int ignored_col)
    {
        if ((ignored_row + ignored_col) % 2 != 0)
        {
            return this->minor(ignored_row, ignored_col) * -1;
        }
        return this->minor(ignored_row, ignored_col);
    }
    bool invertible()
    {
        return this->determinant() != 0;
    }
    /**
     * @brief Returns the inverse of a matrix
     */
    matrix inverse()
    {
        matrix<X, Y> output {};
        for (int col{}; col < Y; ++col)
        {
            for (int row{}; row < X; ++row)
            {
                output[row][col] = this->cofactor(row, col);
            }
        }
        output = output.transpose();
        output = output * 1 / this->determinant();
        return output;
    }

};
template <int X, int Y> bool operator==(const matrix<X, Y> &lhs_matrix, const matrix<X, Y> &rhs_matrix)
{
    for (int i{0}; i < Y; ++i)
    {
        if (lhs_matrix[i] != rhs_matrix[i])
        {
            return false;
        }
    }
    return true;
}
template <int X, int Y>
matrix<X, Y> operator*(const matrix<X, Y>& ls_matrix, const float num)
{
    matrix<X, Y> result {ls_matrix};
    for (int col{}; col < Y; ++col)
    {
        for (int row{}; row < X; ++row)
        {
            result[row][col] *= num;
        }
    }
    return result;
}
template <int X, int Y>
matrix<X, Y> operator/(const matrix<X, Y>& ls_matrix, const float num)
{
    matrix<X, Y> result{ls_matrix};
    for (auto& row : result.tuples)
    {
        for (int i = 0; i < X; ++i)
        {
            row[i] /= num;
        }
    }
    return result;
}
tuple::tuple<4> operator*(const matrix<4, 4> &ls_matrix, const tuple::tuple<4> &rs_tuple)
{
    tuple::tuple<4> output{rs_tuple};
    for (int row{0}; row < 4; ++row)
    {
        output[row] = tuple::dot_product(ls_matrix[row], rs_tuple);
    }
    return output;
}
matrix<4, 4> operator*(const matrix<4, 4> &ls_matrix, const matrix<4, 4> &rs_matrix)
{
    matrix<4, 4> output{std::array<tuple::tuple<4>, 4>{}};

    for (int col{0}; col < 4; ++col)
    {
        tuple::tuple<4> column = rs_matrix[col];
        for (int row{0}; row < 4; ++row)
        {
            tuple::tuple<4> left_row{ls_matrix[0][row], ls_matrix[1][row], ls_matrix[2][row], ls_matrix[3][row]};
            output[col][row] = tuple::dot_product(left_row, column);
        }
    }
    return output;
}
/**
 * @brief Returns 4x4 identity matrix
 */
matrix<4, 4> identity_matrix()
{
    return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}
} // namespace matrix
