cmake_minimum_required(VERSION 2.8)
project(super-dollop)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES lexer.c symbol-detection.c symbol-detection.h tokens.h input-output.c input-output.h)

add_executable(super-dollop ${SOURCE_FILES})