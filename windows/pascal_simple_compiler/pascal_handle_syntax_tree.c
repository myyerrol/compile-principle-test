#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pascal_handle_syntax_tree.h"

void printAllAbstractSyntaxTreeNode(AbstractSyntaxTreeNode *ast_node)
{
    int count = SPACE_POSITION;
    AbstractSyntaxTreeNode *ast_temp_node;
    ast_temp_node = ast_node;

    printf("============================================================\n");
    printf("                    Abstract Syntax Tree                    \n");
    printf("============================================================\n");
    printf("");


    PRINT_SPACE(count);
    printf("%s\n", ast_temp_node->value);

    while (ast_temp_node->son != NULL) {
        ast_temp_node = ast_temp_node->son;
        count -= SPACE_HALF_LENGTH;
        PRINT_SPACE(count);
        printf("%s", ast_temp_node->value);
        ast_temp_node = ast_temp_node->brother;
        PRINT_SPACE(2 * SPACE_HALF_LENGTH);
        printf("%s\n",ast_temp_node->value);
        count += (2 * SPACE_HALF_LENGTH);
    }
}

int createSyntaxTreeNode(struct SyntaxTreeNode **st_node)
{
    if (st_node != NULL) {
        *st_node =
            (struct SyntaxTreeNode *)malloc(sizeof(struct SyntaxTreeNode));
        if (initSyntaxTreeNode(*st_node) == STATE_INIT_NODE_SUCCESS) {
            return STATE_CREATE_NODE_SUCCESS;
        }
        else {
            return STATE_ALLOCATE_MEMORY_ERROR;
        }
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

int initSyntaxTreeNode(struct SyntaxTreeNode *st_node)
{
    if (st_node != NULL) {
        st_node->type    = NODE_NULL;
        st_node->value   = NULL;
        st_node->parent  = NULL;
        st_node->son     = NULL;
        st_node->brother = NULL;
        return STATE_INIT_NODE_SUCCESS;
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

int setSyntaxTreeNode(struct SyntaxTreeNode *st_node, int type, char *value)
{
    if (st_node != NULL && value != NULL) {
        if (st_node->value != NULL) {
            free(st_node->value);
        }
        st_node->type  = type;
        st_node->value = (char *)malloc(strlen(value) + 1);
        strcpy(st_node->value, value);
        return STATE_SET_NODE_SUCCESS;
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

int addSyntaxTreeSonNode(struct SyntaxTreeNode *st_parent_node,
                         struct SyntaxTreeNode *st_son_node)
{
    if (st_parent_node != NULL && st_son_node != NULL) {
        if (st_parent_node->son == NULL) {
            st_parent_node->son = st_son_node;
        }
        else {
            struct SyntaxTreeNode *temp_node = st_parent_node->son;
            while (temp_node->brother != NULL) {
                temp_node = temp_node->brother;
            }
            temp_node->brother = st_son_node;
            st_son_node->parent = st_parent_node;
        }
        return STATE_ADD_SON_NODE_SUCCESS;
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

int addSyntaxTreeBrotherNode(struct SyntaxTreeNode *st_current_node,
                             struct SyntaxTreeNode *st_brother_node)
{
    if (st_current_node != NULL && st_brother_node != NULL) {
        struct SyntaxTreeNode *temp_node = NULL;
        if (st_current_node->parent == NULL) {
            return STATE_ADD_BROTHER_NODE_ERROR;
        }
        else {
            st_current_node->brother = st_brother_node;
            st_brother_node->parent = st_current_node->parent;
        }
        return STATE_ADD_BROTHER_NODE_SUCCESS;
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

int getSyntaxTreeSonNode(struct SyntaxTreeNode *st_parent_node, 
                         struct SyntaxTreeNode **st_son_node)
{
    if (st_parent_node != NULL && st_son_node != NULL) {
        *st_son_node = st_parent_node->son;
        return STATE_GET_SON_NODE_SUCCESS;
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

int getSyntaxTreeBrotherNode(struct SyntaxTreeNode *st_current_node,
                             struct SyntaxTreeNode **st_brother_node)
{
    if (st_current_node != NULL && st_brother_node != NULL) {
        *st_brother_node = st_current_node->brother;
        return STATE_GET_BROTHER_NODE_SUCCESS;
    }
    else {
        return STATE_NULL_NODE_POINTER;
    }
}

struct SyntaxTreeNode **createSyntaxTreeNodePointer()
{
    struct SyntaxTreeNode **st_node;
    st_node = (struct SyntaxTreeNode **)malloc(sizeof(struct SyntaxTreeNode));
    return st_node;
}

