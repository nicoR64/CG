#include "Math.h"

#include <cmath>

float cg::pi()
{
    return static_cast<float>(std::atan(1)) * 4.0f;
}

bool cg::equals(float a, float b, float eps)
{
    return a + eps >= b && a - eps <= b;
}

cg::vec2 cg::zeroVec2()
{
    cg::vec2 vector;
    vector[0] = vector[1] = 0.0f;

    return vector;
}

cg::vec3 cg::zeroVec3()
{
    cg::vec3 vector;
    vector[0] = vector[1] = vector[2] = 0.0f;

    return vector;
}

cg::vec4 cg::zeroVec4()
{
    cg::vec4 vector;
    vector[0] = vector[1] = vector[2] = vector[3] = 0.0f;

    return vector;
}

cg::vec2 cg::oneVec2()
{
    cg::vec2 vector;
    vector[0] = vector[1] = 1.0f;

    return vector;
}

cg::vec3 cg::oneVec3()
{
    cg::vec3 vector;
    vector[0] = vector[1] = vector[2] = 1.0f;

    return vector;
}

cg::vec4 cg::oneVec4()
{
    cg::vec4 vector;
    vector[0] = vector[1] = vector[2] = vector[3] = 1.0f;

    return vector;
}

cg::mat2 cg::zeroMat2()
{
    cg::mat2 matrix;
    matrix[0][0] = matrix[0][1] = 0.0f;
    matrix[1][0] = matrix[1][1] = 0.0f;

    return matrix;
}

cg::mat3 cg::zeroMat3()
{
    cg::mat3 matrix;
    matrix[0][0] = matrix[0][1] = matrix[0][2] = 0.0f;
    matrix[1][0] = matrix[1][1] = matrix[1][2] = 0.0f;
    matrix[2][0] = matrix[2][1] = matrix[2][2] = 0.0f;

    return matrix;
}

cg::mat4 cg::zeroMat4()
{
    cg::mat4 matrix;
    matrix[0][0] = matrix[0][1] = matrix[0][2] = matrix[0][3] = 0.0f;
    matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[1][3] = 0.0f;
    matrix[2][0] = matrix[2][1] = matrix[2][2] = matrix[2][3] = 0.0f;
    matrix[3][0] = matrix[3][1] = matrix[3][2] = matrix[3][3] = 0.0f;

    return matrix;
}

cg::mat2 cg::unitMat2()
{
    cg::mat2 matrix = zeroMat2();
    matrix[0][0] = matrix[1][1] = 1.0f;

    return matrix;
}

cg::mat3 cg::unitMat3()
{
    cg::mat3 matrix = zeroMat3();
    matrix[0][0] = matrix[1][1] = matrix[2][2] = 1.0f;

    return matrix;
}

cg::mat4 cg::unitMat4()
{
    cg::mat4 matrix = zeroMat4();
    matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1.0f;

    return matrix;
}

cg::Color cg::black()
{
    cg::Color vector;
    vector[0] = vector[1] = vector[2] = 0.0f;
    vector[3] = 1.0f;

    return vector;
}

cg::Color cg::white()
{
    cg::Color vector;
    vector[0] = vector[1] = vector[2] = vector[3] = 1.0f;

    return vector;
}

cg::Color cg::red()
{
    cg::Color vector;
    vector[0] = vector[3] = 1.0f;
    vector[1] = vector[2] = 0.0f;

    return vector;
}

cg::Color cg::green()
{
    cg::Color vector;
    vector[1] = vector[3] = 1.0f;
    vector[0] = vector[2] = 0.0f;

    return vector;
}

cg::Color cg::blue()
{
    cg::Color vector;
    vector[2] = vector[3] = 1.0f;
    vector[0] = vector[1] = 0.0f;

    return vector;
}

cg::Triangle2D::Triangle2D()
{
}

cg::Triangle2D::Triangle2D(const cg::Triangle &other)
{
    this->points = {
        Point{Point2D(other.points[0].position), other.points[0].color},
        Point{Point2D(other.points[1].position), other.points[1].color},
        Point{Point2D(other.points[2].position), other.points[2].color}};
}

namespace
{
    bool sameSide(const cg::Point2D &first, const cg::Point2D &second, const cg::Point2D &line_start, const cg::Point2D &line_end)
    {
        const auto line = line_end - line_start;
        const auto first_line = first - line_start;
        const auto second_line = second - line_start;

        const float cp1 = line.x * first_line.y - line.y * first_line.x;
        const float cp2 = line.x * second_line.y - line.y * second_line.x;

        return glm::dot(cp1, cp2) >= 0.0f;
    }
}

bool cg::pointInTriangle(const cg::Triangle2D &triangle, const cg::Point2D &position)
{
    return sameSide(position, triangle.points[0].position, triangle.points[1].position, triangle.points[2].position) && sameSide(position, triangle.points[1].position, triangle.points[0].position, triangle.points[2].position) && sameSide(position, triangle.points[2].position, triangle.points[0].position, triangle.points[1].position);
}

cg::vec3 cg::calculateBarycentricCoords(const Triangle2D &triangle, const cg::Point2D &position)
{
    const float x0 = triangle.points[0].position.x;
    const float y0 = triangle.points[0].position.y;
    const float x1 = triangle.points[1].position.x;
    const float y1 = triangle.points[1].position.y;
    const float x2 = triangle.points[2].position.x;
    const float y2 = triangle.points[2].position.y;

    const float x = position.x;
    const float y = position.y;

    const float denominator = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2);

    float weight_a = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) / denominator;
    float weight_b = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) / denominator;
    float weight_c = 1.0f - weight_a - weight_b;

    float determinant = dBA * dCA - dCBA * dCBA;

    weight_b = (dCA * dPBA - dCBA * dPCA) / determinant;
    weight_c = (dBA * dPCA - dCBA * dPBA) / determinant;

    weight_a = 1 - weight_b - weight_c;

    return vec3(weight_a, weight_b, weight_c);
}

cg::Point3D cg::sphericalToCartesian(const float r, const float teta, const float phi)
{
    const float x = r * std::sin(teta) * std::cos(phi);
    const float y = r * std::sin(teta) * std::sin(phi);
    const float z = r * std::cos(teta);

    return Point3D(x, y, z);
}
