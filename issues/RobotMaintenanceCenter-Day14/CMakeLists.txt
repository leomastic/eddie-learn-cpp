cmake_minimum_required(VERSION 3.26)
project(robot_maintenance_center_14 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ROBOT_MAINTENANCE_SOURCES
    battery.cpp
    robot.cpp
    technician.cpp
    maintenance_center.cpp
    utils.cpp
)

add_executable(robot_maintenance_center_14
    main.cpp
    ${ROBOT_MAINTENANCE_SOURCES}
)

add_executable(robot_maintenance_center_14_tests
    tests.cpp
    ${ROBOT_MAINTENANCE_SOURCES}
)

foreach(target robot_maintenance_center_14 robot_maintenance_center_14_tests)
    target_compile_options(${target} PRIVATE
        "$<$<CONFIG:Debug>:-g;-O0>"
        "$<$<CONFIG:Release>:-O3>"
    )

    target_include_directories(${target} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endforeach()
