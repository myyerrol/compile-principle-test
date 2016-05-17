#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "top_down_recursive_descent_analysis.h"

void buildStatements(const char **input_char)
{
    while (!matchTerminalCharacter(input_char, EOI)) {
        buildExpression(input_char);
        if (matchTerminalCharacter(input_char, SEMI)) {
            readNextCharacter(input_char);
        }
        else {
            printf("Error, please insert missing semicolon!\n");
            return ;
        }
    }

    printf("Yes!\n");
}

void buildExpression(const char **input_char)
{
    if (!matchTerminalFirstSet(input_char, EXPRESSION)) {
        return ;
    }

    buildTerm(input_char);

    while (matchTerminalCharacter(input_char, PLUS)) {
        readNextCharacter(input_char);
        buildTerm(input_char);
    }
}

void buildTerm(const char **input_char)
{
    if (!matchTerminalFirstSet(input_char, TERM)) {
        return ;
    }

    buildFactor(input_char);

    while (matchTerminalCharacter(input_char, TIMES)) {
        readNextCharacter(input_char);
        buildFactor(input_char);
    }
}

void buildFactor(const char **input_char)
{
    if (!matchTerminalFirstSet(input_char, FACTOR)) {
        return ;
    }
    if (matchTerminalCharacter(input_char, NUMBER)) {
        readNextCharacter(input_char);
    }
    else if (matchTerminalCharacter(input_char, LP)) {
        readNextCharacter(input_char);
        buildExpression(input_char);
        if (matchTerminalCharacter(input_char, RP)) {
            readNextCharacter(input_char);
        }
        else {
            printf("Error, please insert missing right bracket!\n");
        }
    }
    else {
        printf("Error, please insert number or identifier!\n");
    }
}

void readNextCharacter(const char **input_char)
{
    (*input_char)++;
    return ;
}

int matchTerminalCharacter(const char **input_char, const char terminal_char)
{
    char current_char = **input_char;

    if (current_char >= '0' && current_char <= '9') {
        current_char = NUMBER;
    }
    if (current_char == terminal_char) {
        return 1;
    }
    else {
        return 0;
    }
}

int matchTerminalFirstSet(const char **input_char, const char nonterminal_char)
{
    int i;
    int index;
    char current_char = **input_char;

    if (current_char >= '0' && current_char <= '9') {
        current_char = NUMBER;
    }
    if (nonterminal_char == STATEMENTS) {
        index = 0;
    }
    else if (nonterminal_char == EXPRESSION) {
        index = 1;
    }
    else if (nonterminal_char == TERM) {
        index = 2;
    }
    else if (nonterminal_char == FACTOR) {
        index = 3;
    }

    for (i = 0; i < first_set[index].first_len; i++) {
        if (current_char == first_set[index].first[i]) {
            return 1;
        }
    }

    printf("Error, no characters belong to nonterminal character!\n");
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    int char_size = strlen(argv[2]);

    Production production[4], *p_production;
    p_production = production;

    p_production[0].head = STATEMENTS;
    p_production[0].tail[0] = EXPRESSION;
    p_production[0].tail[1] = SEMI;
    p_production[0].tail_len = 2;

    p_production[1].head = EXPRESSION;
    p_production[1].tail[0] = TERM;
    p_production[1].tail[1] = PLUS;
    p_production[1].tail[2] = TERM;
    p_production[1].tail_len = 3;

    p_production[2].head = TERM;
    p_production[2].tail[0] = FACTOR;
    p_production[2].tail[1] = SEMI;
    p_production[2].tail[2] = FACTOR;
    p_production[2].tail_len = 3;

    p_production[3].head = FACTOR;
    p_production[3].tail[0] = NUMBER;
    p_production[3].tail[1] = LP;
    p_production[3].tail[2] = EXPRESSION;
    p_production[3].tail[3] = RP;

    printf("Start Recursive Descent Analysis\n");
    printf("Input string: ");

    for (i = 0; i < char_size; i++) {
        printf("%c", *argv[2]);
        argv[2]++;
    }
    
    printf("\n");
    
    argv[2] -= char_size;
    buildStatements(&argv[2]);

    return 0;
}
