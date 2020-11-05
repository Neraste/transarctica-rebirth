add_library(
    test-train
    OBJECT
    test_merchandises.cpp
    test_cars.cpp
    # test_train.cpp
)

target_link_libraries(
    test-train
    PRIVATE
        train
)
