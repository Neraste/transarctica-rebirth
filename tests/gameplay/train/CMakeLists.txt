add_library(
    test-train
    OBJECT
    test_merchandises.cpp
    test_cars.cpp
)

target_link_libraries(
    test-train
    PRIVATE
        train
)
