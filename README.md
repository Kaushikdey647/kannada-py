# Kannada-Py

## ಪೈಥಾನ್ ಕಂಪೈಲರ್

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

### Project Status

The following components have been implemented and are working:

1. **Lexer (Tokenizer)**
   - Recognizes Kannada keywords, identifiers, and literals
   - Handles basic operators and punctuation
2. **Parser**
   - Constructs Abstract Syntax Tree (AST) from tokens
   - Supports basic language constructs (if-else, while loops, assignments)
3. **Abstract Syntax Tree (AST)**
   - Defines node structures for various language constructs
   - Includes utilities for creating and manipulating AST nodes
4. **Symbol Table**
   - Management of identifiers and their attributes
5. **Main Compiler Driver**
   - Coordinates lexing and parsing phases
   - Provides basic error reporting

### Components Not Yet Implemented

1. **Semantic Analyzer**
   - Type checking
   - Scope analysis
   - Error detection for semantic issues
2. **Intermediate Code Generator**
   - Translation of AST to an intermediate representation
3. **Code Optimizer**
   - Optimization passes on the intermediate representation
4. **Code Generator**
   - Generation of target machine code or bytecode
5. **Error Handler**
   - Comprehensive error reporting and recovery mechanisms
6. **Standard Library**
   - Implementation of basic I/O, math, and other standard functions in Kannada

### Roadmap
Our next steps in the development of the Kannada Python Compiler include:
1. Implementing the Semantic Analyzer to catch semantic errors and perform type checking.
2. Developing an Intermediate Code Generator to translate the AST into a lower-level representation.
3. Creating a basic Code Generator to produce executable output.
4. Expanding the language features to include functions, modules, and more complex data structures.
5. Developing a standard library with common functions and utilities accessible in Kannada.

We welcome contributions in any of these areas! Check our issues page for specific tasks or propose new features.

### Contributing

We welcome contributions to the Kannada Python Compiler project! Whether it's adding new features, improving documentation, or reporting bugs, your help is appreciated. Please feel free to submit pull requests or open issues on our GitHub repository.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Acknowledgments

- Thanks to all contributors who have helped shape this project. Especially, ME... Kaushik Dey!
- Special thanks to the Kannada-speaking community for their support and feedback.

Happy coding in Kannada! ಸಂತೋಷದ ಕೋಡಿಂಗ್!
