def get_flex_filename(input_file_name: str) -> str:
    input_file_name = input_file_name.split('/')[-1]
    if '.' in input_file_name:
        return input_file_name.split('.')[0] + '.l'
    else:
        return input_file_name + '.l'


def get_bison_filename(input_file_name: str) -> str:
    input_file_name = input_file_name.split('/')[-1]
    if '.' in input_file_name:
        return input_file_name.split('.')[0] + '.y'
    else:
        return input_file_name + '.y'


def get_class_filename(class_name: str, extension: str) -> str:
    filename = ""
    for char in class_name:
        if char.isupper():
            filename += "_"
        filename += char.lower()

    if filename[0] == "_":
        filename = filename[1:]

    return filename + "." + extension


def get_cmake_filename(input_file_name: str) -> str:
    return "CMakeLists.txt"


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


def get_enum_name(token: str) -> str:
    enum = ""
    for char in token:
        if char.isupper():
            enum += "_"
        enum += char.upper()
    return enum[1:]


def get_guard_name(class_name: str) -> str:
    return get_class_filename(class_name, 'hpp').upper().replace(".", "_")


def get_kind_name(class_name: str) -> str:
    return get_class_filename(class_name, '').upper().replace('.', '_')[:-6]
