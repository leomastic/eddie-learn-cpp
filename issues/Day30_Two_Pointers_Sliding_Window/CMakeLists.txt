cmake_minimum_required(VERSION 3.16)

project(Day30_Two_Pointers_Sliding_Window LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

foreach(problem RANGE 1 5)
    add_executable(problem${problem} problem${problem}.cpp)
endforeach()
