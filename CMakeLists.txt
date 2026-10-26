cmake_minimum_required(VERSION 3.10)

project(problem VERSION 1.0)

# Initialize some default paths
include(GNUInstallDirs)

# Define the minimum C++ standard that is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         v1.9.2
)

FetchContent_Declare(
    flatbuffers
    GIT_REPOSITORY  https://github.com/google/flatbuffers.git
    GIT_TAG         v2.0.0
)

FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY  https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG         1.9.4
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         release-1.11.0
)

FetchContent_MakeAvailable(flatbuffers)
FetchContent_MakeAvailable(jsoncpp)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(googletest)

# Add project subdirectories
add_subdirectory(01-point)
add_subdirectory(02-postfix)
