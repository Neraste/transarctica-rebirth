# cmake version
cmake_minimum_required(
        VERSION 3.9...3.15
        FATAL_ERROR
)

# project definition
project(
        TransarcticaRebirth
        VERSION 0.0.0
        LANGUAGES CXX
)

# external libraries
find_package(Boost REQUIRED
        COMPONENTS
                unit_test_framework
)

# gameplay library
add_library(gameplay
        src/merchandises.cpp include/merchandises.hpp
        src/cars.cpp include/cars.hpp
)
target_include_directories(gameplay PUBLIC include)

# test executable
add_executable(unit
        tests/unit.cpp
        tests/test_merchandises.cpp
        tests/test_cars.cpp
)
target_include_directories(unit PUBLIC include)
target_compile_definitions(unit PUBLIC
        BOOST_TEST_DYN_LINK
)
target_link_libraries(unit
        Boost::unit_test_framework
        gameplay
)
add_test(
        NAME unit
        COMMAND unit --log_level=test_suite
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# testing
enable_testing()
