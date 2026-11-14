cmake_minimum_required(VERSION 3.16)

project(Day31_Provincial_HSG_Mock_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

foreach(problem PARKING SENSORS WAREHOUSE STABLE TEAMS)
    add_executable(${problem} ${problem}.cpp)
endforeach()
