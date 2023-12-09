cmake_minimum_required(VERSION 3.24)
project(TI301I_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Main_Project main.c src/appointments.c headers/appointments.h)
