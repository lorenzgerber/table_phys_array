cmake_minimum_required(VERSION 3.3)
project(table_phys_array)

set(CMAKE_C_FLAGS "-std=c99")


set(SOURCE_FILES table.c table.h main.c)
add_executable(tabletest ${SOURCE_FILES} main.c)
