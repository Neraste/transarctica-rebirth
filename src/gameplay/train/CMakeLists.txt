add_library(
    train
    merchandises.cpp
    cars.cpp
)

target_include_directories(
    train
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/gameplay/train
)
