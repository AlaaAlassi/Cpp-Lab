cmake_minimum_required(VERSION 2.8.11)
Project(Multi_threading_demo)

file(GLOB files ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

set(i 0)
foreach(file ${files})
message(${file})
get_filename_component(execName ${file} NAME_WE)
add_executable(${execName} ${file})
set_property(TARGET ${execName} PROPERTY CXX_STANDARD 20)
target_link_libraries (${execName} pthread)
math(EXPR i "${i} + 1")
endforeach()