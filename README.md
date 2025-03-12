# Expression Evaluator @ C++

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

A CLI tool that evaluates mathematical expressions. \
Class project for the course **Programming Languages - Q1-2025** at [**Universidad Tecnológica Centroamericana (UNITEC)**](https://unitec.edu).

This project was made to learn how to implement a tokenizer, parser and the mathematical expression evaluator. \
The project is written in C++ and uses the C++23 standard.

## ⚙️ Usage

```bash
$ ./operate <expression>
```

### Supported Operations

The expression evaluator supports the following operations:

- Addition `+`
- Subtraction `-`
- Multiplication `*`
- Division `/`
- Modulus `%`
- Exponentiation `^`
- Parentheses `()`

> [!IMPORTANT]
> The expression evaluator does not support unary operations. \
> Example: `-1 + 3` is not supported.

> [!IMPORTANT]
> Multiplications with joint terms are not supported. \
> Example: `2x` is not supported.

## 🔨 Installation

**Pre-requisites:**

- Catch2
- CMake
- A C++ compiler with C++23 support

1. Clone the repository:

```bash
# Clone with SSH or HTTPS
$ git clone git@github.com:fer-hnndz/cpp-expression-evaluator.git
```

2. Make a `build` directory and build the project with `CMake`:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

3. Run the CLI tool:

```bash
$ ./operate <expression>
```

> [!NOTE]
> You can optionally pass the `--debug` tag to the CLI tool to enable printing the expression in postfix notation. \
> This was a requirement of the project, but it is not necessary for the evaluation of the expression.
