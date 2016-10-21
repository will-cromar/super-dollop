cmake_minimum_required(VERSION 2.8)
project(super-dollop)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(DRIVER_SOURCE_FILES compiler.c)
set(LEXER_SOURCE_FILES lexer/lexer.c lexer/symbol_detection.c lexer/input_output.c)
set(VM_SOURCE_FILES virtual_machine/input_output.c virtual_machine/instructions.c virtual_machine/util.c virtual_machine/vm.c)

add_executable(compiler ${DRIVER_SOURCE_FILES} ${LEXER_SOURCE_FILES} ${VM_SOURCE_FILES})