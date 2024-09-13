from typing import Dict, List, Tuple

from generator import special_split, get_ast_node_name, get_token_type

class_header_file_template = \
    """#ifndef AST_{guard}
#define AST_{guard}

#include "ast_node.hpp"
#include "ast_visitor.hpp"
{headers}

namespace ast {{
class {class_name} : public AstNode {{
 public:
  {enums}
    
  {class_name}() = default;
    
{constructors}
  {class_name}(const {class_name}&) = delete;
  {class_name}({class_name}&&) = default;
    
  {class_name}& operator=(const {class_name}&) = delete;
  {class_name}& operator=({class_name}&&) = default;
    
  ~{class_name}() = default;
  
{getters}
  void accept(class AstVisitor* visitor) const override {{ visitor->visit(this); }}
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
  
 private:
{fields}
}};
}}  // namespace ast

#endif  // AST_{guard}
"""

class_source_file_template = \
    """#include "../../include/ast/{file_class_name}"
    
namespace ast {{
{enum_print}
[[nodiscard]] std::unique_ptr<AstNode> {class_name}::clone() const {{
{clone_args_preparation}
  return std::make_unique<{class_name}>({clone_args});
}}
    
void {class_name}::print(std::ostream& out, int tab) const {{
  out << std::string(tab, ' ') << "{class_name}" << std::endl;
{print_instructions}
}}
}} // namespace ast
"""

visitor_header_file_template = \
    """#ifndef AST_VISITOR_HPP
#define AST_VISITOR_HPP

namespace ast {{
{class_declarations}
class AstVisitor {{
 public:
  AstVisitor() = default;
    
  AstVisitor(const AstVisitor&) = default;
  AstVisitor(AstVisitor&&) = default;
    
  AstVisitor& operator=(const AstVisitor&) = default;
  AstVisitor& operator=(AstVisitor&&) = default;
    
  virtual ~AstVisitor() = default;
    
{visits}
}};
}}  // namespace ast

#endif  // AST_VISITOR_HPP
"""

def get_class_filename(class_name: str, extension: str) -> str:
    filename = ""
    for char in class_name:
        if char.isupper():
            filename += "_"
        filename += char.lower()

    if filename[0] == "_":
        filename = filename[1:]

    return filename + "." + extension


def get_guard(class_name: str) -> str:
    return get_class_filename(class_name, 'hpp').upper().replace(".", "_")


def generate_constructor_args_and_headers(class_name: str, rules: List[Tuple[str, List[str]]]) -> Tuple[
    List[List[str]], List[str]]:
    constructor_args = []
    headers_set = set()
    for rule in rules:
        rule_name, rule_parts = rule
        rule_name = get_ast_node_name(rule_name)
        for rule_part in rule_parts:
            parts = [p for p in special_split(rule_part) if get_token_type(p) != "literal"]
            if len(parts) == 0 or rule_name != class_name:
                continue

            counter = {}
            enums_counter = 0
            for p in parts:
                p_type = get_token_type(p)
                if p_type == "grammar" or p_type == "regex":
                    if parts.count(p) > 1:
                        counter[p] = 1
                elif p_type == "enum":
                    enums_counter += 1

            if enums_counter > 1:
                counter["enum"] = 1

            args = []
            for p in parts:
                p_type = get_token_type(p)
                if p_type == "grammar" or p_type == "regex":
                    p_name = p.lower()
                    if p in counter:
                        p_name = f"{p}{counter[p]}"
                        counter[p] += 1
                    args.append(f"{get_ast_node_name(p.lower())}* {p_name}")
                    headers_set.add(get_ast_node_name(p.lower()))
                elif p_type == "enum":
                    p_name = "operation"
                    if "enum" in counter:
                        p_name = f"operation{counter['enum']}"
                        counter['enum'] += 1
                    args.append(f"{rule_name}Operation {p_name}")

            constructor_args.append(args)

    if class_name in headers_set:
        headers_set.remove(class_name)

    return constructor_args, list(headers_set)

def get_all_class_names(rules: List[Tuple[str, List[str]]]) -> List[str]:
    class_names = []
    for rule in rules:
        rule_name, rule_parts = rule
        rule_name = get_ast_node_name(rule_name)
        class_names.append(rule_name)
        for rule_part in rule_parts:
            parts = [p for p in special_split(rule_part) if get_token_type(p) != "literal"]
            for p in parts:
                p_type = get_token_type(p)
                if p_type == "grammar" or p_type == "regex":
                    class_names.append(get_ast_node_name(p.lower()))

    return list(set(class_names))

def generate_headers_enums_fields_getters_and_constructors(class_data: Dict[str, List[str] or str],
                                                           rules: List[Tuple[str, List[str]]]) -> Tuple[
    str, str, str, str, str]:
    class_name = class_data['class_name']

    class_enums = [cde.replace('TOKEN_', '') for cde in class_data['enums']]
    if len(class_enums) > 0:
        enums = f"enum class {class_name}Operation {{ {', '.join(['UNDEF'] + list(set(class_enums)))} }};"
    else:
        enums = ""

    constructor_args, headers = generate_constructor_args_and_headers(class_name, rules)

    unique_constructor_args = []
    for ca in constructor_args:
        if ca not in unique_constructor_args:
            unique_constructor_args.append(ca)

    constructor_args = sorted(unique_constructor_args, key=lambda x: len(x), reverse=True)

    constructors = ""
    for ca_index, ca in enumerate(constructor_args):
        constructors += f"  {class_name}({', '.join(ca)}):\n"
        for na_index, na in enumerate(ca):
            constructors += f"    {na.split()[1]}_{{{na.split()[1]}}}"
            if na_index == len(ca) - 1:
                constructors += "{}\n"
            else:
                constructors += ",\n"

        if ca_index != len(constructor_args) - 1:
            constructors += "\n"

    fields = ""
    getters = ""
    for index, ca in enumerate(constructor_args[0]):
        type, name = ca.split()
        if '*' in type:
            fields += f"  std::unique_ptr<{type.replace('*', '')}> {name}_;"
            getters += f"  const std::unique_ptr<{type.replace('*', '')}>& get{name.title().replace('_','')}() const {{ return {name}_; }}\n"
        else:
            fields += f"  {type} {name}_;"
            getters += f"  {type} get{name.title()}() const {{ return {name}_; }}\n"
        if index != len(constructor_args[0]) - 1:
            fields += "\n"

    headers = "\n".join([f"#include \"{get_class_filename(header, 'hpp')}\"" for header in headers])

    return headers, enums, fields, getters, constructors


def generate_clone_print_enum_instructions(class_data: Dict[str, List[str] or str],
                                           rules: List[Tuple[str, List[str]]]) -> Tuple[str, str, str, str]:
    class_name = class_data['class_name']
    class_enums = [cde.replace('TOKEN_', '') for cde in class_data['enums']]

    constructor_args, _ = generate_constructor_args_and_headers(class_name, rules)

    clone_args_preparation = ""
    clone_args = []
    print_instructions = ""
    for ca in constructor_args[0]:
        ca_type, ca_name = ca.split()
        if ca_type.endswith('Operation'):
            clone_args.append(f"{ca_name}_")
            print_instructions += f"  out << std::string(tab, ' ') << \"{ca_type}: \" << {ca_name}_ << std::endl;\n"
        else:
            clone_args_preparation += f"  {ca_type} new_{ca_name} = {ca_name}_ ? dynamic_cast<{ca_type}>({ca_name}_->clone().release()) : nullptr;\n"
            clone_args.append(f"std::move(new_{ca_name})")
            print_instructions += f"  if ({ca_name}_) {{\n"
            print_instructions += f"    {ca_name}_->print(out, tab + 2);\n"
            print_instructions += f"  }}\n"
            print_instructions += f"  else {{\n"
            print_instructions += f"    out << std::string(tab + 2, ' ') << \"nullptr\" << std::endl;\n"
            print_instructions += f"  }}\n"

    enum_print = ""
    if len(class_enums) > 0:
        enum_print += f"std::ostream& operator<<(std::ostream& os, {class_name}::{class_name}Operation name) {{\n"
        enum_print += f"  switch (name) {{\n"
        for e in ['UNDEF'] + list(set(class_enums)):
            enum_print += f"    case {class_name}::{class_name}Operation::{e}:\n"
            enum_print += f"      os << \"{e}\";\n"
            enum_print += f"      break;\n"
        enum_print += f"  }}\n"
        enum_print += f"  return os;\n"
        enum_print += f"}}\n"

    return clone_args_preparation, ", ".join(clone_args), print_instructions, enum_print


def write_header_class_file(class_data: Dict[str, List[str] or str], rules: List[Tuple[str, List[str]]],
                            output_file: str) -> None:
    headers, enums, fields, getters, constructors = generate_headers_enums_fields_getters_and_constructors(class_data,
                                                                                                           rules)
    with open(output_file, 'w') as file:
        file.write(
            class_header_file_template.format(class_name=class_data['class_name'],
                                              headers=headers,
                                              guard=get_guard(class_data['class_name']),
                                              enums=enums, constructors=constructors,
                                              getters=getters, fields=fields))


def write_source_class_file(class_data: Dict[str, List[str] or str], rules: List[Tuple[str, List[str]]],
                            output_file: str) -> None:
    clone_args_preparation, clone_args, print_instructions, enum_print = generate_clone_print_enum_instructions(
        class_data, rules)
    with open(output_file, 'w') as file:
        file.write(class_source_file_template.format(class_name=class_data['class_name'],
                                                     file_class_name=get_class_filename(class_data['class_name'], 'hpp'),
                                                     enum_print=enum_print,
                                                     clone_args_preparation=clone_args_preparation,
                                                     clone_args=clone_args,
                                                     print_instructions=print_instructions))

def write_visitor_header_file(rules: List[Tuple[str, List[str]]], output_file: str) -> None:
    class_names = get_all_class_names(rules)
    class_declarations = ""
    visits = ""
    for class_name in class_names:
        class_declarations += f"class {class_name};\n"
        visits += f"  virtual void visit(const ast::{class_name}*) = 0;\n"
    with open(output_file, 'w') as file:
        file.write(visitor_header_file_template.format(visits=visits,
                                                       class_declarations=class_declarations))