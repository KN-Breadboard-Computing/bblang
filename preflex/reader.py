from typing import Dict, List, Tuple
import re


def load_definitions(file_content: str) -> Dict[str, str]:
    file_content_tokenized = [token.strip() for token in file_content.split('\n')]

    definitions = {}
    for token in file_content_tokenized:
        split_token = token.split()
        if len(split_token) == 2:
            def_name, def_desc = split_token
            definitions[def_name] = def_desc

    return definitions


def load_rules(file_content: str) -> List[Tuple[str, List[str]]]:
    pattern = r"(\w[\w-]*):\s*((?:.*?\n?)*?);"
    matches = re.findall(pattern, file_content)

    rules = [(match[0], [s.strip() for s in match[1].strip().split('|')]) for match in matches]

    return rules


def read_description(grammar_definition_file: str) -> Tuple[Dict[str, str], List[Tuple[str, List[str]]]]:
    with open(grammar_definition_file, 'r') as file:
        file_content = file.read()

    first_part, second_part = file_content.split('%%')

    definitions = load_definitions(first_part.strip())
    rules = load_rules(second_part.strip())

    return definitions, rules
