# cmake version
cmake_minimum_required(
    VERSION
        3.9
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
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set include directory
include_directories(include)

# external libraries
find_package(
    Boost
    1.66.0
    REQUIRED
    COMPONENTS
        unit_test_framework
)

find_package(
    Doxygen
    1.8
    REQUIRED
)

option(
    TESTING
    "Build tests"
    ON
)

option(
    DOCUMENTATION
    "Build documentation"
    ON
)

add_subdirectory(src)

# testing
if(TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# doc
if(DOCUMENTATION)
    add_subdirectory(doc)
endif()
