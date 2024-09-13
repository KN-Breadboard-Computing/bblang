cmake_file_template = \
    """cmake_minimum_required(VERSION 3.15)
project({name}parser)

# Find Flex and Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Define C++ flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${{CMAKE_CXX_FLAGS}} -Wall -Wextra -Werror")

# Define the Flex and Bison input files
set(FLEX_INPUT ${{CMAKE_CURRENT_SOURCE_DIR}}/{name}.l)
set(BISON_INPUT ${{CMAKE_CURRENT_SOURCE_DIR}}/{name}.y)

# Set the output files for Flex and Bison
set(FLEX_OUTPUT ${{CMAKE_CURRENT_BINARY_DIR}}/../{name}_lexer.cpp)
set(BISON_OUTPUT ${{CMAKE_CURRENT_BINARY_DIR}}/../{name}_parser.cpp)
set(BISON_OUTPUT_HEADER ${{CMAKE_CURRENT_BINARY_DIR}}/../{name}_parser.hpp)

# Custom arguments and flags for Bison to generate C++ code
set(BISON_FLAGS "--defines=${{BISON_OUTPUT_HEADER}} --no-lines --language=c++")

# Run Bison to generate the parser files
BISON_TARGET({name}_parser ${{BISON_INPUT}} ${{BISON_OUTPUT}} DEFINES_FILE ${{BISON_OUTPUT_HEADER}})

# Run Flex to generate the lexer file
FLEX_TARGET({name}_lexer ${{FLEX_INPUT}} ${{FLEX_OUTPUT}})

# Ensure Bison is run before Flex, and Flex is run before compiling
ADD_FLEX_BISON_DEPENDENCY({name}_lexer {name}_parser)

# Create a custom target to ensure these files are generated
add_custom_target({name}_parser_generator ALL
    DEPENDS ${{FLEX_OUTPUT}} ${{BISON_OUTPUT}} ${{BISON_OUTPUT_HEADER}}
)"""


def get_cmake_filename(input_file_name: str) -> str:
    return "CMakeLists.txt"


def write_cmake_file(input_file_name: str, output_file: str) -> None:
    with open(output_file, 'w') as file:
        if '/' in input_file_name:
            input_file_name = input_file_name.split('/')[-1]
        file.write(cmake_file_template.format(name=input_file_name.split('.')[0]))
