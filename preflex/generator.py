from typing import Dict, List, Tuple

from naming import get_ast_node_name, get_enum_name, get_literal_name

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
                    grammars[rule_name]['enums'].append(get_enum_name(token))

    for definition in definitions:
        if definition == "%SingleLineCommentBegin" or definition == "%MultiLineCommentBegin" or definition == "%MultiLineCommentEnd":
            continue
        if get_token_type(definition) == "regex":
            regexes[definition] = definitions[definition]
        elif get_token_type(definition) == "enum":
            enums[get_enum_name(definition)] = definitions[definition]

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
