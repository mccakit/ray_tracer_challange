export module matrix_transformations;
import std;
import tuple;
import matrix;

export namespace matrix_transformations
{
matrix::matrix<4, 4> translation(const int x, const int y, const int z)
{
    matrix::matrix<4, 4> output{matrix::identity_matrix()};
    output(3, 0) = x;
    output(3, 1) = y;
    output(3, 2) = z;
    return output;
}
matrix::matrix<4, 4> scaling(const int x, const int y, const int z)
{
    matrix::matrix<4, 4> output{matrix::identity_matrix()};
    output(0, 0) = x;
    output(1, 1) = y;
    output(2, 2) = z;
    return output;
}
matrix::matrix<4, 4> rotation_x(const float radians)
{
    matrix::matrix<4, 4> output{matrix::identity_matrix()};
    output(1, 1) = std::cos(radians);
    output(1, 2) = std::sin(radians);
    output(2, 1) = -std::sin(radians);
    output(2, 2) = std::cos(radians);
    return output;
}
matrix::matrix<4, 4> rotation_y(const float radians)
{
    matrix::matrix<4, 4> output{matrix::identity_matrix()};
    output(0, 0) = std::cos(radians);
    output(0, 2) = -std::sin(radians);
    output(2, 0) = std::sin(radians);
    output(2, 2) = std::cos(radians);
    return output;
}
matrix::matrix<4, 4> rotation_z(const float radians)
{
    matrix::matrix<4, 4> output{matrix::identity_matrix()};
    output(0, 0) = std::cos(radians);
    output(0, 1) = std::sin(radians);
    output(1, 0) = -std::sin(radians);
    output(1, 1) = std::cos(radians);
    return output;
}
matrix::matrix<4, 4> shearing(const float xy, const float xz, const float yx, const float yz, const float zx,
                              const float zy)
{
    matrix::matrix<4, 4> output{matrix::identity_matrix()};
    output(1, 0) = xy;
    output(2, 0) = xz;
    output(0, 1) = yx;
    output(0, 2) = zx;
    output(2, 1) = yz;
    output(1, 2) = zy;
    return output;
}
}; // namespace matrix_transformations
