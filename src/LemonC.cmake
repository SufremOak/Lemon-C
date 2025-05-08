# Lemon-C SDK CMake Configuration
# This file provides the necessary configuration for using the Lemon-C SDK in your project

# Set minimum required CMake version
cmake_minimum_required(VERSION 3.14)

# Define the SDK version
set(LEMONC_VERSION "1.0.0")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the SDK include directories
set(LEMONC_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

# Create the Lemon-C library target
add_library(lemonc STATIC
    "${CMAKE_CURRENT_LIST_DIR}/src/Baselang.cpp"
)

# Set include directories for the library
target_include_directories(lemonc
    PUBLIC
        ${LEMONC_INCLUDE_DIRS}
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Set compile definitions
target_compile_definitions(lemonc
    PUBLIC
        LEMONC_VERSION="${LEMONC_VERSION}"
)

# Export the library for use in other projects
install(TARGETS lemonc
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(FILES "${LEMONC_INCLUDE_DIRS}/Baselang.h"
    DESTINATION include/lemonc
)

# Export package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LemonCConfigVersion.cmake"
    VERSION ${LEMONC_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Usage instructions for other projects
set(LEMONC_USAGE "
# To use Lemon-C in your project:
find_package(LemonC REQUIRED)
target_link_libraries(your_target PRIVATE lemonc)
") 