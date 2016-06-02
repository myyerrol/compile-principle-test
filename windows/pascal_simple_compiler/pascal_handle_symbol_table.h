#ifndef PASCAL_HANDLE_SYMBOL_TABLE_H
#define PASCAL_HANDLE_SYMBOL_TABLE_H

#define TYPE_INTEGER   600
#define TYPE_REAL      601
#define TYPE_SINGLE    602
#define TYPE_DOUBLE    603
#define TYPE_CHAR      604
#define TYPE_STRING    605
#define TYPE_BOOLEAN   606
#define TYPE_NULL      607

#define VARIABLE_USER  650
#define VARIABLE_TEMP  651

typedef struct ConstantTable {
    int  type;
    char *value;
} ConstantTable;

typedef struct ConstantTableNode {
    int                      index;
    ConstantTable            *constant;
    struct ConstantTableNode *next;
} ConstantTableNode;

typedef struct VariableTable {
    int  type;
    int  flag;
    char *value;
    char *name;
} VariableTable;

typedef struct VariableTableNode {
    int                      index;
    VariableTable            *variable;
    struct VariableTableNode *next;
} VariableTableNode;

extern void createConstantNode(void);
extern void createVariableNode(void);
extern void printAllConstantNode(void);
extern void printAllVariableNode(void);
extern void ModifyConstantNodeValue(int index, char *value);
extern void ModifyVariableNodeValue(int index, char *value);
extern void ModifySymbolNodeValue(int index, char *value);
extern void ModifyVariableNode(int index, int type, char *value);
extern int generateConstantNode(int type, char *value);
extern int generateVariableNode(int type, int flag, char *value, char *name);
extern int getConstantNodeType(int index);
extern int getVariableNodeType(int index);
extern int getSymbolNodeType(int index);
extern char *getConstantNodeValue(int index);
extern char *getVariableNodeValue(int index);
extern char *getSymbolNodeValue(int index);

#endif // PASCAL_HANDLE_SYMBOL_TABLE_H
