from typing import Dict

flex_single_line_comment = """"{begin}".*  {{ linesCounter++; }}"""

flex_multi_line_comment_state = "\n%x COMMENT\n"

flex_file_template = \
    """%{{
#define NO_YY_WRAP
#define YY_NO_UNPUT
#define YY_NO_INPUT

#include "{file_name}_parser.hpp"

#include <iostream>
#include <string>

size_t linesCounter = 1;
%}}
{multi_line_comment_state}
%%

{flex_single_line_comment}        
{flex_multi_line_comment}

{definitions}

[ \\t\\f]  {{ }}

"\\n"  {{ linesCounter++; }}

.  {{ std::cerr << "Error:  illegal character " << yytext[0] << " at line " << linesCounter << std::endl; }}

%%

int yywrap(void) {{
    return 1;
}}
"""


def get_flex_filename(input_file_name: str) -> str:
    input_file_name = input_file_name.split('/')[-1]
    if '.' in input_file_name:
        return input_file_name.split('.')[0] + '.l'
    else:
        return input_file_name + '.l'


def write_flex_file(literals: Dict[str, str], regexes: Dict[str, str], enums: Dict[str, str],
                    single_line_co_begin: str or None, multi_line_co_begin: str or None, multi_line_co_end: str or None,
                    output_file: str):
    single_line_comment = flex_single_line_comment.format(begin=single_line_co_begin) if single_line_co_begin else ""

    literals_and_enums = sorted(
        [pair for pair in literals.items()] + [[f"\"{pair[1]}\"", pair[0]] for pair in enums.items()],
        key=lambda x: x[0], reverse=True)

    definitions = ""
    for literal in literals_and_enums:
        definitions += f'{literal[0]}  {{ return {literal[1]}; }}\n'
    definitions += '\n'
    for regex in regexes:
        definitions += f'{regexes[regex]}  {{ return {regex}; }}\n'

    with open(output_file, 'w') as file:
        file.write(flex_file_template.format(file_name=output_file.split('/')[-1].replace('.l', ''),
                                             multi_line_comment_state="",
                                             flex_single_line_comment=single_line_comment,
                                             flex_multi_line_comment="",
                                             definitions=definitions))
