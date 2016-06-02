#include <stdio.h>
#include "pascal_simple_compiler_lex.h"
#include "pascal_simple_compiler_yacc.h"
#include "pascal_handle_quaternion.h"
#include "pascal_handle_symbol_table.h"
#include "pascal_handle_syntax_tree.h"

#if 1
int main(int argc, char **argv)
{
    yyin = stdin;

    if (argc > 1) {
        if ((yyin=fopen(argv[1], "r")) == NULL) {
            printf("Error, can't not open file %s\n", argv[1]);
            return 0;
        }
    }

    yyparse();

    return 0;
}
#endif
