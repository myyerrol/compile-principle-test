#ifndef TOP_DOWN_RECURSIVE_DESCENT_ANALYSIS_H
#define TOP_DOWN_RECURSIVE_DESCENT_ANALYSIS_H

// G[Statements]:
// Statements->{Expression;}
// Expression->Term{+Term}
// Term->Factor{*Factor}
// Factor->Number | {Expression}
#define STATEMENTS 'S'
#define EXPRESSION 'E'
#define TERM       'T'
#define FACTOR     'F'
#define NUMBER     'n'
#define PLUS       '+'
#define TIMES      '*'
#define SEMI       ';'
#define LP         '('
#define RP         ')'
#define EOI        0
#define SIZE       5

typedef struct Production {
    char head;
    char tail[SIZE];
    int  tail_len;
} Production;

typedef struct FiristSet {
    char first[SIZE];
    char first_len;
} FiristSet;

FiristSet first_set[4] = {
    {0},
    {{NUMBER, LP}, 2},
    {{NUMBER, LP}, 2},
    {{NUMBER, LP}, 2}
};

void buildStatements(const char **input_char);
void buildExpression(const char **input_char);
void buildTerm(const char **input_char);
void buildFactor(const char **input_char);
void readNextCharacter(const char **input_char);
int matchTerminalCharacter(const char **input_char, const char terminal_char);
int matchTerminalFirstSet(const char **input_char, const char nonterminal_char);

#endif // TOP_DOWN_RECURSIVE_DESCENT_ANALYSIS_H
