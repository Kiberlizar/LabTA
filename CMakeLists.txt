cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(LabaTA)

file(GLOB SOURCES *.cpp)

add_executable(LabaTA ${SOURCES})

