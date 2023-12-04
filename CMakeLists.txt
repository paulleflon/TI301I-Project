cmake_minimum_required(VERSION 3.24)
project(TI301I_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_library(CommonLibrary
        headers/cell.h
        headers/list.h
        src/cell.c
        src/list.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Main_Project main.c)
add_executable(Time_Measurements headers/timer.h src/timer.c time_measurements.c)
target_link_libraries(Main_Project CommonLibrary)
target_link_libraries(Time_Measurements CommonLibrary)
