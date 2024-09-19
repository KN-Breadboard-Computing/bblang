import argparse
import os

from reader import read_description
from generator import generate_definitions, get_single_line_comment_begin, get_multi_line_comment_begin_end
from naming import get_flex_filename, get_bison_filename, get_class_filename, get_cmake_filename
from flex_writer import write_flex_file
from bison_writer import write_bison_file
from class_writer import write_header_class_file, write_source_class_file, \
    write_visitor_header_file, write_kind_header_file
from cmake_writer import write_cmake_file

regenerate_files = [

]

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='To bison grammar expander.')
    parser.add_argument('file', type=str, help='Path to the description file')
    parser.add_argument('parser_output', type=str, help='Path to the parser output files')
    parser.add_argument('ast_header_output', type=str, help='Path to the ast output include files')
    parser.add_argument('ast_source_output', type=str, help='Path to the ast output source files')
    parser.add_argument('force', type=str, help='Override existing files')

    current_file_path = os.path.abspath(__file__)
    current_dir = os.path.dirname(current_file_path)

    args = parser.parse_args()
    force = args.force == 'True'

    definitions, rules = read_description(args.file)

    # print('Definitions:')
    # for definition in definitions:
    #     print(f'{definition}: {definitions[definition]}')
    #
    # print('Rules:')
    # for rule in rules:
    #     print(f'{rule[0]}: {rule[1]}')

    literals, grammars, regexes, enums = generate_definitions(definitions, rules)

    # print('\nLiterals:')
    # for l in literals:
    #     print(f'{l}: {literals[l]}')
    #
    # print('\nGrammars:')
    # for g in grammars:
    #     print(f'{g}: {grammars[g]}')
    #
    # print('\nRegexes:')
    # for r in regexes:
    #     print(f'{r}: {regexes[r]}')
    #
    # print('\nEnums:')
    # for e in enums:
    #     print(f'{e}: {enums[e]}')

    if not os.path.exists(args.parser_output):
        os.makedirs(args.parser_output)

    if not os.path.exists(f"{args.ast_header_output}/ast"):
        os.makedirs(f"{args.ast_header_output}/ast")

    if not os.path.exists(f"{args.ast_source_output}/ast"):
        os.makedirs(f"{args.ast_source_output}/ast")

    flex_file_path = f"{args.parser_output}/{get_flex_filename(args.file)}"
    if (not os.path.exists(flex_file_path)) or force or (flex_file_path in regenerate_files):
        write_flex_file(literals, regexes, enums, get_single_line_comment_begin(definitions),
                        *get_multi_line_comment_begin_end(definitions), flex_file_path)
    else:
        print(f"File {flex_file_path} exist")

    bison_file_path = f"{args.parser_output}/{get_bison_filename(args.file)}"
    if (not os.path.exists(bison_file_path)) or force or (bison_file_path in regenerate_files):
        write_bison_file(literals, grammars, regexes, enums, rules, bison_file_path)
    else:
        print(f"File {bison_file_path} exist")

    for grammar in grammars:
        header_file_path = f"{args.ast_header_output}/ast/{get_class_filename(grammars[grammar]['class_name'], 'hpp')}"
        if (not os.path.exists(header_file_path)) or force or (header_file_path in regenerate_files):
            write_header_class_file(grammars[grammar], rules, header_file_path)
        else:
            print(f"File {header_file_path} exist")

        source_file_path = f"{args.ast_source_output}/ast/{get_class_filename(grammars[grammar]['class_name'], 'cpp')}"
        if (not os.path.exists(source_file_path)) or force or (source_file_path in regenerate_files):
            write_source_class_file(grammars[grammar], rules, source_file_path)
        else:
            print(f"File {source_file_path} exist")

    visitor_file_path = f"{args.ast_header_output}/ast/ast_visitor.hpp"
    if (not os.path.exists(visitor_file_path)) or force or (visitor_file_path in regenerate_files):
        write_visitor_header_file(rules, visitor_file_path)
    else:
        print(f"File {visitor_file_path} exist")

    kind_file_path = f"{args.ast_header_output}/ast/ast_kind.hpp"
    if (not os.path.exists(kind_file_path)) or force or (kind_file_path in regenerate_files):
        write_kind_header_file(rules, kind_file_path)
    else:
        print(f"File {kind_file_path} exist")

    os.system(f"cp {current_dir}/ast_node.hpp {args.ast_header_output}/ast")
    os.system(f"cp {current_dir}/ast_node.cpp {args.ast_source_output}/ast")

    cmake_file_path = f"{args.parser_output}/{get_cmake_filename(args.file)}"
    if (not os.path.exists(cmake_file_path)) or force or (cmake_file_path in regenerate_files):
        write_cmake_file(args.file, cmake_file_path)
    else:
        print(f"File {cmake_file_path} exist")
