cmake_minimum_required(VERSION 3.16)

project(ConfigLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)

file(GLOB SOURCES src/*.cpp)

file(GLOB TEST main.cpp)

add_library(config SHARED ${SOURCES})
add_executable(test ${TEST})

target_include_directories(config
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(test PRIVATE config)

target_include_directories(config PRIVATE include)
target_compile_options(config PRIVATE -Wall -Wextra -O3)