/**
 * @file problem.cpp
 * @brief Representation and coordinate calculations for a 3D Point.
 */

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>
#include <array>
#include <map>

/**
 * @defgroup Constructors Constructors
 * @brief Group of constructor functions for initializing Point objects.
 */

/**
 * @defgroup Getters Getters
 * @brief Group of getter functions for accessing Cartesian and spherical coordinates.
 */

/**
 * @brief Enumeration of output coordinate systems for Point stream formatting.
 */
enum class PointFormat : long
{
    Cartesian = 0,
    Spherical = 1
};

/** @brief Index for storing Point format state in std::ios_base. */
static const int point_format_index = std::ios_base::xalloc();

/**
 * @brief Stream manipulator to set Point output format to Cartesian coordinates.
 * @param os The output stream.
 * @return Reference to the output stream.
 */
inline std::ostream &cartesian(std::ostream &os)
{
    os.iword(point_format_index) = static_cast<long>(PointFormat::Cartesian);
    return os;
}

/**
 * @brief Stream manipulator to set Point output format to Spherical coordinates.
 * @param os The output stream.
 * @return Reference to the output stream.
 */
inline std::ostream &spherical(std::ostream &os)
{
    os.iword(point_format_index) = static_cast<long>(PointFormat::Spherical);
    return os;
}

/**
 * @class Point
 * @brief Represents a point in 3D Cartesian space with spherical coordinate conversion methods.
 */
class Point
{
private:
    /** @brief X-coordinate of the point. */
    double x;
    /** @brief Y-coordinate of the point. */
    double y;
    /** @brief Z-coordinate of the point. */
    double z;

public:
    /**
     * @addtogroup Constructors
     * @brief Constructs a Point object at the origin (0, 0, 0).
     *
     * Default constructor initializes the point to the origin (0, 0, 0).
     * Make sure to keep this constructor, as it is used in the main function to
     * create a Point object.
     */
    Point() : x(0.0), y(0.0), z(0.0)
	{}

    /**
     * @addtogroup Constructors
     * @brief Constructs a Point object with specified coordinates.
     *
     * This constructor is useful if you know the coordinates of the point in
     * advance. It allows you to create a Point object with specific x, y, and z
     * values.
     *
     * @param X The x-coordinate.
     * @param Y The y-coordinate.
     * @param Z The z-coordinate.
     */
    Point(double X, double Y, double Z) : x(X), y(Y), z(Z) {}

    /**
     * @addtogroup Getters
     * @brief Returns the x-coordinate of the point.
     * @return The x-coordinate.
     */
    double getX() const {
        return x;
    }

    /**
     * @addtogroup Getters
     * @brief Returns the y-coordinate of the point.
     * @return The y-coordinate.
     */
    double getY() const {
        return y;
    }

    /**
     * @addtogroup Getters
     * @brief Returns the z-coordinate of the point.
     * @return The z-coordinate.
     */
    double getZ() const {
        return z;
    }

    /**
     * @addtogroup Getters
     * @brief Computes and returns the radial distance (r) from the origin.
     * @return The radial distance r.
     */
    double getRadius() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    /**
     * @addtogroup Getters
     * @brief Computes and returns the polar angle (phi) in radians.
     * @return The polar angle in radians.
     */
    double getPhi() const {
        return std::acos(z / std::sqrt(x * x + y * y + z * z));
    }

    /**
     * @addtogroup Getters
     * @brief Computes and returns the azimuthal angle (theta) in radians.
     * @return The azimuthal angle in radians.
     */
    double getTheta() const {
        if (x >= 0) {
            return std::atan(y / x);
        } else {
            return std::atan(x / y + std::numbers::pi);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &p);
};

/**
 * @brief Overloads the << operator for outputting Point objects according to stream coordinate format state.
 * @param os The output stream.
 * @param p The Point object to output.
 * @return Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &os, const Point &p)
{
    PointFormat fmt = static_cast<PointFormat>(os.iword(point_format_index));

    if (fmt == PointFormat::Spherical)
        os << "Point(" << p.getRadius() << ", " << p.getPhi() << ", " << p.getTheta() << ")";
    else
        os << "Point(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
    return os;
}

/**
 * @brief Main function demonstrating Point instantiation and stream manipulators.
 * @return Returns 0 on successful execution.
 */
int main() {
    Point p1;
    std::map<std::string, Point> inputValues;
    double X, Y, Z;

    std::cout << "Enter points in the format: X Y Z (Ctrl+D to end input):" << std::endl;
    std::size_t idx = 0;
    while (std::cin >> X >> Y >> Z && std::cin.fail() == false)
    {
        std::string key = "point" + std::to_string(idx++);
        inputValues.emplace(key, Point{X, Y, Z});
        std::cout << "Point added: " << inputValues.find(key)->second << std::endl;
    }

    for (const auto &[key, point] : inputValues)
    {
        std::cout << "Cartesian: " << cartesian << key << " -> " << point << std::endl;
        std::cout << "Spherical: " << spherical << key << " -> " << point << std::endl;
    }

    return 0;
}
