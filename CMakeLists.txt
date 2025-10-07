cmake_minimum_required(VERSION 3.23)

project(containers)

add_executable(containers "main.c" "array_list.c")

target_link_libraries(containers cunit)

