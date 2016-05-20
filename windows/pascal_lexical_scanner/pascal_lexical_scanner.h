#ifndef PASCAL_LEXICAL_SCANNER_H
#define PASCAL_LEXICAL_SCANNER_H

#define SIZE           29

#define IDENTIFIER     258
#define SEMICOLON      259
#define COLON          260
#define TYPE_INTEGER   261
#define TYPE_REAL      262
#define COMMA          263
#define BLOCK_BEGIN    264
#define BLOCK_END      265
#define DOT            266
#define ASSIGN         267
#define IF             268
#define ELSE           269
#define THEN           270
#define WHILE          271
#define DO             272
#define ADD            273
#define SUB            274
#define MUL            275
#define DIV            276
#define LP             277
#define RP             278
#define AND            279
#define OR             280
#define NOT            281
#define LT             282
#define GT             283
#define LE             284
#define GE             285
#define EQ             286
#define NE             287
#define NUMBER_INTEGER 288
#define NUMBER_REAL    289

typedef struct {
    char *name;
    int  value;
} TokenTable;

extern TokenTable token_table[SIZE] = {
    {";",       SEMICOLON},
    {":",       COLON},
    {",",       COMMA},
    {"integer", TYPE_INTEGER},
    {"real",    TYPE_REAL},
    {"begin",   BLOCK_BEGIN},
    {"end",     BLOCK_END},
    {".",       DOT},
    {":=",      ASSIGN},
    {"if",      IF},
    {"else",    ELSE},
    {"then",    THEN},
    {"while",   WHILE},
    {"do",      DO},
    {"+",       ADD},
    {"-",       SUB},
    {"*",       MUL},
    {"/",       DIV},
    {"(",       LP},
    {")",       RP},
    {"and",     AND},
    {"or",      OR},
    {"not",     NOT},
    {"<",       LT},
    {">",       GT},
    {"<=",      LE},
    {">=",      GE},
    {"=",       EQ},
    {"<>",      NE}
};

TokenTable *searchTokenTable(TokenTable *input_table,
                             TokenTable *search_table);
int judgeIdentifierOrNumber(char *input_string);

#endif // PASCAL_LEXICAL_SCANNER_H
