#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEXEME 256

/* ============================================================
   C KEYWORDS
   ============================================================ */

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while",
    "_Alignas", "_Alignof", "_Atomic", "_Bool",
    "_Complex", "_Generic", "_Imaginary", "_Noreturn",
    "_Static_assert", "_Thread_local"
};

int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

/* ============================================================
   CHECK WHETHER WORD IS A KEYWORD
   ============================================================ */

int isKeyword(const char *word)
{
    for (int i = 0; i < keyword_count; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

/* ============================================================
   CHECK DELIMITERS / SEPARATORS
   ============================================================ */

int isDelimiter(char ch)
{
    return (
        ch == '(' || ch == ')' ||
        ch == '{' || ch == '}' ||
        ch == '[' || ch == ']' ||
        ch == ';' || ch == ',' ||
        ch == ':' 
    );
}

/* ============================================================
   CHECK OPERATOR START
   ============================================================ */

int isOperatorStart(char ch)
{
    return (
        ch == '+' || ch == '-' ||
        ch == '*' || ch == '/' ||
        ch == '%' || ch == '=' ||
        ch == '<' || ch == '>' ||
        ch == '!' || ch == '&' ||
        ch == '|' || ch == '^' ||
        ch == '~' || ch == '?' 
    );
}

/* ============================================================
   CHECK TWO CHARACTER OPERATORS
   ============================================================ */

int isTwoCharacterOperator(char first, char second)
{
    if (
        (first == '+' && second == '+') ||
        (first == '-' && second == '-') ||
        (first == '=' && second == '=') ||
        (first == '!' && second == '=') ||
        (first == '<' && second == '=') ||
        (first == '>' && second == '=') ||
        (first == '&' && second == '&') ||
        (first == '|' && second == '|') ||
        (first == '+' && second == '=') ||
        (first == '-' && second == '=') ||
        (first == '*' && second == '=') ||
        (first == '/' && second == '=') ||
        (first == '%' && second == '=') ||
        (first == '&' && second == '=') ||
        (first == '|' && second == '=') ||
        (first == '^' && second == '=') ||
        (first == '<' && second == '<') ||
        (first == '>' && second == '>')
    )
    {
        return 1;
    }

    return 0;
}

/* ============================================================
   CHECK THREE CHARACTER OPERATORS
   ============================================================ */

int isThreeCharacterOperator(char a, char b, char c)
{
    if (
        (a == '<' && b == '<' && c == '=') ||
        (a == '>' && b == '>' && c == '=')
    )
    {
        return 1;
    }

    return 0;
}

/* ============================================================
   PRINT TOKEN
   ============================================================ */

void printToken(int line,
                const char *lexeme,
                const char *token_type)
{
    printf("%-8d %-30s %-25s\n",
           line,
           lexeme,
           token_type);
}

/* ============================================================
   READ A STRING / CHARACTER LITERAL
   Handles escape characters as well.
   ============================================================ */

void readQuotedLiteral(FILE *fp,
                       char quote,
                       char *lexeme,
                       int *line)
{
    int i = 0;
    int ch;

    lexeme[i++] = quote;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (i < MAX_LEXEME - 1)
            lexeme[i++] = (char)ch;

        /* Handle escaped character */
        if (ch == '\\')
        {
            int next = fgetc(fp);

            if (next == EOF)
                break;

            if (i < MAX_LEXEME - 1)
                lexeme[i++] = (char)next;

            if (next == '\n')
                (*line)++;
        }
        else if (ch == '\n')
        {
            (*line)++;
        }
        else if (ch == quote)
        {
            break;
        }
    }

    lexeme[i] = '\0';
}

/* ============================================================
   READ NUMBER / CONSTANT
   Supports:
      123
      123.45
      1.2e10
      0xFF
      0755
      10U
      20L
      3.14f
   ============================================================ */

void readNumber(FILE *fp,
                int first,
                char *lexeme)
{
    int i = 0;
    int ch;

    lexeme[i++] = (char)first;

    /* Hexadecimal */
    if (first == '0')
    {
        ch = fgetc(fp);

        if (ch == 'x' || ch == 'X')
        {
            lexeme[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   isxdigit((unsigned char)ch))
            {
                if (i < MAX_LEXEME - 1)
                    lexeme[i++] = (char)ch;
            }

            /* Integer suffix */
            if (ch == 'u' || ch == 'U' ||
                ch == 'l' || ch == 'L')
            {
                if (i < MAX_LEXEME - 1)
                    lexeme[i++] = (char)ch;

                ch = fgetc(fp);

                if ((ch == 'l' || ch == 'L') &&
                    i < MAX_LEXEME - 1)
                {
                    lexeme[i++] = (char)ch;
                }
                else if (ch != EOF)
                {
                    ungetc(ch, fp);
                }
            }
            else if (ch != EOF)
            {
                ungetc(ch, fp);
            }

            lexeme[i] = '\0';
            return;
        }

        if (ch != EOF)
            ungetc(ch, fp);
    }

    /* Decimal / floating-point */
    int has_dot = 0;
    int has_exp = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isdigit((unsigned char)ch))
        {
            if (i < MAX_LEXEME - 1)
                lexeme[i++] = (char)ch;
        }
        else if (ch == '.' && !has_dot && !has_exp)
        {
            has_dot = 1;

            if (i < MAX_LEXEME - 1)
                lexeme[i++] = (char)ch;
        }
        else if ((ch == 'e' || ch == 'E') && !has_exp)
        {
            has_exp = 1;

            if (i < MAX_LEXEME - 1)
                lexeme[i++] = (char)ch;

            int next = fgetc(fp);

            if (next == '+' || next == '-')
            {
                if (i < MAX_LEXEME - 1)
                    lexeme[i++] = (char)next;
            }
            else if (next != EOF)
            {
                ungetc(next, fp);
            }
        }
        else
        {
            break;
        }
    }

    /* Common suffixes */
    if (ch == 'f' || ch == 'F' ||
        ch == 'u' || ch == 'U' ||
        ch == 'l' || ch == 'L')
    {
        if (i < MAX_LEXEME - 1)
            lexeme[i++] = (char)ch;

        ch = fgetc(fp);

        if ((ch == 'f' || ch == 'F' ||
             ch == 'l' || ch == 'L') &&
            i < MAX_LEXEME - 1)
        {
            lexeme[i++] = (char)ch;
        }
        else if (ch != EOF)
        {
            ungetc(ch, fp);
        }
    }
    else if (ch != EOF)
    {
        ungetc(ch, fp);
    }

    lexeme[i] = '\0';
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    FILE *fp;
    char filename[200];

    printf("=============================================================\n");
    printf("                  C LEXICAL ANALYZER\n");
    printf("=============================================================\n\n");

    printf("Enter C source file name (.c): ");
    scanf("%199s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("\nError: Unable to open file '%s'\n", filename);
        return 1;
    }

    printf("\nFile opened successfully: %s\n\n", filename);

    printf("--------------------------------------------------------------------------\n");
    printf("%-8s %-30s %-25s\n",
           "LINE", "LEXEME", "TOKEN TYPE");
    printf("--------------------------------------------------------------------------\n");

    int ch;
    int line = 1;

    while ((ch = fgetc(fp)) != EOF)
    {
        /* ========================================================
           WHITE SPACE
           ======================================================== */

        if (ch == ' ' || ch == '\t' || ch == '\r')
        {
            continue;
        }

        if (ch == '\n')
        {
            line++;
            continue;
        }

        /* ========================================================
           PREPROCESSOR
           Example:
               #include
               #define
           ======================================================== */

        if (ch == '#')
        {
            char lexeme[MAX_LEXEME];
            int i = 0;

            lexeme[i++] = '#';

            while ((ch = fgetc(fp)) != EOF &&
                   ch != '\n')
            {
                if (i < MAX_LEXEME - 1)
                    lexeme[i++] = (char)ch;
            }

            lexeme[i] = '\0';

            printToken(line, lexeme, "PREPROCESSOR");

            if (ch == '\n')
                line++;

            continue;
        }

        /* ========================================================
           IDENTIFIER / KEYWORD
           ======================================================== */

        if (isalpha((unsigned char)ch) || ch == '_')
        {
            char lexeme[MAX_LEXEME];
            int i = 0;

            lexeme[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum((unsigned char)ch) || ch == '_'))
            {
                if (i < MAX_LEXEME - 1)
                    lexeme[i++] = (char)ch;
            }

            lexeme[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(lexeme))
            {
                printToken(line, lexeme, "KEYWORD");
            }
            else
            {
                printToken(line, lexeme, "IDENTIFIER");
            }

            continue;
        }

        /* ========================================================
           NUMERIC CONSTANT
           ======================================================== */

        if (isdigit((unsigned char)ch))
        {
            char lexeme[MAX_LEXEME];

            readNumber(fp, ch, lexeme);

            printToken(line, lexeme, "CONSTANT");

            continue;
        }

        /* Floating constant beginning with .
           Example:
               .5
        */

        if (ch == '.')
        {
            int next = fgetc(fp);

            if (isdigit((unsigned char)next))
            {
                char lexeme[MAX_LEXEME];

                lexeme[0] = '.';

                int i = 1;
                lexeme[i++] = (char)next;

                while ((ch = fgetc(fp)) != EOF &&
                       isdigit((unsigned char)ch))
                {
                    if (i < MAX_LEXEME - 1)
                        lexeme[i++] = (char)ch;
                }

                lexeme[i] = '\0';

                if (ch != EOF)
                    ungetc(ch, fp);

                printToken(line, lexeme, "CONSTANT");

                continue;
            }

            if (next != EOF)
                ungetc(next, fp);

            printToken(line, ".", "OPERATOR");

            continue;
        }

        /* ========================================================
           STRING LITERAL
           ======================================================== */

        if (ch == '"')
        {
            char lexeme[MAX_LEXEME];

            readQuotedLiteral(fp,
                              '"',
                              lexeme,
                              &line);

            printToken(line,
                       lexeme,
                       "STRING LITERAL");

            continue;
        }

        /* ========================================================
           CHARACTER CONSTANT
           ======================================================== */

        if (ch == '\'')
        {
            char lexeme[MAX_LEXEME];

            readQuotedLiteral(fp,
                              '\'',
                              lexeme,
                              &line);

            printToken(line,
                       lexeme,
                       "CHARACTER CONSTANT");

            continue;
        }

        /* ========================================================
           COMMENTS OR DIVISION OPERATOR
           ======================================================== */

        if (ch == '/')
        {
            int next = fgetc(fp);

            /* Single-line comment */
            if (next == '/')
            {
                char lexeme[MAX_LEXEME];
                int i = 0;

                lexeme[i++] = '/';
                lexeme[i++] = '/';

                while ((ch = fgetc(fp)) != EOF &&
                       ch != '\n')
                {
                    if (i < MAX_LEXEME - 1)
                        lexeme[i++] = (char)ch;
                }

                lexeme[i] = '\0';

                printToken(line,
                           lexeme,
                           "SINGLE-LINE COMMENT");

                if (ch == '\n')
                    line++;

                continue;
            }

            /* Multi-line comment */
            if (next == '*')
            {
                char lexeme[MAX_LEXEME];
                int i = 0;
                int previous = 0;

                lexeme[i++] = '/';
                lexeme[i++] = '*';

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (i < MAX_LEXEME - 1)
                        lexeme[i++] = (char)ch;

                    if (ch == '\n')
                        line++;

                    if (previous == '*' && ch == '/')
                        break;

                    previous = ch;
                }

                lexeme[i] = '\0';

                printToken(line,
                           lexeme,
                           "MULTI-LINE COMMENT");

                continue;
            }

            /* Division operator */
            if (next != EOF)
                ungetc(next, fp);

            printToken(line,
                       "/",
                       "OPERATOR");

            continue;
        }

        /* ========================================================
           OPERATORS
           ======================================================== */

        if (isOperatorStart((char)ch))
        {
            int next1;
            int next2;

            next1 = fgetc(fp);
            next2 = fgetc(fp);

            /* Check 3-character operator */
            if (next1 != EOF &&
                next2 != EOF &&
                isThreeCharacterOperator(
                    (char)ch,
                    (char)next1,
                    (char)next2))
            {
                char lexeme[4];

                lexeme[0] = (char)ch;
                lexeme[1] = (char)next1;
                lexeme[2] = (char)next2;
                lexeme[3] = '\0';

                printToken(line,
                           lexeme,
                           "OPERATOR");

                continue;
            }

            /* Put second lookahead back */
            if (next2 != EOF)
                ungetc(next2, fp);

            /* Check 2-character operator */
            if (next1 != EOF &&
                isTwoCharacterOperator(
                    (char)ch,
                    (char)next1))
            {
                char lexeme[3];

                lexeme[0] = (char)ch;
                lexeme[1] = (char)next1;
                lexeme[2] = '\0';

                printToken(line,
                           lexeme,
                           "OPERATOR");

                continue;
            }

            if (next1 != EOF)
                ungetc(next1, fp);

            char lexeme[2];

            lexeme[0] = (char)ch;
            lexeme[1] = '\0';

            printToken(line,
                       lexeme,
                       "OPERATOR");

            continue;
        }

        /* ========================================================
           DELIMITERS / SEPARATORS
           ======================================================== */

        if (isDelimiter((char)ch))
        {
            char lexeme[2];

            lexeme[0] = (char)ch;
            lexeme[1] = '\0';

            printToken(line,
                       lexeme,
                       "DELIMITER");

            continue;
        }

        /* ========================================================
           INVALID / UNKNOWN CHARACTER
           ======================================================== */

        {
            char lexeme[2];

            lexeme[0] = (char)ch;
            lexeme[1] = '\0';

            printToken(line,
                       lexeme,
                       "INVALID / UNKNOWN");
        }
    }

    fclose(fp);

    printf("--------------------------------------------------------------------------\n");
    printf("\nLexical analysis completed successfully.\n");
    printf("Input file: %s\n", filename);

    return 0;
}