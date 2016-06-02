%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pascal_simple_compiler_lex.h"
#include "pascal_simple_compiler_yacc.h"
#include "pascal_handle_quaternion.h"
#include "pascal_handle_symbol_table.h"
#include "pascal_handle_syntax_tree.h"

#define string_size            20
#define string_with_minus_size 25

void performArithmeticOperation(struct Expression *expr_parent_node,
                                struct Expression *expr_l_son_node,
                                struct Expression *expr_r_son_node,
                                int type_quaternion,
                                int type_syntaxtree,
                                char *opcode);
int yyerror(char *string);
%}

%union {
    int  type;
    char *string;
    struct Statement {
        struct SyntaxTreeNode **ast_node;
    } *statement;
    struct Expression {
        int                   index_symbol;
        int                   index_quaternion;
        struct SyntaxTreeNode **ast_node;
    } *expression;
    struct Symbol {
        int                   index_symbol;
        struct SyntaxTreeNode **ast_node;
    } *symbol;
}

%token <string> IDENTIFIER
%token <string> NUMBER_INTEGER
%token <string> NUMBER_REAL
%token          ERROR_STRING
%token          SEMICOLON
%token          COMMA
%token          COLON
%token          DOT
%token          INTEGER
%token          REAL
%token          STATEMENT_BEGIN
%token          STATEMENT_END
%token          ASSIGN
%token          IF
%token          ELSE
%token          THEN
%token          WHILE
%token          DO
%token          ADD
%token          SUB
%token          MUL
%token          DIV
%token          LP
%token          RP
%token          AND
%token          OR
%token          NOT
%token          LT
%token          GT
%token          LE
%token          GE
%token          EQ
%token          NE

%left OR
%left AND
%nonassoc NOT
%nonassoc LT GT LE GE EQ NE
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS

%type <string>     Statement
%type <statement>  AssignmentStatement
%type <expression> Expression
%type <symbol>     Variable
%type <symbol>     Constant

%start ProgramDefinition

%%
ProgramDefinition
    : Program IDENTIFIER SEMICOLON SubProgram {

    }
SubProgram
    : VariableDefinition CompleteStatement {

    }
VariableDefinition
    : Variable VariableDefinitionList SEMICOLON {

    }
VariableDefinitionList
    : VariableDefinitionStatement SEMICOLON VariableDefinitionList {

    }
    | VariableDefinitionStatement {

    }
VariableDefinitionStatement
    : VariableList COLON Type {

    }
Type
    : TYPE_INTEGER | TYPE_REAL {

    }
VariableList
    : Variable COMMA VariableList {

    }
    | Variable {

    }
StatementList
    : Statement SEMICOLON StatementList {

    }
    | Statement {

    }
Statement
    : AssignmentStatement {

    }
    | IfStatementElse Statement {

    }
    | IfBoolExpressionThen Statement {

    }
    | WhileBoolExpressionDo Statement {

    }
    | CompleteStatement {

    }
    |
CompleteStatement
    : STATEMENT_BEGIN StatementList STATEMENT_END DOT {

    }
AssignmentStatement
    : Variable ASSIGN Expression {
        int  type_temp;
        char *value_temp;

        value_temp = getSymbolNodeValue($3->index_symbol);
        type_temp  = getSymbolNodeType($3->index_symbol);

        ModifyVariableNode($1->index_symbol, type_temp, value_temp);
        generateQuaternionNode($3->index_symbol,
                               0,
                               $1->index_symbol,
                               OPCODE_ASSIGN);

        $$ = (struct Statement *)malloc(sizeof(struct Statement));
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_ASSIGN, ":=");
        addSyntaxTreeSonNode(*($$->ast_node), *($1->ast_node));
        addSyntaxTreeSonNode(*($$->ast_node), *($3->ast_node));
    }
IfStatementElse
    : IfBoolExpressionThen Statement ELSE {

    }
IfBoolExpressionThen
    : IF BoolExpression THEN {

    }
WhileBoolExpressionDo
    : WHILE BoolExpression DO {

    }
Expression
    : Expression ADD Expression {
        int    index_temp;
        int    type_a, type_b;
        int    result_type;
        int    result_int;
        double result_real;
        char   result[string_size];
        char   *value_a, *value_b;

        type_a  = getSymbolNodeType($1->index_symbol);
        type_b  = getSymbolNodeType($3->index_symbol);
        value_a = getSymbolNodeValue($1->index_symbol);
        value_b = getSymbolNodeValue($3->index_symbol);

        if (type_a == TYPE_INTEGER && type_b == TYPE_INTEGER) {
            result_int = atoi(value_a) + atoi(value_b);
            sprintf(result, "%d", result_int);
            result_type = TYPE_INTEGER;
        }
        else if (type_a == TYPE_REAL && type_b == TYPE_REAL) {
            result_real = atof(value_a) + atof(value_b);
            sprintf(result, "%lf", result_real);
            result_type = TYPE_REAL;
        }
        else {
            printf("Warning, \'%s\' type mismatch \'%s\'!", value_a, value_b);
            exit(0);
        }

        index_temp = generateVariableNode(result_type, VARIABLE_TEMP, result,
                                          "temp");
        $$ = (struct Expression *)malloc(sizeof(struct Expression));
        $$->index_symbol = index_temp;
        $$->index_quaternion = generateQuaternionNode($1->index_symbol,
                                                      $3->index_symbol,
                                                      index_temp,
                                                      OPCODE_ADD);
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_ADD, "+");
        addSyntaxTreeSonNode(*($$->ast_node), *($1->ast_node));
        addSyntaxTreeSonNode(*($$->ast_node), *($3->ast_node));
    }
    | Expression SUB Expression {
        performArithmeticOperation($$, $1, $3, OPCODE_SUB, NODE_SUB, "-");
    }
    | Expression MUL Expression {
        performArithmeticOperation($$, $1, $3, OPCODE_MUL, NODE_MUL, "*");
    }
    | Expression DIV Expression {
        performArithmeticOperation($$, $1, $3, OPCODE_DIV, NODE_DIV, "/");
    }
    | LP Expression RP {
        $$ = $2;
    }
    | '-' Expression %prec UMINUS {
        int  index_temp;
        int  type_temp;
        char result[string_with_minus_size] = "-";
        char *value_temp;

        value_temp = getSymbolNodeValue($2->index_symbol);
        type_temp = getSymbolNodeType($2->index_symbol);
        strcat(result, value_temp);

        if ($2->index_symbol > 0) {
            index_temp = generateConstantNode(type_temp, result);
        }
        else {
            index_temp = generateVariableNode(type_temp, VARIABLE_TEMP, result,
                                              "temp");
        }

        $$ = (struct Expression *)malloc(sizeof(struct Expression));
        $$->index_symbol = index_temp;
        $$->index_quaternion = generateQuaternionNode($2->index_symbol,
                                                      0,
                                                      $$->index_symbol,
                                                      OPCODE_MINUS);
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_NULL, result);
    }
    | Variable {
        $$ = (struct Expression *)malloc(sizeof(struct Expression));
        $$->index_symbol = $1->index_symbol;
        $$->index_quaternion = 0;
        $$->ast_node = $1->ast_node;
    }
    | Constant {
        $$ = (struct Expression *)malloc(sizeof(struct Expression));
        $$->index_symbol = $1->index_symbol;
        $$->index_quaternion = 0;
        $$->ast_node = $1->ast_node;
    }
BoolExpression
    : Expression RelationOperator Expression {
    }
    | BoolExpression AND {
    }
    | BoolExpression OR {
    }
    | NOT BoolExpression {
    }
    | LP BoolExpression RP {
    }
Variable
    : IDENTIFIER {
        $$ = (struct Symbol *)malloc(sizeof(struct Symbol));
        $$->index_symbol = generateVariableNode(TYPE_NULL, VARIABLE_USER, NULL, $1);
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_NULL, $1);
    }
Constant
    : NUMBER_INTEGER {
        $$ = (struct Symbol *)malloc(sizeof(struct Symbol));
        $$->index_symbol = generateConstantNode(TYPE_INTEGER, $1);
        $$->ast_node =
            (struct SyntaxTreeNode **)malloc(sizeof(struct SyntaxTreeNode));
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_INTEGER, $1);
    }
    | NUMBER_REAL {
        $$ = (struct Symbol *)malloc(sizeof(struct Symbol));
        $$->index_symbol = generateConstantNode(TYPE_REAL, $1);
        $$->ast_node =
            (struct SyntaxTreeNode **)malloc(sizeof(struct SyntaxTreeNode));
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_REAL, $1);
    }
RelationOperator
    : LT {}
    | GT {}
    | LE {}
    | GE {}
    | EQ {}
    | NE {}

%%

void performArithmeticOperation(struct Expression *expr_parent_node,
                                struct Expression *expr_l_son_node,
                                struct Expression *expr_r_son_node,
                                int type_quaternion,
                                int type_syntaxtree,
                                char *opcode)
{
    int    index_temp;
    int    type_a, type_b;
    int    result_type;
    int    result_int;
    double result_real;
    char   *result = NULL;
    char   *value_a, *value_b;

    type_a  = getSymbolNodeType(expr_l_son_node->index_symbol);
    type_b  = getSymbolNodeType(expr_r_son_node->index_symbol);
    value_a = getSymbolNodeValue(expr_l_son_node->index_symbol);
    value_b = getSymbolNodeValue(expr_r_son_node->index_symbol);

    if (type_a == TYPE_INTEGER && type_b == TYPE_INTEGER) {
        result_int = atoi(value_a) + atoi(value_b);
        sprintf(result, "%d", result_int);
        result_type = TYPE_INTEGER;
    }
    else if (type_a == TYPE_REAL && type_b == TYPE_REAL) {
        result_real = atof(value_a) + atof(value_b);
        sprintf(result, "%lf", result_real);
        result_type = TYPE_REAL;
    }
    else {
        printf("Warning, \'%s\' type mismatch \'%s\'!", value_a, value_b);
        exit(0);
    }

    index_temp = generateVariableNode(result_type, VARIABLE_TEMP, result,
                                      "temp");
    expr_parent_node = (struct Expression *)malloc(sizeof(struct Expression));
    expr_parent_node->index_symbol = index_temp;
    expr_parent_node->index_quaternion = generateQuaternionNode(
        expr_l_son_node->index_symbol,
        expr_r_son_node->index_symbol,
        index_temp,
        type_quaternion);
    expr_parent_node->ast_node = createSyntaxTreeNodePointer();
    createSyntaxTreeNode(expr_parent_node->ast_node);
    setSyntaxTreeNode(*(expr_parent_node->ast_node), type_syntaxtree, opcode);
    addSyntaxTreeSonNode(*(expr_parent_node->ast_node),
                         *(expr_l_son_node->ast_node));
    addSyntaxTreeSonNode(*(expr_parent_node->ast_node),
                         *(expr_r_son_node->ast_node));
}

int yyerror(char *string)
{
    printf("%s!\n",string);
    return 0;
}
