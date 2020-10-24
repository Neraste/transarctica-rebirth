# add tests
add_subdirectory(gameplay)

# create unit executable
add_executable(unit
    unit.cpp
)

target_link_libraries(
    unit
    PRIVATE
        Boost::unit_test_framework
        test-train
)

# create unit test
add_test(
    NAME
        unit
    COMMAND
        unit --log_level=test_suite
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}
)
