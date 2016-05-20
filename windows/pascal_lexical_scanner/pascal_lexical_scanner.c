#include <stdio.h>
#include <stdlib.h>
#include "pascal_lexical_scanner_lex.h"
#include "pascal_lexical_scanner.h"

TokenTable *searchTokenTable(TokenTable *input_table, 
                             TokenTable *search_table)
{
    int i;

    for (i = 0; i < SIZE; i++) {
        if (!strcmp(input_table->name, token_table[i].name)) {
            return &token_table[i];
        }
    }

    return NULL;
}

int judgeIdentifierOrNumber(char *input_string)
{
    TokenTable *p_temp_token_table;
    TokenTable temp_token_table;

    temp_token_table.name = input_string;
    p_temp_token_table = searchTokenTable(&temp_token_table, token_table);

    if (p_temp_token_table != NULL) {
        return p_temp_token_table->value;
    }
    else {
        return 1;
    }
}

int main(int argc, char **argv)
{
    int type;
	int token;
    yylineno = 1;

	if (argc > 1) {
		if ((yyin = fopen(argv[1], "r")) == NULL) {
			printf("Error, can't open file %s\n", argv[1]);
			return -1;
		}
	}

    printf("Line's number  Identified content  Identified type\n");

	while (token = yylex()) {
        type = judgeIdentifierOrNumber(yytext);
        if (type == 1) {
            type = token;
        }
		printf("%13d  %18s  %15d\n", yylineno, yytext, type);
	}

	return 0;
}