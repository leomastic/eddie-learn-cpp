cmake_minimum_required(VERSION 3.16)

project(Day25_Persistent_CRUD_and_Data_Integrity LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(day25_maintenance_log
    main.cpp
    maintenance_record.cpp
    maintenance_log.cpp
    maintenance_file.cpp
)
