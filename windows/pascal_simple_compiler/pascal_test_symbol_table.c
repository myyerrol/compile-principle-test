#include <stdlib.h>
#include <stdio.h>
#include "pascal_handle_symbol_table.h"

#if 0
int main(void)
{
    int constant_index;
    int variable_index;

    createConstantNode();
    generateConstantNode(TYPE_INTEGER, "10");
    generateConstantNode(TYPE_REAL, "20.0");
    generateConstantNode(TYPE_STRING, "Hello");
    //constant_index = getConstantNodeIndex("10");
    printAllConstantNode();
    printf("\n");

    createVariableNode();
    generateVariableNode(TYPE_INTEGER, VARIABLE_USER,"10", "a");
    generateVariableNode(TYPE_REAL, VARIABLE_USER, "20.0", "b");
    generateVariableNode(TYPE_STRING, VARIABLE_TEMP, "Hello", "c");
    //variable_index = getVariableNodeIndex("c");
    printAllVariableNode();
    printf("\n");

    return 0;
}
#endif
