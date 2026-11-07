# C Lexical Analyzer

A **C-based lexical analyzer** developed as a **Compiler Design** project. The program reads a C source file, scans it character by character, identifies lexemes, and classifies them into different token categories.

---

## Table of Contents

- [Overview](#overview)
- [Objective](#objective)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
  - [macOS](#macos)
  - [Windows](#windows)
  - [Linux](#linux)
- [How to Run](#how-to-run)
- [Running Different Test Files](#running-different-test-files)
- [Example Input Program](#example-input-program)
- [Token Categories](#token-categories)
- [Save Output to a File](#save-output-to-a-file)
- [Recompile After Changes](#recompile-after-changes)
- [Clean the Compiled Program](#clean-the-compiled-program)
- [Quick Run](#quick-run)
- [Troubleshooting](#troubleshooting)
- [Project Workflow](#project-workflow)
- [Author](#author)

---

## Overview

Lexical analysis is the first phase of a compiler. It converts a source program into a sequence of **tokens** by identifying meaningful lexemes such as keywords, identifiers, constants, operators, and delimiters.

This project implements a simplified lexical analyzer for the **C programming language**.

The analyzer reads a `.c` source file and generates a token table containing:

- Line number
- Lexeme
- Token type

---

## Objective

> To design and implement a lexical analyzer in C that reads a C source program, scans the source code character by character, identifies lexemes, and classifies them into appropriate token categories.

---

## Features

The lexical analyzer supports the following:

- **Keywords**
- **Identifiers**
- **Integer constants**
- **Floating-point constants**
- **Hexadecimal constants**
- **Operators**
- **Delimiters / separators**
- **String literals**
- **Character constants**
- **Single-line comments**
- **Multi-line comments**
- **Preprocessor directives**
- **Invalid / unknown symbols**
- **Line number tracking**
- **Token table generation**
- **Input from `.c` source files**

---

## Project Structure

```text
Lexical-Analyzer/
│
├── src/
│   └── lexical_analyzer.c
│
├── input/
│   ├── input.c
│   ├── test_keywords.c
│   ├── test_operators.c
│   └── test_invalid.c
│
├── output/
│   └── token_output.txt
│
├── docs/
│   └── Project_Report.pdf
│
└── README.md
```

### Directory Description

| Directory / File | Description |
|---|---|
| `src/` | Contains the lexical analyzer source code |
| `src/lexical_analyzer.c` | Main C implementation |
| `input/` | C source files used for testing |
| `input/input.c` | Main demonstration input |
| `input/test_keywords.c` | Keyword test cases |
| `input/test_operators.c` | Operator test cases |
| `input/test_invalid.c` | Invalid-symbol test cases |
| `output/` | Stores generated output files |
| `docs/` | Project documentation |
| `README.md` | Project documentation and usage instructions |

---

# Requirements

## macOS

You need:

- GCC / Clang compiler
- Terminal
- VS Code *(optional but recommended)*

### Check whether a C compiler is installed

```bash
gcc --version
```

macOS may use Clang behind the `gcc` command.

### If a compiler is not available

Install Apple's Command Line Tools:

```bash
xcode-select --install
```

Then verify:

```bash
gcc --version
```

---

## Windows

Install **MinGW-w64** or another GCC-compatible C compiler.

Verify the installation:

```bash
gcc --version
```

---

## Linux

Install GCC if required.

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install gcc
```

Verify:

```bash
gcc --version
```

---

# How to Run

## Step 1 — Open the Project

Open the `Lexical-Analyzer` folder in VS Code.

The terminal should be opened at the **project root**:

```text
Lexical-Analyzer/
```

### Check the current directory

```bash
pwd
```

### Check the project files

```bash
ls
```

You should see something similar to:

```text
input
src
README.md
```

---

## Step 2 — Compile the Program

From the project root, run:

```bash
gcc src/lexical_analyzer.c -o lexer
```

If compilation is successful, no error message should appear.

This creates an executable named:

```text
lexer
```

Check the project directory:

```bash
ls
```

Expected structure:

```text
Lexical-Analyzer/
├── input/
├── src/
├── lexer
└── README.md
```

> **Note:** `lexer` is a compiled executable and should normally be excluded from Git using `.gitignore`.

---

## Step 3 — Run the Lexical Analyzer

Run:

```bash
./lexer
```

The program will display:

```text
=============================================================
                  C LEXICAL ANALYZER
=============================================================

Enter C source file name (.c):
```

Enter the path of the C source file you want to analyze.

For the main test file:

```text
input/input.c
```

Press **Enter**.

---

## Step 4 — View the Token Table

The analyzer displays a token table similar to:

```text
--------------------------------------------------------------------------
LINE     LEXEME                         TOKEN TYPE
--------------------------------------------------------------------------
1        #include <stdio.h>             PREPROCESSOR
3        int                             KEYWORD
3        main                            IDENTIFIER
3        (                               DELIMITER
3        )                               DELIMITER
4        {                               DELIMITER
5        int                             KEYWORD
5        age                             IDENTIFIER
5        =                               OPERATOR
5        20                              CONSTANT
5        ;                               DELIMITER
6        float                           KEYWORD
6        marks                           IDENTIFIER
6        =                               OPERATOR
6        95.5f                           CONSTANT
6        ;                               DELIMITER
...
```

Each token contains:

```text
LINE NUMBER
     +
  LEXEME
     +
TOKEN TYPE
```

---

# Running Different Test Files

## Test Keywords

Run:

```bash
./lexer
```

Enter:

```text
input/test_keywords.c
```

---

## Test Operators

Run:

```bash
./lexer
```

Enter:

```text
input/test_operators.c
```

---

## Test Invalid Symbols

Run:

```bash
./lexer
```

Enter:

```text
input/test_invalid.c
```

---

# Example Input Program

The main test program `input/input.c` may contain:

```c
#include <stdio.h>

int main()
{
    int age = 20;
    float marks = 95.5f;
    char grade = 'A';

    // Calculate result
    age = age + 5;

    /*
       This is a
       multi-line comment
    */

    if (marks >= 50.0)
    {
        printf("Age = %d\n", age);
        printf("Grade = %c\n", grade);
    }

    return 0;
}
```

This example demonstrates:

- Preprocessor directive
- Keywords
- Identifiers
- Integer constant
- Floating-point constant
- Character constant
- Operators
- Delimiters
- String literals
- Single-line comments
- Multi-line comments

---

# Token Categories

| Token Type | Examples |
|---|---|
| **Keyword** | `int`, `float`, `if`, `return` |
| **Identifier** | `main`, `age`, `marks` |
| **Constant** | `10`, `95.5`, `0xFF` |
| **Operator** | `+`, `-`, `=`, `==`, `>=`, `++` |
| **Delimiter** | `(`, `)`, `{`, `}`, `;`, `,` |
| **String Literal** | `"Hello"` |
| **Character Constant** | `'A'`, `'\n'` |
| **Single-Line Comment** | `// comment` |
| **Multi-Line Comment** | `/* comment */` |
| **Preprocessor** | `#include <stdio.h>` |
| **Invalid / Unknown** | Unrecognized characters |

---

# Save Output to a File

The program output can be redirected from the terminal to a text file.

Run:

```bash
./lexer > output/token_output.txt
```

The generated file will be:

```text
output/token_output.txt
```

You can then open it using VS Code or any text editor.

### Important

When using output redirection, the program's prompt and token table are also redirected to the file.

---

# Recompile After Changes

Whenever you modify:

```text
src/lexical_analyzer.c
```

compile the program again:

```bash
gcc src/lexical_analyzer.c -o lexer
```

Then run:

```bash
./lexer
```

---

# Clean the Compiled Program

To remove the compiled executable:

```bash
rm lexer
```

Then compile again when needed:

```bash
gcc src/lexical_analyzer.c -o lexer
```

---

# Quick Run

For normal use, the complete process is:

```bash
gcc src/lexical_analyzer.c -o lexer
./lexer
```

When prompted:

```text
Enter C source file name (.c):
```

enter:

```text
input/input.c
```

That's all that is required for a normal run.

---

# Troubleshooting

## `gcc: command not found`

### macOS

Install Apple's Command Line Tools:

```bash
xcode-select --install
```

Then:

```bash
gcc --version
```

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install gcc
```

Then:

```bash
gcc --version
```

---

## `No such file or directory`

Make sure you are inside the project root.

Check:

```bash
pwd
```

Then:

```bash
ls
```

You should see:

```text
input
src
README.md
```

Use the correct source-file path:

```text
input/input.c
```

---

## `Unable to open file`

Check whether the input files exist:

```bash
ls input
```

You should see:

```text
input.c
test_keywords.c
test_operators.c
test_invalid.c
```

If the file is located somewhere else, provide its correct path when the analyzer asks for the filename.

---

## Permission Denied on `./lexer`

On macOS/Linux, try:

```bash
chmod +x lexer
```

Then:

```bash
./lexer
```

---

# Project Workflow

The lexical analysis process implemented by this project can be represented as:

```text
                    C SOURCE FILE
                           |
                           v
                  +----------------+
                  | Read Character |
                  +----------------+
                           |
                           v
                  +----------------+
                  | Identify       |
                  | Lexeme         |
                  +----------------+
                           |
                           v
              +------------+------------+
              |            |            |
              v            v            v
          Keyword      Identifier    Constant
              |            |            |
              +------------+------------+
                           |
                           v
                       Operators
                           |
                           v
                      Delimiters
                           |
                           v
                  Strings / Characters
                           |
                           v
                       Comments
                           |
                           v
                 Invalid Characters
                           |
                           v
                    +-------------+
                    | Token Table |
                    +-------------+
                           |
                           v
                        OUTPUT
```

---

# Tokenization Flow

The analyzer broadly follows this process:

```text
Input C Program
      |
      v
Read character
      |
      v
Is it whitespace?
   /        \
 Yes         No
  |           |
Skip          v
        Identify character
              |
     +--------+--------+
     |        |        |
     v        v        v
  Letter    Digit   Special Symbol
     |        |        |
     v        v        v
Keyword   Constant   Operator /
or ID                Delimiter /
                     String /
                     Comment
              |
              v
          Token Table
```

---

# Example

Given the following source code:

```c
int x = 10;
```

The lexical analyzer produces:

| Line | Lexeme | Token Type |
|---:|---|---|
| 1 | `int` | KEYWORD |
| 1 | `x` | IDENTIFIER |
| 1 | `=` | OPERATOR |
| 1 | `10` | CONSTANT |
| 1 | `;` | DELIMITER |

---

# Educational Purpose

This project demonstrates the fundamental concepts of **lexical analysis**, including:

1. Reading source code character by character
2. Recognizing lexemes
3. Classifying lexemes into tokens
4. Tracking source-code line numbers
5. Handling comments and literals
6. Detecting invalid symbols
7. Generating a structured token table

It is intended for educational use in **Compiler Design / Compiler Construction** coursework.

---

# Author

**C Lexical Analyzer — Compiler Design Project**

**Language:** C

**Purpose:** Educational implementation of lexical analysis.
