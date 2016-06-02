#include <stdio.h>
#include <stdlib.h>
#include "pascal_handle_symbol_table.h"
#include "pascal_handle_quaternion.h"

int g_quaternion_index  = 1;
QuaternionTableNode *g_quaternion_head_node, *g_quaternion_tail_node;

void createQuaternionNode()
{
    g_quaternion_head_node = 
        (QuaternionTableNode *)malloc(sizeof(QuaternionTableNode));
    g_quaternion_head_node->quaternion = 
        (QuaternionTable *)malloc(sizeof(QuaternionTable));

    g_quaternion_tail_node = g_quaternion_head_node;

    g_quaternion_head_node->index                  = 0;
    g_quaternion_head_node->quaternion->argument_a = 0;
    g_quaternion_head_node->quaternion->argument_b = 0;
    g_quaternion_head_node->quaternion->opcode     = 0;
    g_quaternion_head_node->quaternion->result     = 0;
    g_quaternion_head_node->next = NULL;
}

int generateQuaternionNode(int argument_a, int argument_b, int result,
                           int opcode)
{
    QuaternionTableNode *quaternion_new_node;
    quaternion_new_node = 
        (QuaternionTableNode *)malloc(sizeof(QuaternionTableNode));
    quaternion_new_node->quaternion =
        (QuaternionTable *)malloc(sizeof(QuaternionTable));

    if (g_quaternion_head_node == NULL) {
        createQuaternionNode();
    }

    quaternion_new_node->index                  = g_quaternion_index;
    quaternion_new_node->quaternion->argument_a = argument_a;
    quaternion_new_node->quaternion->argument_b = argument_b;
    quaternion_new_node->quaternion->opcode     = opcode;
    quaternion_new_node->quaternion->result     = result;
    g_quaternion_tail_node->next                = quaternion_new_node;
    g_quaternion_tail_node                      = quaternion_new_node;
    g_quaternion_tail_node->next                = NULL;

    g_quaternion_index++;

    return quaternion_new_node->index;
}

int getQuaternionNodeIndex(int argument_a, int argument_b, int result,
                           int opcode)
{
    QuaternionTableNode *quaternion_temp_node;
    quaternion_temp_node = g_quaternion_head_node;

    while ((quaternion_temp_node = quaternion_temp_node->next) != NULL) {
        if (quaternion_temp_node->quaternion->argument_a == argument_a &&
            quaternion_temp_node->quaternion->argument_b == argument_b &&
            quaternion_temp_node->quaternion->result     == result     &&
            quaternion_temp_node->quaternion->opcode     == opcode) {
                return quaternion_temp_node->index;
        }
    }

    return 0;
}

void printAllQuaternionNode()
{
    char *argument_a, *argument_b, *result, *opcode;
    QuaternionTableNode *quaternion_temp_node;
    quaternion_temp_node = g_quaternion_head_node;

    printf("============================================================\n");
    printf("                      Quaternion Table                      \n");
    printf("============================================================\n");
    printf("[index]   [opcode]   [argument a]   [argument b]    [result]\n");

    while ((quaternion_temp_node = quaternion_temp_node->next) != NULL) {
        if (quaternion_temp_node->quaternion->argument_a > 0) {
            argument_a = getConstantNodeValue(
                quaternion_temp_node->quaternion->argument_a);
        }
        else {
            argument_a = getVariableNodeValue(
                quaternion_temp_node->quaternion->argument_a);
        }
        if (quaternion_temp_node->quaternion->argument_b > 0) {
            argument_b = getConstantNodeValue(
                quaternion_temp_node->quaternion->argument_b);
        }
        else {
            argument_b = getVariableNodeValue(
                quaternion_temp_node->quaternion->argument_b);
        }
        if (quaternion_temp_node->quaternion->result > 0) {
            result = getConstantNodeValue(
                quaternion_temp_node->quaternion->result);
        }
        else {
            result = getVariableNodeValue(
                quaternion_temp_node->quaternion->result);
        }
        if (quaternion_temp_node->quaternion->opcode == OPCODE_ADD) {
            opcode = "+";
        }
        else if (quaternion_temp_node->quaternion->opcode == OPCODE_SUB) {
            opcode = "-";
        }
        else if (quaternion_temp_node->quaternion->opcode == OPCODE_MUL) {
            opcode = "*";
        }
        else if (quaternion_temp_node->quaternion->opcode == OPCODE_DIV) {
            opcode = "/";
        }
        printf("%-7d   %-8s   %-12s   %-12s    %-8s\n",
            quaternion_temp_node->index, opcode, argument_a, argument_b,
            result);
    }
}
