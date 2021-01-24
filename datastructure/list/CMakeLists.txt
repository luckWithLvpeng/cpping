cmake_minimum_required(VERSION 3.17)

project(list)
FILE(GLOB source_files "*.cpp")
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}   ${source_files})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")