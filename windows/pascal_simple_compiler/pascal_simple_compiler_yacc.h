/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PASCAL_SIMPLE_COMPILER_YACC_H_INCLUDED
# define YY_YY_PASCAL_SIMPLE_COMPILER_YACC_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     NUMBER_INTEGER = 259,
     NUMBER_REAL = 260,
     TYPE_INTEGER = 261,
     TYPE_REAL = 262,
     PROGRAM = 263,
     ERROR_STRING = 264,
     SEMICOLON = 265,
     COMMA = 266,
     COLON = 267,
     DOT = 268,
     INTEGER = 269,
     REAL = 270,
     STATEMENT_BEGIN = 271,
     STATEMENT_END = 272,
     ASSIGN = 273,
     IF = 274,
     ELSE = 275,
     THEN = 276,
     WHILE = 277,
     DO = 278,
     ADD = 279,
     SUB = 280,
     MUL = 281,
     DIV = 282,
     LP = 283,
     RP = 284,
     AND = 285,
     OR = 286,
     NOT = 287,
     LT = 288,
     GT = 289,
     LE = 290,
     GE = 291,
     EQ = 292,
     NE = 293,
     UMINUS = 294
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 82 "pascal_simple_compiler.y"

    char *string;
    struct Statement {
        struct SyntaxTreeNode **ast_node;
    } *statement;
    struct BoolExpression {
        int                   true_or_false;
        int                   chain_true;
        int                   chain_false;
        struct SyntaxTreeNode **ast_node;
    } *bool_expression;
    struct Expression {
        int                   type;
        int                   index_symbol;
        int                   index_quaternion;
        char                  *value;
        char                  *name;
        struct SyntaxTreeNode **ast_node;
    } *expression;
    struct Symbol {
        int                   type;
        int                   index_symbol;
        char                  *value;
        char                  *name;
        struct SyntaxTreeNode **ast_node;
    } *symbol;
    struct RelationOperator {
        int  type_ast;
        int  type_opcode;
        char *value;
    } relation_operator;


/* Line 2058 of yacc.c  */
#line 130 "pascal_simple_compiler_yacc.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PASCAL_SIMPLE_COMPILER_YACC_H_INCLUDED  */
