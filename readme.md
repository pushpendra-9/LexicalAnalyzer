C Lexical Analyzer

A C-based lexical analyzer project for Compiler Design that reads a C source file, identifies lexemes, and classifies them into different token categories.

Objective

To design and implement a lexical analyzer in C that reads a C source program, scans the source code character by character, identifies lexemes, and classifies them into appropriate token categories.

Features

The analyzer supports:

* Keywords
* Identifiers
* Integer and floating-point constants
* Hexadecimal constants
* Operators
* Delimiters / separators
* String literals
* Character constants
* Single-line comments
* Multi-line comments
* Preprocessor directives
* Invalid / unknown symbols
* Line number tracking
* Token table output
* Reading input from a .c source file

Project Structure

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

Requirements

macOS

You need:

* GCC / Clang compiler
* Terminal
* VS Code (optional, but recommended)

Check whether a C compiler is installed:

gcc --version

If GCC is not available, install Apple’s Command Line Tools:

xcode-select --install

Then verify again:

gcc --version

Windows

Install MinGW-w64 or another GCC-compatible C compiler.

Check:

gcc --version

Linux

Install GCC if required.

Ubuntu/Debian:

sudo apt update
sudo apt install gcc

Verify:

gcc --version

How to Run

Step 1: Open the Project

Open the Lexical-Analyzer folder in VS Code.

The terminal should be opened at the project root:

Lexical-Analyzer/

You can verify the current location using:

pwd

Then check the project files:

ls

You should see something similar to:

input
src
README.md

Step 2: Compile the Program

From the project root, run:

gcc src/lexical_analyzer.c -o lexer

If compilation is successful, no error message will be displayed.

You should now have an executable named:

lexer

Check using:

ls

Expected structure:

Lexical-Analyzer/
├── input/
├── src/
├── lexer
└── README.md

Step 3: Run the Lexical Analyzer

Run:

./lexer

The program will display:

=============================================================
                  C LEXICAL ANALYZER
=============================================================
Enter C source file name (.c):

Enter the path of the C source file you want to analyze.

For the main test file:

input/input.c

Press Enter.

Step 4: View the Token Table

The analyzer will display a token table similar to:

--------------------------------------------------------------------------
LINE     LEXEME                         TOKEN TYPE
--------------------------------------------------------------------------
1        #include <stdio.h>             PREPROCESSOR
3        int                            KEYWORD
3        main                           IDENTIFIER
3        (                              DELIMITER
3        )                              DELIMITER
4        {                              DELIMITER
5        int                            KEYWORD
5        age                            IDENTIFIER
5        =                              OPERATOR
5        20                             CONSTANT
5        ;                              DELIMITER
6        float                          KEYWORD
6        marks                          IDENTIFIER
6        =                              OPERATOR
6        95.5f                          CONSTANT
6        ;                              DELIMITER
...

Running Different Test Files

Test Keywords

./lexer

Enter:

input/test_keywords.c

Test Operators

./lexer

Enter:

input/test_operators.c

Test Invalid Symbols

./lexer

Enter:

input/test_invalid.c

Example Input Program

input/input.c may contain:

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

Token Categories

Token Type	Examples
Keyword	int, float, if, return
Identifier	main, age, marks
Constant	10, 95.5, 0xFF
Operator	+, -, =, ==, >=, ++
Delimiter	(, ), {, }, ;, ,
String Literal	"Hello"
Character Constant	'A', '\n'
Single-Line Comment	// comment
Multi-Line Comment	/* comment */
Preprocessor	#include <stdio.h>
Invalid / Unknown	Unrecognized characters

Optional: Save Output to a File

You can redirect the terminal output to a file:

./lexer > output/token_output.txt

Then open:

output/token_output.txt

This stores the lexical analysis results in a text file.

Recompile After Making Changes

Whenever you modify lexical_analyzer.c, compile again:

gcc src/lexical_analyzer.c -o lexer

Then run:

./lexer

Clean the Compiled Program

To remove the generated executable:

rm lexer

Then compile again whenever needed:

gcc src/lexical_analyzer.c -o lexer

Complete Quick Run

For normal use, these are the only commands you need:

gcc src/lexical_analyzer.c -o lexer
./lexer

When prompted:

Enter C source file name (.c):

enter:

input/input.c

Troubleshooting

gcc: command not found

On macOS:

xcode-select --install

On Ubuntu/Debian:

sudo apt install gcc

No such file or directory

Make sure you are in the project root:

pwd

Then verify:

ls

You should see:

input
src

Use the correct source-file path:

input/input.c

Unable to open file

Check that the file actually exists:

ls input

You should see:

input.c
test_keywords.c
test_operators.c
test_invalid.c

Project Workflow

               C Source File
                     |
                     v
             Read Character
                     |
                     v
             Identify Lexeme
                     |
          +----------+----------+
          |          |          |
          v          v          v
       Keyword   Identifier   Constant
          |          |          |
          +----------+----------+
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
               Token Table
                     |
                     v
                  Output

Author

C Lexical Analyzer — Compiler Design Project

Language: C

Purpose: Educational implementation of lexical analysis
