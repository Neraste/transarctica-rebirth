# cmake version
cmake_minimum_required(
    VERSION
        3.9
    FATAL_ERROR
)

# project definition
project(
    TransarcticaRebirth
    VERSION
        0.0.0
    LANGUAGES
        CXX
)

# set bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# set C++ standard
set(CMAKE_CXX_STANDARD 11)

# set include directory
include_directories(include)

# external libraries
find_package(
    Boost
    REQUIRED
    COMPONENTS
        unit_test_framework
)

option(
    TESTING
    "Build tests"
    ON
)

add_subdirectory(src)

# testing
if(TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
