# add tests
add_subdirectory(gameplay)

# create test unit executable
add_executable(
    test-unit
    test_unit.cpp
)

target_link_libraries(
    test-unit
    PRIVATE
        Boost::unit_test_framework
        test-train
)

# requested by older version of boost
target_compile_definitions(
    test-unit
    PRIVATE
        BOOST_TEST_DYN_LINK
)

# create unit test
add_test(
    NAME
        unit
    COMMAND
        test-unit --log_level=test_suite
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}
)
