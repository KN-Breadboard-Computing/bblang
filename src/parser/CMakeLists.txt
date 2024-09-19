cmake_minimum_required(VERSION 3.15)
project(bblangparser)

# Find Flex and Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Define C++ flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Define the Flex and Bison input files
set(FLEX_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/bblang.l)
set(BISON_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/bblang.y)

# Set the output files for Flex and Bison
set(FLEX_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/../bblang_lexer.cpp)
set(BISON_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/../bblang_parser.cpp)
set(BISON_OUTPUT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/../bblang_parser.hpp)

# Custom arguments and flags for Bison to generate C++ code
set(BISON_FLAGS "--defines=${BISON_OUTPUT_HEADER} --no-lines --language=c++")

# Run Bison to generate the parser files
BISON_TARGET(bblang_parser ${BISON_INPUT} ${BISON_OUTPUT} DEFINES_FILE ${BISON_OUTPUT_HEADER})

# Run Flex to generate the lexer file
FLEX_TARGET(bblang_lexer ${FLEX_INPUT} ${FLEX_OUTPUT})

# Ensure Bison is run before Flex, and Flex is run before compiling
ADD_FLEX_BISON_DEPENDENCY(bblang_lexer bblang_parser)

# Create a custom target to ensure these files are generated
add_custom_target(bblang_parser_generator ALL
    DEPENDS ${FLEX_OUTPUT} ${BISON_OUTPUT} ${BISON_OUTPUT_HEADER}
)