from typing import Dict

flex_single_line_comment = """"{begin}".*  {{ linesCounter++; }}"""

flex_multi_line_comment_head = """"{begin}"  {{ eatComment(); }}"""
flex_multi_line_comment_body = \
    """void eatComment() {{
  int c;
  while ((c = yyinput()) != 0) {{
    if (c == '\\n') {{
      ++linesCounter;
    }}
    else if (c == '{first_comment_end_char}') {{
      if ((c = yyinput()) == '{last_comment_end_char}') {{
        break;
      }}
      unput(c);
    }}
  }}
}}"""

flex_file_template = \
    """%{{
#define NO_YY_WRAP

#include "{file_name}_parser.hpp"

#include <iostream>
#include <string>

size_t linesCounter = 1;
{multi_line_comment_fun_def}
%}}
%%

{flex_single_line_comment}        
{flex_multi_line_comment_head}

{definitions}

[ \\t\\f]  {{ }}

"\\n"  {{ linesCounter++; }}

.  {{ std::cerr << "Error:  illegal character " << yytext[0] << " at line " << linesCounter << std::endl; }}

%%
{flex_multi_line_comment_body}

int yywrap(void) {{
    return 1;
}}
"""


def write_flex_file(literals: Dict[str, str], regexes: Dict[str, str], enums: Dict[str, str],
                    single_line_co_begin: str or None, multi_line_co_begin: str or None, multi_line_co_end: str or None,
                    output_file: str):
    multi_line_comment_fun_def = "void eatComment();\n" if multi_line_co_begin else ""

    single_line_comment = flex_single_line_comment.format(begin=single_line_co_begin) if single_line_co_begin else ""

    multi_line_comment_head = flex_multi_line_comment_head.format(
        begin=multi_line_co_begin) if multi_line_co_begin else ""
    if not multi_line_co_begin:
        multi_line_comment_body = ""
    else:
        if len(multi_line_co_end) != 2:
            raise ValueError("multi_line_co_end should be a tuple of two distinct characters")
        first_comment_end_char = multi_line_co_end[0]
        last_comment_end_char = multi_line_co_end[1]
        if first_comment_end_char == last_comment_end_char:
            raise ValueError("multi_line_co_end should be a tuple of two distinct characters")
        multi_line_comment_body = flex_multi_line_comment_body.format(first_comment_end_char=first_comment_end_char,
                                                                      last_comment_end_char=last_comment_end_char)

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
                                             multi_line_comment_fun_def=multi_line_comment_fun_def,
                                             flex_single_line_comment=single_line_comment,
                                             flex_multi_line_comment_head=multi_line_comment_head,
                                             flex_multi_line_comment_body=multi_line_comment_body,
                                             definitions=definitions))
