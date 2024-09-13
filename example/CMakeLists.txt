cmake_minimum_required(VERSION 3.15)
project(calc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(PARSER_DIR ${CMAKE_SOURCE_DIR}/src/parser)
set(PARSER_SOURCES
        ${PARSER_DIR}/calc_lexer.cpp
        ${PARSER_DIR}/calc_parser.cpp
        ${PARSER_DIR}/calc_parser.hpp
        )

file(GLOB AST_SOURCES "${CMAKE_SOURCE_DIR}/src/ast/*.cpp")

# Generate parser
add_custom_command(
        OUTPUT ${PARSER_SOURCES}
        COMMAND ${CMAKE_COMMAND} -S ${PARSER_DIR} -B ${PARSER_DIR}/build
        COMMAND ${CMAKE_COMMAND} --build ${PARSER_DIR}/build
        COMMENT "Configuring and building parser"
        DEPENDS ${PARSER_DIR}/CMakeLists.txt
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src
        VERBATIM
)
add_custom_target(calcparser ALL DEPENDS ${PARSER_SOURCES})

# Generate main
add_executable(calcprogram
        ${PARSER_SOURCES}
        ${AST_SOURCES}
        main.cpp
        )

add_dependencies(calcprogram calcparser)