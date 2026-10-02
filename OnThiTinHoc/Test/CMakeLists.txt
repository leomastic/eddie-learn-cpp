cmake_minimum_required(VERSION 3.16)
project(OnThiTinHoc_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(src IN LISTS TEST_SOURCES)
    get_filename_component(target_name "${src}" NAME_WE)
    add_executable(${target_name} "${src}")
endforeach()
