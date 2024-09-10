## Preflex

**Preflex** is a tool for generating **flex** and **bison** files for generating **grammar parser**.
 based on custom-defined grammar rules. This tool allows for fast and efficient code generation, enabling you to focus on your project without getting bogged down by syntax parsing details.
Result of parsing is **abstract syntax trees (AST)**, which can be used for further processing. Target language is **C++**.

---

## Features
- **Automated parser generation** from custom grammar.
- **AST generation** for further processing.
- **Visitor** for AST traversal.
- **Bison-like syntax** for defining grammar rules.
- Supports **single-line and multi-line comments**.
- Fast code generation that allows for easy post-generation validation and correction.

---

## Workflow
1. **Define** your grammar description.
2. **Generate** the code.
3. **Check**, **validate**, and **correct** the generated code as necessary.
4. **Enjoy** working with fast, efficiently generated parser code.

---

## Grammar Description

### Identifiers
- **Lowercase identifiers** with underscores (`_`) are automatically converted into AST node classes.
- **Uppercase identifiers** must be declared as regular expressions (regex) before the `%%` marker on separate lines.
- **Char sequences in double quotes** (`"example"`) are treated as literals and will not be used in class creation.
- **Other identifiers** are transformed into an enum of rule classes. Like uppercase identifiers, these must also be defined as regex before the `%%` marker.

### Defining Grammar Rules
Grammar rules are defined after the `%%` marker in a **Bison-like** format. Don’t specify the body of the rules; just define the structure.

### Comments
- Use `%SingleLineCommentBegin` to define the beginning of a single-line comment.
- Use `%MultiLineCommentBegin` and `%MultiLineCommentEnd` markers to define the style for multi-line comments.

### Note
You need to define the classes representing your regex patterns in the generated code.

---

### Usage
To use Preflex, follow these steps:
```shell
clone preflex
python preflex/parser.py <grammar description> <parser target directory> <ast headers directory> <ast sources directory> <force overwrite>
```

---

## Example 
For a basic example of how to use Preflex to create to LLVM IR translator, check out the `example-sketch` and `example-result` branches of this repository. 
Branch `example-sketch` contains a simple grammar description before Preflex code generation, 
while branch `example-result` contains the generated and corrected code with to LLVM IR translator.
