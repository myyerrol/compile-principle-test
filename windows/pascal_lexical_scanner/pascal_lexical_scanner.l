%option noyywrap yylineno
%{
#include <stdio.h>
#include <stdlib.h>

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
%}

%%
";"                    { return SEMICOLON; }
":"                    { return COLON; }
","                    { return COMMA; }
"integer"              { return TYPE_INTEGER; }
"real"                 { return TYPE_REAL; }
"begin"                { return BLOCK_BEGIN; }
"end"                  { return BLOCK_END; }
"."                    { return DOT; }
":="                   { return ASSIGN; }
"if"                   { return IF; }
"else"                 { return ELSE; }
"then"                 { return THEN; }
"while"                { return WHILE; }
"do"                   { return DO; }
"+"                    { return ADD; }
"-"                    { return SUB; }
"*"                    { return MUL; }
"/"                    { return DIV; }
"("                    { return LP; }
")"                    { return RP; }
"and"                  { return AND; }
"or"                   { return OR; }
"not"                  { return NOT; }
"<"                    { return LT; }
">"                    { return GT; }
"<="                   { return LE; }
">="                   { return GE; }
"="                    { return EQ; }
"<>"                   { return NE; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
([1-9][0-9]*)|"0"      { return NUMBER_INTEGER; }
[0-9]+\.[0-9]+         { return NUMBER_REAL; }
\n                     { ; }
[ \t]                  { ; }
.                      { printf("Error, invalid character: %s\n", yytext); }
