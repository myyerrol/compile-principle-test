%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pascal_simple_compiler_lex.h"
#include "pascal_simple_compiler_yacc.h"
#include "pascal_handle_quaternion.h"
#include "pascal_handle_symbol_table.h"
#include "pascal_handle_syntax_tree.h"

#define STRING_SIZE            20
#define STRING_WITH_MINUS_SIZE 25
#define TRUE                   1
#define FALSE                  0

#define MALLOC_YACC_STRUCT(type)                                         \
(struct type *)malloc(sizeof(struct type))                               \

#define JUDGE_BOOL_EXPRESSION(expr_l, expr_r, expr_bool, operator, type) \
do {                                                                     \
    if (operator.type_opcode == OPCODE_JLT) {                            \
        if (type(expr_l->value) < type(expr_r->value)) {                 \
            expr_bool->true_or_false = TRUE;                             \
        }                                                                \
        else {                                                           \
            expr_bool->true_or_false = FALSE;                            \
        }                                                                \
    }                                                                    \
    else if (operator.type_opcode == OPCODE_JGT) {                       \
        if (type(expr_l->value) > type(expr_r->value)) {                 \
            expr_bool->true_or_false = TRUE;                             \
        }                                                                \
        else {                                                           \
            expr_bool->true_or_false = FALSE;                            \
        }                                                                \
    }                                                                    \
    else if (operator.type_opcode == OPCODE_JLE) {                       \
        if (type(expr_l->value) <= type(expr_r->value)) {                \
            expr_bool->true_or_false = TRUE;                             \
        }                                                                \
        else {                                                           \
            expr_bool->true_or_false = FALSE;                            \
        }                                                                \
    }                                                                    \
    else if (operator.type_opcode == OPCODE_JGE) {                       \
        if (type(expr_l->value) >= type(expr_r->value)) {                \
            expr_bool->true_or_false = TRUE;                             \
        }                                                                \
        else {                                                           \
            expr_bool->true_or_false = FALSE;                            \
        }                                                                \
    }                                                                    \
    else if (operator.type_opcode == OPCODE_JEQ) {                       \
        if (type(expr_l->value) == type(expr_r->value)) {                \
            expr_bool->true_or_false = TRUE;                             \
        }                                                                \
        else {                                                           \
            expr_bool->true_or_false = FALSE;                            \
        }                                                                \
    }                                                                    \
    else if (operator.type_opcode == OPCODE_JNE) {                       \
        if (type(expr_l->value) != type(expr_r->value)) {                \
            expr_bool->true_or_false = TRUE;                             \
        }                                                                \
        else {                                                           \
            expr_bool->true_or_false = FALSE;                            \
        }                                                                \
    }                                                                    \
} while (0)

extern int g_quaternion_index;

void performArithmeticOperation(struct Expression *expr_parent_node,
                                struct Expression *expr_l_son_node,
                                struct Expression *expr_r_son_node,
                                int type_quaternion,
                                int type_syntaxtree,
                                char *opcode);
int yyerror(char *string);
%}

%union {
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
}

%token <string> IDENTIFIER
%token <string> NUMBER_INTEGER
%token <string> NUMBER_REAL
%token          TYPE_INTEGER
%token          TYPE_REAL
%token          PROGRAM
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

%type <string>            ProgramDefinition
%type <string>            SubProgram
%type <string>            VariableDefinition
%type <string>            CompleteStatement
%type <string>            VariableDefinitionList
%type <string>            VariableDefinitionStatement
%type <string>            VariableList
%type <string>            Type
%type <string>            StatementList
%type <string>            Statement
%type <statement>         AssignmentStatement
%type <string>            IfStatementElse
%type <string>            IfBoolExpressionThen
%type <string>            WhileBoolExpressionDo
%type <bool_expression>   BoolExpression;
%type <expression>        Expression
%type <symbol>            Variable
%type <symbol>            Constant
%type <relation_operator> RelationOperator

%start ProgramDefinition

%%
ProgramDefinition
    : PROGRAM IDENTIFIER SEMICOLON SubProgram {

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
    : TYPE_INTEGER {

    }
    | TYPE_REAL {

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
        ModifyVariableNode($1->index_symbol, $3->type, $3->value);
        generateQuaternionNode($3->index_symbol, 0, $1->index_symbol,
                               OPCODE_ASSIGN);
        $$ = MALLOC_YACC_STRUCT(Statement);
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
        performArithmeticOperation($$, $1, $3, OPCODE_SUB, NODE_SUB, "+");
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
        char result[STRING_WITH_MINUS_SIZE] = "-";

        strcat(result, $2->value);

        if ($2->index_symbol > 0) {
            index_temp = generateConstantNode($2->type, result);
        }
        else {
            index_temp = generateVariableNode($2->type, VARIABLE_TEMP, result,
                                              "temp");
        }

        $$ = MALLOC_YACC_STRUCT(Expression);
        $$->index_symbol = index_temp;
        $$->index_quaternion = generateQuaternionNode($2->index_symbol, 0,
                                                      $$->index_symbol,
                                                      OPCODE_MINUS);
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_NULL, result);
    }
    | Variable {
        $$ = MALLOC_YACC_STRUCT(Expression);
        $$->index_symbol = $1->index_symbol;
        $$->type  = $1->type;
        $$->value = $1->value;
        $$->name  = $1->name;
        $$->index_quaternion = 0;
        $$->ast_node = $1->ast_node;
    }
    | Constant {
        $$ = MALLOC_YACC_STRUCT(Expression);
        $$->index_symbol = $1->index_symbol;
        $$->type  = $1->type;
        $$->value = $1->value;
        $$->name  = $1->name;
        $$->index_quaternion = 0;
        $$->ast_node = $1->ast_node;
    }
BoolExpression
    : Expression RelationOperator Expression {
        if ($1->type == TYPE_INTEGER && $3->type == TYPE_INTEGER) {
            JUDGE_BOOL_EXPRESSION($1, $3, $$, $2, atoi);
        }
        else if ($1->type == TYPE_REAL && $3->type == TYPE_REAL) {
            JUDGE_BOOL_EXPRESSION($1, $3, $$, $2, atof);
        }
        else {
            printf("Warning, \'%s\' type mismatch \'%s\' type!", $1->value,
                $3->value);
            exit(0);
        }

        $$ = MALLOC_YACC_STRUCT(BoolExpression);
        $$->chain_true  = g_quaternion_index;
        $$->chain_false = g_quaternion_index + 1;
        generateQuaternionNode($1->index_symbol, $3->index_symbol, 0,
                               $2.type_opcode);
        generateQuaternionNode(0, 0, 0, OPCODE_JMP);
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), $2.type_ast, $2.value);
        addSyntaxTreeSonNode(*($$->ast_node), *($1->ast_node));
        addSyntaxTreeSonNode(*($$->ast_node), *($3->ast_node));
    }
    | BoolExpression AND {

    }
    | BoolExpression OR {
    }
    | NOT BoolExpression {
        $$ = MALLOC_YACC_STRUCT(BoolExpression);
        $$->true_or_false = ($2->true_or_false == TRUE) ? FALSE : TRUE;
        $$->chain_true = $2->chain_false;
        $$->chain_false = $2->chain_true;
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_NOT, "not");
        addSyntaxTreeSonNode(*($$->ast_node), *($2->ast_node));
    }
    | LP BoolExpression RP {
        $$ = MALLOC_YACC_STRUCT(BoolExpression);
        $$->true_or_false = $2->true_or_false;
        $$->chain_true = $2->chain_true;
        $$->chain_false = $2->chain_false;
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_LP_RP, "()");
        addSyntaxTreeSonNode(*($$->ast_node), *($2->ast_node));
    }
Variable
    : IDENTIFIER {
        $$ = MALLOC_YACC_STRUCT(Symbol);
        $$->index_symbol = generateVariableNode(TYPE_NULL, VARIABLE_USER, NULL, $1);
        $$->type  = TYPE_NULL;
        $$->value = NULL;
        $$->name  = $1;
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_NULL, $1);
    }
Constant
    : NUMBER_INTEGER {
        $$ = MALLOC_YACC_STRUCT(Symbol);
        $$->index_symbol = generateConstantNode(TYPE_INTEGER, $1);
        $$->type  = TYPE_INTEGER;
        $$->value = $1;
        $$->name  = NULL;
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_INTEGER, $1);
    }
    | NUMBER_REAL {
        $$ = MALLOC_YACC_STRUCT(Symbol);
        $$->index_symbol = generateConstantNode(TYPE_REAL, $1);
        $$->type  = TYPE_REAL;
        $$->value = $1;
        $$->name  = NULL;
        $$->ast_node = createSyntaxTreeNodePointer();
        createSyntaxTreeNode($$->ast_node);
        setSyntaxTreeNode(*($$->ast_node), NODE_REAL, $1);
    }
RelationOperator
    : LT {
        $$.type_ast    = NODE_LT;
        $$.type_opcode = OPCODE_JLT;
        $$.value       = "LT";
    }
    | GT {
        $$.type_ast    = NODE_GT;
        $$.type_opcode = OPCODE_JGT;
        $$.value       = "GT";
    }
    | LE {
        $$.type_ast    = NODE_LE;
        $$.type_opcode = OPCODE_JLE;
        $$.value       = "LE";
    }
    | GE {
        $$.type_ast    = NODE_GE;
        $$.type_opcode = OPCODE_JGE;
        $$.value       = "GE";
    }
    | EQ {
        $$.type_ast    = NODE_EQ;
        $$.type_opcode = OPCODE_JEQ;
        $$.value       = "EQ";
    }
    | NE {
        $$.type_ast    = NODE_NE;
        $$.type_opcode = OPCODE_JNE;
        $$.value       = "NE";
    }

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
    char   result[STRING_SIZE];
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
        printf("Warning, \'%s\' type mismatch \'%s\' type!", value_a, value_b);
        exit(0);
    }

    index_temp = generateVariableNode(result_type, VARIABLE_TEMP, result,
                                      "temp");
    expr_parent_node = MALLOC_YACC_STRUCT(Expression);
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
