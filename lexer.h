#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 20
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    UNKNOWN
} TokenType;

typedef enum{
    e_success,
    e_failure
} Status;

typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

Status initializeLexer(const char* filename);
int isKeyword(const char* str,int* i);
int isOperator(const char* str,int* i);
int isSpecialCharacter(char ch);
int isConstant(const char* str,int* i);
int isIdentifier(const char* str,int* i);
void skip_preprocessor_lines(const char* str,int* i);
void tokens();

#endif
