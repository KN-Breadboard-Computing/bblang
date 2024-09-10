## bblang

**bblang** is a simple programming language that is designed to be easy to learn and use. It is a high-level language
that is designed to be easy to read and write. It is a statically typed language that is designed to be easy to
understand and use. It is a compiled language.
Project is written using **C++**, **flex**, **bison** and **LLVM**.

To generate parser more easily, **Preflex** is used. More information about **Preflex** can be in
subdirectory `preflex`.

---

## Features

---

## Workflow

### Necessary tools
- python3
- C++ compiler
- flex
- bison
- LLVM
- cmake

### Build
```shell
mkdir build
cd build
cmake ..
make
```

### Run
```shell
./bblang <source file> <output file>
```