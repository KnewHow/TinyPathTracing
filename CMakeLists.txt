cmake_minimum_required(VERSION 3.0.0)
project(TinyPathTracing)

# source file

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCES "${SRC_DIR}/main.cpp")

file(GLOB SOURCES
    "${SRC_DIR}/*.hpp"
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/common/*.hpp"
    "${SRC_DIR}/common/*.cpp"
    "${SRC_DIR}/geometry/*.hpp"
    "${SRC_DIR}/geometry/*.cpp"
    "${SRC_DIR}/material/*.hpp"
    "${SRC_DIR}/material/*.cpp"
    "${SRC_DIR}/accelerator/*.hpp"
    "${SRC_DIR}/accelerator/*.cpp"
    "${SRC_DIR}/texture/*.hpp"
    "${SRC_DIR}/texture/*.cpp"
    "${SRC_DIR}/noise/*.hpp"
    "${SRC_DIR}/noise/*.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# TinyMath
set(TinyMath_DIR "${LIB_DIR}/TinyMath")
target_include_directories(${PROJECT_NAME} PRIVATE "${TinyMath_DIR}")

# stb
set(STB_DIR "${LIB_DIR}/stb")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_DIR}")

# open mp
find_package(OpenMP)
if (OPENMP_FOUND)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()