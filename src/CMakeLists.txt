cmake_minimum_required(VERSION 3.15)
project(bblang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(LLVM REQUIRED CONFIG)

separate_arguments(LLVM_DEFINITIONS)

# Set up paths for LLVM headers and libraries
include_directories(${LLVM_INCLUDE_DIRS})

# LLVM requires some additional definitions
add_definitions(${LLVM_DEFINITIONS})

set(PARSER_DIR ${CMAKE_SOURCE_DIR}/parser)
set(PARSER_SOURCES
        ${PARSER_DIR}/bblang_lexer.cpp
        ${PARSER_DIR}/bblang_parser.cpp
        ${PARSER_DIR}/bblang_parser.hpp
        )

file(GLOB AST_SOURCES "${CMAKE_SOURCE_DIR}/ast/*.cpp")
file(GLOB SEMANTIC_SOURCES "${CMAKE_SOURCE_DIR}/semantic-check/*.cpp")
file(GLOB CODEGEN_SOURCES "${CMAKE_SOURCE_DIR}/code-gen/*.cpp")

# Generate parser
add_custom_command(
        OUTPUT ${PARSER_SOURCES}
        COMMAND ${CMAKE_COMMAND} -S ${PARSER_DIR} -B ${PARSER_DIR}/build
        COMMAND ${CMAKE_COMMAND} --build ${PARSER_DIR}/build
        COMMENT "Configuring and building parser"
        DEPENDS ${PARSER_DIR}/CMakeLists.txt
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
)
add_custom_target(bblangparser ALL DEPENDS ${PARSER_SOURCES})

# Generate compiler
add_executable(bblangcompiler
        ${PARSER_SOURCES}
        ${AST_SOURCES}
        ${SEMANTIC_SOURCES}
        ${CODEGEN_SOURCES}
        main.cpp
        )

add_dependencies(bblangcompiler bblangparser)

execute_process(
        COMMAND llvm-config --libs all
        OUTPUT_VARIABLE llvm_libs
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_link_libraries(bblangcompiler ${llvm_libs})
