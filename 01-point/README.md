# Solution to Wyzant Point Conversion to Spherical Question

This is my solution to a question posted on Wyzant which I was unable to post because the answer was more than 10,000 characters.

## Summary

Here's a better implementation.

I've added a stream operator overload that allows you to specify how you want the coordinates output, cartesian or spherical. So to print a Point, you simply run

```cpp
#include <iostream>
#include <iomanip>

Point point;
std::cout << "Point in cartesian: " << cartesian << point << std::endl;
std::cout << "Point in spherical: " << spherical << point << std::endl;
```

## Build Files

But before I add the source, here's a CMakeLists.txt and a CMakePresets.json file so you're guaranteed to get the right compile options on the command line.

Place the text from CMakeLists.txt and CMakePresets.json into files by those names and place the code from the box with the solution at the bottom into a file named problem.cpp. Then cd into that directory and run:

```bash
cmake --preset=production
cmake --build --preset=build-production
```

## How to Run the Solution

This should give you the result in out/build/production/problem, which you can run via:

```bash
out/build/production/problem
```

I set it up to take multiple inputs on the command line and to terminate input with Ctrl+D (the EOF character in Linux, signaling the end of a file or input). Here's a sample output:

```bash
root@9acff118dc20:/workspaces/Sandbox# out/build/production/problem 
Enter points in the format: X Y Z (Ctrl+D to end input):
1 2 3
Point added: Point(1, 2, 3)
3 3 3
Point added: Point(3, 3, 3)
[Ctrl+D] (Note: Does not show up in terminal; no new line or anything)
Cartesian: Point(1, 2, 3)
Spherical: Point(3.74166, 0.640522, 1.10715)
Cartesian: Point(3, 3, 3)
Spherical: Point(5.19615, 0.955317, 0.785398)
```

Note that the output angles are in radians. I'll leave it as a fun exercise to write stream modifiers named "radians" and "degrees" similar to "cartesian" and "spherical" in order to tell the stream to write output of spherical coordinates in either radians or degrees. Try it. It's useful to know how to do.

## CMake and GCC Version Details

In order to get this solution to build, make sure you're using these versions at least for CMake and GCC.

CMake version: 3.28.3
GNU GCC version: g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0

## The Repository with Devcontainer Files

Specifically, I ran this in a devcontainer in VS Code. The devcontainer.json and Dockerfile are listed below as well.

The repository containing all of these files can be found at https://github.com/snarfable/point-problem-wyzant. In VS Code, make sure you have the Dev Containers (formerly known as Remote - Containers) installed, and then you can run Ctrl+Shift+P and type "Clone repository" which should bring up Clone Repository in Named Container Volume. See image below. Then you might see a window pop up asking whether you want to trust the workspace. Select to trust it and everything should build and you should end up with exactly the same development environment under which I built this example.

Good luck and let me know if anyone needs any additional help.

## Explicit Listing of File Contents

Here are the files explicitly.

.devcontainer/devcontainer.json:
```json
{
  "name": "C++ and CMake",
  "build": {
    "dockerfile": "Dockerfile",
    "context": ".."
  },
  "customizations": {
    "vscode": {
      "extensions": [
        "ms-vscode.cpptools",
        "ms-vscode.cmake-tools"
      ]
    }
  }
}
```

.devcontainer/Dockerfile:
```Dockerfile
FROM ubuntu:24.04

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        gdb \
        git \
        ninja-build \
    && rm -rf /var/lib/apt/lists/*
```

CMakeLists.txt:
```bash
cmake_minimum_required(VERSION 3.10)

project(problem VERSION 1.0)

add_executable(problem problem.cpp)
target_compile_options(problem PRIVATE -std=c++20)
```

CMakePresets.json:
```json
{
    "version": 8,
    "configurePresets": [
        {
            "name": "production",
            "displayName": "Configure preset using toolchain file",
            "description": "Sets Ninja generator, build and install directory",
            "generator": "Unix Makefiles",
            "binaryDir": "${sourceDir}/out/build/${presetName}",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "CMAKE_TOOLCHAIN_FILE": "",
                "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "build-production",
            "configurePreset": "production",
            "description": "Builds the project using the default configuration preset"
        }
    ]
}
```

problem.cpp:
```cpp
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
    std::vector<Point> inputValues;
    double X, Y, Z;

    std::cout << "Enter points in the format: X Y Z (Ctrl+D to end input):" << std::endl;
    while (std::cin >> X >> Y >> Z && std::cin.fail() == false)
    {
        inputValues.emplace_back(X, Y, Z);
        std::cout << "Point added: " << inputValues.back() << std::endl;
    }

    for (const auto &point : inputValues)
    {
        std::cout << "Spherical: " << spherical << point << std::endl;
    }

    return 0;
}
```
