cmake_minimum_required(VERSION 3.26)
project(robot VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add debug symbols
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Debug)

# Optional sample executable if main.cpp exists
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(robot
    main.cpp
    robot.cpp
    state_machine.cpp
    utils.cpp
    simulation.cpp
    )
endif()
