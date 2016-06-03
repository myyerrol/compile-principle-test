#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pascal_handle_symbol_table.h"

int g_constant_index = 1;
int g_variable_index = -1;
ConstantTableNode *g_constant_head_node, *g_constant_tail_node;
VariableTableNode *g_variable_head_node, *g_variable_tail_node;

void createConstantNode()
{
    g_constant_head_node =
        (ConstantTableNode *)malloc(sizeof(ConstantTableNode));
    g_constant_head_node->constant =
        (ConstantTable *)malloc(sizeof(ConstantTable));
    
    g_constant_tail_node = g_constant_head_node;

    g_constant_head_node->constant->type = 0;
    g_constant_head_node->constant->value = NULL;
    g_constant_head_node->index = 0;
    g_constant_head_node->next  = NULL;
}

void createVariableNode()
{
    g_variable_head_node =
        (VariableTableNode *)malloc(sizeof(VariableTableNode));
    g_variable_head_node->variable =
        (VariableTable *)malloc(sizeof(VariableTable));

    g_variable_tail_node = g_variable_head_node;

    g_variable_head_node->variable->type  = 0;
    g_variable_head_node->variable->flag  = 0;
    g_variable_head_node->variable->value = NULL;
    g_variable_head_node->variable->name  = NULL;
    g_variable_head_node->index           = 0;
    g_variable_head_node->next            = NULL;
}

void printAllConstantNode()
{
    char *constant_type;
    ConstantTableNode *constant_temp_node;
    constant_temp_node = g_constant_head_node;

    printf("============================================================\n");
    printf("                    Constant Symbol Table                   \n");
    printf("============================================================\n");
    printf("[index]          [element's type]          [element's value]\n");

    while ((constant_temp_node = constant_temp_node->next) != NULL) {
        if (constant_temp_node->constant->type == TYPE_INTEGER) {
            constant_type = "integer";
        }
        else if (constant_temp_node->constant->type == TYPE_REAL) {
            constant_type = "real";
        }
        else if (constant_temp_node->constant->type == TYPE_CHAR) {
            constant_type = "char";
        }
        else if (constant_temp_node->constant->type == TYPE_STRING) {
            constant_type = "string";
        }
        else if (constant_temp_node->constant->type == TYPE_BOOLEAN) {
            constant_type = "boolean";
        }
        printf("%-7d          %-16s          %-17s\n",
            constant_temp_node->index, constant_type,
            constant_temp_node->constant->value);
    }
}

void printAllVariableNode()
{
    char *variable_type;
    char *variable_flag;
    VariableTableNode *variable_temp_node;
    variable_temp_node = g_variable_head_node;

    printf("============================================================\n");
    printf("                    Variable Symbol Table                   \n");
    printf("============================================================\n");
    printf("[index] [variable's type] [element's type] [element's value]\n");

    while ((variable_temp_node = variable_temp_node->next) != NULL) {
        if (variable_temp_node->variable->type == TYPE_INTEGER) {
            variable_type = "integer";
        }
        else if (variable_temp_node->variable->type == TYPE_REAL) {
            variable_type = "real";
        }
        else if (variable_temp_node->variable->type == TYPE_CHAR) {
            variable_type = "char";
        }
        else if (variable_temp_node->variable->type == TYPE_STRING) {
            variable_type = "string";
        }
        else if (variable_temp_node->variable->type == TYPE_BOOLEAN) {
            variable_type = "boolean";
        }
        if (variable_temp_node->variable->flag == VARIABLE_USER) {
            variable_flag = "user";
        }
        else if (variable_temp_node->variable->flag == VARIABLE_TEMP) {
            variable_flag = "temp";
        }
        printf("%-7d %-17s %-16s %-17s\n", variable_temp_node->index,
            variable_flag, variable_type, variable_temp_node->variable->value);
    }
}

void ModifyConstantNodeValue(int index, char *value)
{
    ConstantTableNode *constant_temp_node;
    constant_temp_node = g_constant_head_node;

    while ((constant_temp_node = constant_temp_node->next) != NULL) {
        if (constant_temp_node->index == index) {
            constant_temp_node->constant->value = value;
        }
    }
}

void ModifyVariableNodeValue(int index, char *value)
{
    VariableTableNode *variable_temp_node;
    variable_temp_node = g_variable_head_node;

    while ((variable_temp_node = variable_temp_node->next) != NULL) {
        if (variable_temp_node->index == index) {
            variable_temp_node->variable->value = value;
        }
    }
}

void ModifySymbolNodeValue(int index, char *value)
{
    if (index > 0) {
        ModifyConstantNodeValue(index, value);
    }
    else {
        ModifyVariableNodeValue(index, value);
    }
}

void ModifyVariableNode(int index, int type, char *value)
{
    VariableTableNode *variable_temp_node;
    variable_temp_node = g_variable_head_node;

    while ((variable_temp_node = variable_temp_node->next) != NULL) {
        if (variable_temp_node->index == index) {
            variable_temp_node->variable->type = type;
            variable_temp_node->variable->value = value;
        }
    }
}

int generateConstantNode(int type, char *value)
{
    ConstantTableNode *constant_new_node;
    constant_new_node = 
        (ConstantTableNode *)malloc(sizeof(ConstantTableNode));
    constant_new_node->constant =
        (ConstantTable *)malloc(sizeof(ConstantTable));

    if (g_constant_head_node == NULL) {
        createConstantNode();
    }

    constant_new_node->constant->type  = type;
    constant_new_node->constant->value = value;
    constant_new_node->index           = g_constant_index;
    g_constant_tail_node->next         = constant_new_node;
    g_constant_tail_node               = constant_new_node;
    g_constant_tail_node->next         = NULL;

    g_constant_index++;

    return constant_new_node->index;
}

int generateVariableNode(int type, int flag, char *value, char *name)
{
    VariableTableNode *variable_new_node;
    variable_new_node = 
        (VariableTableNode *)malloc(sizeof(VariableTableNode));
    variable_new_node->variable =
        (VariableTable *)malloc(sizeof(VariableTable));

    if (g_variable_head_node == NULL) {
        createVariableNode();
    }

    variable_new_node->variable->type  = type;
    variable_new_node->variable->flag  = flag;
    variable_new_node->variable->value = value;
    variable_new_node->variable->name  = name;
    variable_new_node->index           = g_variable_index;
    g_variable_tail_node->next         = variable_new_node;
    g_variable_tail_node               = variable_new_node;
    g_variable_tail_node->next         = NULL;

    g_variable_index--;

    return variable_new_node->index;
}

int getConstantNodeType(int index)
{
    ConstantTableNode *constant_temp_node;
    constant_temp_node = g_constant_head_node;

    while ((constant_temp_node = constant_temp_node->next) != NULL) {
        if (constant_temp_node->index == index) {
            return constant_temp_node->constant->type;
        }
    }

    return 0;
}

int getVariableNodeType(int index)
{
    VariableTableNode *variable_temp_node;
    variable_temp_node = g_variable_head_node;

    while ((variable_temp_node = variable_temp_node->next) != NULL) {
        if (variable_temp_node->index == index) {
            return variable_temp_node->variable->type;
        }
    }

    return 0;
}

int getSymbolNodeType(int index)
{
    if (index > 0) {
        return getConstantNodeType(index);
    }
    else {
        return getVariableNodeType(index);
    }
}

char *getConstantNodeValue(int index)
{
    ConstantTableNode *constant_temp_node;
    constant_temp_node = g_constant_head_node;

    while ((constant_temp_node = constant_temp_node->next) != NULL) {
        if (constant_temp_node->index == index) {
            return constant_temp_node->constant->value;
        }
    }

    return NULL;
}

char *getVariableNodeValue(int index)
{
    VariableTableNode *variable_temp_node;
    variable_temp_node = g_variable_head_node;

    while ((variable_temp_node = variable_temp_node->next) != NULL) {
        if (variable_temp_node->index == index) {
            return variable_temp_node->variable->value;
        }
    }

    return NULL;
}

char *getSymbolNodeValue(int index)
{
    if (index > 0) {
        return getConstantNodeValue(index);
    }
    else {
        return getVariableNodeValue(index);
    }
}

ConstantTableNode *getConstantNode(int index)
{
    ConstantTableNode *constant_temp_node;
    constant_temp_node = g_constant_head_node;

    while ((constant_temp_node = constant_temp_node->next) != NULL) {
        if (constant_temp_node->index == index) {
            return constant_temp_node;
        }
    }

    return NULL;
}

VariableTableNode *getVariableNode(int index)
{
    VariableTableNode *variable_temp_node;
    variable_temp_node = g_variable_head_node;

    while ((variable_temp_node = variable_temp_node->next) != NULL) {
        if (variable_temp_node->index == index) {
            return variable_temp_node;
        }
    }

    return NULL;
}

void *getSymbolNode(int index)
{
    if (index > 0) {
        return getConstantNode(index);
    }
    else {
        return getVariableNode(index);
    }
}
