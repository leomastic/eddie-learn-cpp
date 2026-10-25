cmake_minimum_required(VERSION 3.26)
project(mars_base_operations VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mars_base_operations
    main.cpp
    astronaut.cpp
    mission.cpp
    inventory.cpp
    report.cpp
    utils.cpp
)

target_compile_options(mars_base_operations PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
