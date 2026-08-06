cmake_minimum_required(VERSION 3.26)
project(mars_greenhouse_control_center VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mars_greenhouse_control_center
    main.cpp
    water_tank.cpp
    plant_batch.cpp
    greenhouse.cpp
    greenhouse_center.cpp
    utils.cpp
)

add_executable(mars_greenhouse_control_tests
    tests.cpp
    water_tank.cpp
    plant_batch.cpp
    greenhouse.cpp
    greenhouse_center.cpp
    utils.cpp
)