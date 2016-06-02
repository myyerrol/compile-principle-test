%option noyywrap yylineno

%{
    #include "pascal_simple_compiler_yacc.h"
    #include "pascal_handle_symbol_table.h"
%}

LETTER [A-Za-z]
ALNUM  [A-Za-z0-9]
DIGIT  [0-9]
SPACE  [\t\n\040]

%%
[Bb][eE][Gg][iI][Nn]                  { ECHO; return STATEMENT_BEGIN; }
[eE][Nn][Dd]                          { ECHO; return STATEMENT_END; }
[Aa][Nn][Dd]                          { ECHO; return AND; }
[Oo][Rr]                              { ECHO; return OR; }
[Nn][Oo][Tt]                          { ECHO; return NOT; }
[iI][Ff]                              { ECHO; return IF; }
[Ee][Ll][Ss][Ee]                      { ECHO; return ELSE; }
[Tt][Hh][Ee][Nn]                      { ECHO; return THEN; }
[Ww][Hh][Ii][Ll][Ee]                  { ECHO; return WHILE; }
[Dd][oO]                              { ECHO; return DO; }
[Ii][nN][Tt][eE][Gg][eE][Rr]          { ECHO; return INTEGER; }
[Rr][eE][Aa][lL]                      { ECHO; return REAL; }
":="                                  { ECHO; return ASSIGN; }
"+"                                   { ECHO; return ADD; }
"-"                                   { ECHO; return SUB; }
"*"                                   { ECHO; return MUL; }
"/"                                   { ECHO; return DIV; }
"("                                   { ECHO; return LP; }
")"                                   { ECHO; return RP; }
"<"                                   { ECHO; return LT; }
"<="                                  { ECHO; return LE; }
">"                                   { ECHO; return GT; }
">="                                  { ECHO; return GE; }
"="                                   { ECHO; return EQ; }
"<>"                                  { ECHO; return NE; }
":"                                   { ECHO; return COLON; }
";"                                   { ECHO; return SEMICOLON; }
"\."                                  { ECHO; return DOT; }
","                                   { ECHO; return COMMA; }
{SPACE}+                              { ECHO; }
{DIGIT}+ {
    ECHO;
    yylval.string = yytext;
    return NUMBER_INTEGER;
}
{DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+ {
    ECHO;
    yylval.string = yytext;
    return NUMBER_REAL;
}
{LETTER}{ALNUM}*                      {
    ECHO;
    yylval.string = yytext;
    return IDENTIFIER;
}
.                                     { ECHO; return ERROR_STRING; }

%%
