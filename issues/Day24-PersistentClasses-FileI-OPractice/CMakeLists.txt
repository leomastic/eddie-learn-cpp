cmake_minimum_required(VERSION 3.16)
project(Day24_Persistent_Classes_File_IO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day24_maintenance_log
    main.cpp
    maintenance_record.cpp
    maintenance_log.cpp
    maintenance_file.cpp
)
