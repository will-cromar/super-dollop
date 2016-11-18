cmake_minimum_required(VERSION 2.8)
project(super-dollop)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(DRIVER_SOURCE_FILES compile.c)
set(LEXER_SOURCE_FILES lexer/lexer.c lexer/symbol_detection.c lexer/input_output.c)
set(PARSER_SOURCE_FILES parser/parse.c parser/symbols.c parser/symbols.h)

add_executable(compiler ${DRIVER_SOURCE_FILES} ${LEXER_SOURCE_FILES} ${VM_SOURCE_FILES} ${PARSER_SOURCE_FILES})