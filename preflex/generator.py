from typing import Dict, List, Tuple


def special_split(string: str) -> List[str]:
    tokens = []
    in_quotes = False
    current_token = ""
    for char in string:
        if char == "\"":
            in_quotes = not in_quotes
        elif char == " " and not in_quotes:
            if current_token:
                tokens.append(current_token)
                current_token = ""
            continue
        current_token += char
    if current_token:
        tokens.append(current_token)
    return tokens


def get_token_type(token: str) -> str:
    if token[0] == "\"" and token[-1] == "\"":
        return "literal"
    elif token.islower():
        return "grammar"
    elif token.isupper():
        return "regex"
    else:
        return "enum"


def get_ast_node_name(token: str) -> str:
    class_name = ""
    make_upper = True
    for char in token:
        if char == "-" or char == "_":
            make_upper = True
        elif make_upper:
            class_name += char.upper()
            make_upper = False
        else:
            class_name += char

    return class_name + 'Node'


def get_literal_name(token: str) -> str:
    return 'LITERAL_' + token.replace('\"', '').upper().replace(' ', '_')


def generate_definitions(definitions: Dict[str, str], rules: List[Tuple[str, List[str]]]) -> Tuple[
    Dict[str, str], Dict[str, Dict[str, List[str] or str]], Dict[str, str], Dict[str, str]]:
    literals = {}
    grammars = {}
    regexes = {}
    enums = {}

    for rule in rules:
        rule_name, rule_tokens = rule
        for tokens in [rule_name, *rule_tokens]:
            for token in special_split(tokens):
                if get_token_type(token) == "grammar":
                    grammars[token] = {'class_name': get_ast_node_name(token), 'enums': []}
                elif get_token_type(token) == "literal":
                    literals[token] = get_literal_name(token)

    for rule in rules:
        rule_name, rule_tokens = rule
        for tokens in [rule_name, *rule_tokens]:
            for token in special_split(tokens):
                if get_token_type(token) == "enum":
                    grammars[rule_name]['enums'].append('TOKEN_' + token.upper())

    for definition in definitions:
        if definition == "%SingleLineCommentBegin" or definition == "%MultiLineCommentBegin" or definition == "%MultiLineCommentEnd":
            continue
        if get_token_type(definition) == "regex":
            regexes[definition] = definitions[definition]
        elif get_token_type(definition) == "enum":
            enums['TOKEN_' + definition.upper()] = definitions[definition]

    return literals, grammars, regexes, enums


def get_single_line_comment_begin(definitions: Dict[str, str]) -> str or None:
    if '%SingleLineCommentBegin' in definitions:
        return definitions['%SingleLineCommentBegin']
    else:
        return None


def get_multi_line_comment_begin_end(definitions: Dict[str, str]) -> Tuple[str, str] or None:
    if '%MultiLineCommentBegin' in definitions and '%MultiLineCommentEnd' in definitions:
        return definitions['%MultiLineCommentBegin'], definitions['%MultiLineCommentEnd']
    else:
        return None, None
