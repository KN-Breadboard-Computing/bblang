from typing import Dict, List, Tuple
from generator import get_token_type, get_ast_node_name, special_split
from class_writer import get_class_filename

bison_file_template = \
    """%{{
    #include <iostream>
    #include <cstdlib>
    #include <cstdio>

{ast_includes}
    static void yyerror(const char *msg);
    static int yyparse(void);

    int yylex(void);
    
    extern FILE* yyin;
    extern size_t linesCounter;
    std::unique_ptr<ast::ProgramNode> result = nullptr;
%}}

%code requires {{
    #include <iostream>
    
{ast_includes}
    typedef struct Token {{
        std::string* stringValue;
    }} Token;
}}

%union
{{
    Token token;
    {union_fields}
}}

{tokens}
{types}

%%

{generation}
%%

void yyerror(const char *s) {{
    std::cerr << "Error: " << s << std::endl;
}}

std::unique_ptr<ast::ProgramNode> parse(const char* file_path) {{
    yyin = fopen(file_path, "r");
    if (!yyin) {{
        std::cerr << "Cannot open file: " << file_path << std::endl;
        return nullptr;
    }}

    yyparse();
    fclose(yyin);
    
    return std::move(result);
}}
"""


def get_bison_filename(input_file_name: str) -> str:
    input_file_name = input_file_name.split('/')[-1]
    if '.' in input_file_name:
        return input_file_name.split('.')[0] + '.y'
    else:
        return input_file_name + '.y'


def translate_rule(rule: str, literals: Dict[str, str]) -> str:
    translated_tokens = []
    for token in special_split(rule):
        token_type = get_token_type(token)
        if token_type == "literal":
            translated_tokens.append(literals[token])
        elif token_type == "enum":
            translated_tokens.append("TOKEN_" + token.upper())
        else:
            translated_tokens.append(token)

    return " ".join(translated_tokens)


def generate_stack_assignment(target_rule, rule: str) -> str:
    arguments = []
    for index, token in enumerate(special_split(rule)):
        token_type = get_token_type(token)
        if token_type == "literal":
            continue
        elif token_type == "grammar":
            arguments.append(f"${index + 1}")
        elif token_type == "regex":
            arguments.append(f"new ast::{get_ast_node_name(token.lower())}(${index + 1})")
        elif token_type == "enum":
            arguments.append(f"ast::{get_ast_node_name(target_rule)}::{get_ast_node_name(target_rule)}Operation::{token.upper()}")

    return f"$$ = new ast::{get_ast_node_name(target_rule)}({', '.join(arguments)});"


def write_bison_file(literals: Dict[str, str], grammars: Dict[str, Dict[str, List[str] or str]], regexes: Dict[str, str],
                     enums: Dict[str, str], rules: List[Tuple[str, List[str]]], output_file: str):
    ast_includes = ""
    tokens = ""
    types = ""
    union_fields = ""
    generation = ""

    if len(enums) > 0:
        tokens += "\n%token"
        types += "\n%type <token>"
        for enum in enums:
            tokens += f" {enum}"
            types += f" {enum}"

    if len(literals) > 0:
        tokens += "\n%token"
        types += "\n%type <token>"
        for literal in literals:
            tokens += f" {literals[literal]}"
            types += f" {literals[literal]}"

    if len(regexes) > 0:
        tokens += "\n%token"
        types += "\n%type <token>"
        for regex in regexes:
            tokens += f" {regex}"
            types += f" {regex}"

    types += "\n"
    for grammar in grammars:
        grammar_camel = grammars[grammar]['class_name']
        grammar_camel = grammar_camel[0].lower() + grammar_camel[1:]
        grammar_camel2 = ""
        make_upper = False
        for char in grammar_camel:
            if char == '_':
                make_upper = True
            elif make_upper:
                grammar_camel2 += char.upper()
                make_upper = False
            else:
                grammar_camel2 += char
        grammar_camel = grammar_camel2

        types += f"\n%type <{grammar_camel}> {grammar}"
        union_fields += f"\n\tast::{grammars[grammar]['class_name']}* {grammar_camel};"
        ast_includes += f"    #include \"../../include/ast/{get_class_filename(grammar + 'Node', 'hpp')}\"\n"

    for regex in regexes:
        ast_includes += f"    #include \"../../include/ast/{get_class_filename(regex.lower() + 'Node', 'hpp')}\"\n"

    for rule_num, rule in enumerate(rules):
        rule_name, rule_options = rule
        generation += f"{rule_name}:\n"
        for index, rule_option in enumerate(rule_options):
            if index != 0:
                generation += f'|\n'
            if rule_option == '':
                generation += f"\t%empty {{\n"
            else:
                generation += f"\t{translate_rule(rule_option, literals)} {{\n"
            if rule_num == 0:
                save_result = f"\n\t\tresult = std::unique_ptr<ast::{get_ast_node_name(rule_name)}>($$);"
                generation += f"\t\t{generate_stack_assignment(rule_name, rule_option) + save_result}\n\t}}\n"
            else:
                generation += f"\t\t{generate_stack_assignment(rule_name, rule_option)}\n\t}}\n"
        generation += ";\n\n"

    with open(output_file, 'w') as file:
        file.write(
            bison_file_template.format(ast_includes=ast_includes, tokens=tokens, types=types, union_fields=union_fields,
                                       generation=generation))
