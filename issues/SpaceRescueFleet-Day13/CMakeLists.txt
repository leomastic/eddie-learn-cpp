cmake_minimum_required(VERSION 3.26)
project(space_rescue_fleet_13 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(space_rescue_fleet_13
    main.cpp
    robot.cpp
    state_machine.cpp
    fleet.cpp
    simulation.cpp
    utils.cpp
    battery.cpp
)
