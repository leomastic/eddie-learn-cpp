cmake_minimum_required(VERSION 3.26)
project(space_cargo_delivery_center_14 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(space_cargo_delivery_center_14
    main.cpp
    fuel_tank.cpp
    cargo.cpp
    vehicle.cpp
    delivery_center.cpp
    utils.cpp
)

add_executable(space_cargo_delivery_center_tests
    tests.cpp
    fuel_tank.cpp
    cargo.cpp
    vehicle.cpp
    delivery_center.cpp
    utils.cpp
)