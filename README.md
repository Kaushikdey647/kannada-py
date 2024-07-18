# Kannada Python Compiler

## ಕನ್ನಡ ಪೈಥಾನ್ ಕಂಪೈಲರ್

Welcome to the Kannada Python Compiler project! This unique compiler allows you to write Python-like code using Kannada keywords and identifiers, bringing programming closer to Kannada speakers.

### Motivation

The primary goal of this project is to make programming more accessible to Kannada speakers, especially beginners and students. By allowing the use of Kannada keywords and identifiers, we aim to reduce the language barrier in learning programming concepts. This project serves as:

1. An educational tool for teaching programming concepts in Kannada.
2. A bridge for Kannada speakers to transition into mainstream programming languages.
3. A demonstration of language localization in programming environments.

### Features

- Lexical analysis and parsing of Kannada-based Python-like syntax
- Support for basic control structures (if-else, while loops)
- Variable assignments and arithmetic operations
- Print statements for output
- Abstract Syntax Tree (AST) generation for parsed code

### Prerequisites

To build and run this compiler, you need:

- GCC (GNU Compiler Collection)
- Make

These tools are usually pre-installed on most Unix-based systems (Linux, macOS). For Windows users, consider using WSL (Windows Subsystem for Linux) or MinGW.

### Building the Compiler

1. Clone this repository:
   ```
   git clone https://github.com/yourusername/kannada-python-compiler.git
   cd kannada-python-compiler
   ```

2. Build the compiler:
   ```
   make
   ```

This will create the `kannada_compiler` executable in the `bin` directory.

### Running the Compiler

To compile a Kannada Python file:

```
make run ARGS="path/to/your/kannada_python_file.kpy"
```

Replace `path/to/your/kannada_python_file.kpy` with the actual path to your Kannada Python source file.

### Kannada Python Syntax

Here's a brief overview of the Kannada Python syntax:

- Use `ಯದಿ` for `if`
- Use `ಅನ್ಯಥಾ` for `else`
- Use `ಆಗಿರುವ` for `while`
- Use `ಮುದ್ರಿಸು` for `print`
- Use `ನಿಜ` for `True`
- Use `ಸುಳ್ಳು` for `False`
- Use `ಶೂನ್ಯ` for `None`

Example:

```
ಸಂಖ್ಯೆ = ೧೦
ಯದಿ ಸಂಖ್ಯೆ > ೫:
    ಮುದ್ರಿಸು("ಸಂಖ್ಯೆ ೫ಕ್ಕಿಂತ ದೊಡ್ಡದು")
ಅನ್ಯಥಾ:
    ಮುದ್ರಿಸು("ಸಂಖ್ಯೆ ೫ಕ್ಕಿಂತ ಚಿಕ್ಕದು ಅಥವಾ ಸಮ")
```

### Contributing

We welcome contributions to the Kannada Python Compiler project! Whether it's adding new features, improving documentation, or reporting bugs, your help is appreciated. Please feel free to submit pull requests or open issues on our GitHub repository.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Acknowledgments

- Thanks to all contributors who have helped shape this project.
- Special thanks to the Kannada-speaking community for their support and feedback.

Happy coding in Kannada! ಸಂತೋಷದ ಕೋಡಿಂಗ್!