#ifndef PASCAL_HANDLE_QUATERNION_H
#define PASCAL_HANDLE_QUATERNION_H

#define OPCODE_ADD    500
#define OPCODE_SUB    501
#define OPCODE_MUL    502
#define OPCODE_DIV    503
#define OPCODE_MINUS  504
#define OPCODE_ASSIGN 505

typedef struct QuaternionTable {
    int  argument_a;
    int  argument_b;
    int  result;
    int  opcode;
} QuaternionTable;

typedef struct QuaternionTableNode {
    int                        index;
    struct QuaternionTable     *quaternion;
    struct QuaternionTableNode *next;
} QuaternionTableNode;

extern void createQuaternionNode(void);
extern void printAllQuaternionNode(void);
extern int generateQuaternionNode(int argument_a, int argument_b, int result,
                                  int opcode);
extern int getQuaternionNodeIndex(int argument_a, int argument_b, int result,
                                  int opcode);

#endif // PASCAL_HANDLE_QUATERNION_H
