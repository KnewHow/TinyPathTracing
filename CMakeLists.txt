cmake_minimum_required(VERSION 3.0.0)
project(TinyPathTracing)

# source file

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCES "${SRC_DIR}/main.cpp")

file(GLOB SOURCES
    "${SRC_DIR}/*.hpp"
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/material/*.hpp"
    "${SRC_DIR}/material/*.cpp"
    "${SRC_DIR}/geometry/*.hpp"
    "${SRC_DIR}/geometry/*.cpp"
    "${SRC_DIR}/common/*.hpp"
    "${SRC_DIR}/common/*.cpp"
    "${SRC_DIR}/accelerator/*.hpp"
    "${SRC_DIR}/accelerator/*.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# TinyMath
set(TinyMath_DIR "${LIB_DIR}/TinyMath")
target_include_directories(${PROJECT_NAME} PRIVATE "${TinyMath_DIR}")