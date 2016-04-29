#include <stdlib.h>
#include <stdio.h>
#include "delete_useless_production.h"

void inputGrammar(struct Grammar *pointer)
{
    int i;
    char ch;

    printf("Input Vn's length: ");
    scanf("%d", &(pointer->vn_len));

    if (pointer->vn_len > size) {
        printf("Error, Vn's length  greater than %d!", size);
        exit(0);
    }

    setbuf(stdin, NULL);

    printf("Input Vn's data(Don't use whitespace!): ");
    for (i = 0; i < pointer->vn_len; i++) {
        scanf("%c", &(pointer->vn[i]));
    }

    printf("Input Vt's length: ");
    scanf("%d", &(pointer->vt_len));

    if (pointer->vt_len > size) {
        printf("Error, Vt's length  greater than %d!", size);
        exit(0);
    }

    setbuf(stdin, NULL);

    printf("Input Vt's data(Don't use whitespace!): ");
    for (i = 0; i < pointer->vt_len; i++) {
        scanf("%c", &(pointer->vt[i]));
    }

    printf("Input P's number: ");
    scanf("%d", &(pointer->production_num));

    if (pointer->production_num > size) {
        printf("Error, Production's length  greater than %d!", size);
        exit(0);
    }

    printf("Input P's data:");
    for (i = 0; i < pointer->production_num; i++) {
        setbuf(stdin, NULL);
        pointer->production[i].tail_len = 0;
        setbuf(stdin, NULL);

        printf("\nProduction[%d] express(!such as S:=aS):\n", i);
        ch = getchar();
        pointer->production[i].head[0] = ch;
        printf("<%c>", ch);

        while ((ch = getchar()) != '\n') {
            if (ch != ':' && ch != '=') {
                printf("<%c>", ch);
                pointer->production[i].tail[pointer->production[i].tail_len] = ch;
                pointer->production[i].tail_len++;
            }
            else {
                printf("%c", ch);
                continue;
            }
        }
    }

    printf("\nInput S: ");
    scanf("%c", &(pointer->s));
    printf("\n");
    getchar();

    return ;
}

void displayGrammar(struct Grammar *pointer, int grammar_flag)
{
    int i, j;

    printf("G%d[Vn, Vt, P, S]", grammar_flag);

    printf("\nVn: ");
    for (i = 0; i < pointer->vn_len; i++) {
        printf("%c ", pointer->vn[i]);
    }

    printf("\nVt: ");
    for (i = 0; i < pointer->vt_len; i++) {
        printf("%c ", pointer->vt[i]);
    }

    printf("\nP: ");
    for (i = 0; i < pointer->production_num; i++) {
        printf("%c->", pointer->production[i].head[0]);
        for (j = 0; j < pointer->production[i].tail_len; j++) {
            printf("%c", pointer->production[i].tail[j]);
        }
        printf(" ");
    }

    printf("\nS: ");
    printf("%c\n\n", pointer->s);

    return ;
}

void deleteUselessGrammar1(struct Grammar *pointer, struct Grammar *pointer1)
{
    int i, j, k;
    int flag, flag1, flag2;

    // Initialize grammar1's data
    pointer1->s = pointer->s = 'S';

    for (i = 0; i < pointer->vt_len; i++) {
        pointer1->vt[i] = pointer->vt[i];
    }

    pointer1->vn_len = 0;
    pointer1->vt_len = 3;
    pointer1->production_num = 0;

    // Match all terminal symbols on the right hand side of productions
    // and move vn and productions to grammar1
    for (i = 0; i < pointer->production_num; i++) {
        for (j = 0; j < pointer->production[i].tail_len; j++) {
            for (k = 0; k < pointer->vt_len; k++) {
                // Match all lower case characters
                if (pointer->production[i].tail[j] == pointer->vt[k]) {
                    flag = 1;
                    break;
                }
                else {
                    flag = 0;
                }
            }
            if (flag == 0) {
                break;
            }
        }
        // Match successfully
        if (flag == 1) {
            for (k = 0; k < pointer1->vn_len; k++) {
                if (pointer->production[i].head[0] == pointer1->vn[k]) {
                    flag = 0;
                    break;
                }
                else {
                    flag = 1;
                }
            }
            // Add vn and productions to grammar1 without repetition
            if (flag == 1) {
                pointer1->vn[pointer1->vn_len] = pointer->production[i].head[0];
                pointer1->vn_len++;

                pointer1->production[pointer1->production_num].head[0] =
                    pointer->production[i].head[0];

                for (k = 0; k < pointer->production[i].tail_len; k++) {
                    pointer1->production[pointer1->production_num].tail[k] =
                        pointer->production[i].tail[k];
                    pointer1->production[pointer1->production_num].tail_len =
                        pointer->production[i].tail_len;
                }
                pointer1->production_num++;
                pointer->production[i].choose_flag = 1;
            }
        }
    }

    // Match all terminal or noterminal symbols on the right hand side of
    // productions and move the rest vn and productions to grammar1
    for (i = 0; i < pointer->production_num; i++) {
        if (pointer->production[i].choose_flag == 1) {
            continue;
        }
        for (j = 0; j < pointer->production[i].tail_len; j++) {
            for (k = 0; k < pointer->vt_len; k++) {
                if (pointer->production[i].tail[j] == pointer->vt[k]) {
                    flag  = 1;
                    flag1 = 0;
                    break;
                }
                else {
                    flag  = 0;
                    flag1 = 0;
                }
            }
            if (flag == 0) {
                for (k = 0; k < pointer1->vn_len; k++) {
                    if (pointer->production[i].tail[j] == pointer1->vn[k]) {
                        flag1 = 1;
                        break;
                    }
                    else {
                        flag1 = 0;
                    }
                }
            }
            if ((flag == 0) && (flag1 == 0)) {
                break;
            }
        }
        if ((flag || flag1) == 1) {
            for (k = 0; k < pointer1->vn_len; k++) {
                if (pointer->production[i].head[0] == pointer1->vn[k]) {
                    flag = 0;
                    break;
                }
                else {
                    flag = 1;
                }
            }
            if (flag == 1) {
                pointer1->vn[pointer1->vn_len] = pointer->production[i].head[0];
                pointer1->vn_len++;
            }

            pointer1->production[pointer1->production_num].head[0] =
                pointer->production[i].head[0];

            for (k = 0; k < pointer->production[i].tail_len; k++) {
                pointer1->production[pointer1->production_num].tail[k] =
                    pointer->production[i].tail[k];
                pointer1->production[pointer1->production_num].tail_len =
                    pointer->production[i].tail_len;
            }
            pointer1->production_num++;
            pointer->production[i].choose_flag = 1;
        }
    }

    // Match all terminal or noterminal symbols on the left or right hand side
    // of productions and move the rest vn and productions to grammar1
    for (i = 0; i < pointer->production_num; i++) {
        if (pointer->production[i].choose_flag == 1) {
            continue;
        }
        for (j = 0; j < pointer->production[i].tail_len; j++) {
            for (k = 0; k < pointer->vt_len; k++) {
                if (pointer->production[i].tail[j] == pointer->vt[k]) {
                    flag  = 1;
                    flag1 = 0;
                    break;
                }
                else {
                    flag  = 0;
                    flag1 = 0;
                }
            }
            if (flag == 0) {
                for (k = 0; k < pointer1->vn_len; k++) {
                    if (pointer->production[i].tail[j] == pointer1->vn[k]) {
                        flag1 = 1;
                        break;
                    }
                    else {
                        flag1 = 0;
                    }
                }
            }
            if ((flag == 0) && (flag1 == 0)) {
                break;
            }
            if ((flag || flag1) == 1) {
                for (k = 0; k < pointer1->vn_len; k++) {
                    if (pointer->production[i].head[0] == pointer1->vn[k]) {
                        flag2 = 1;
                        break;
                    }
                    else {
                        flag2 = 0;
                    }
                }
            }
        }
        if ((flag || flag1) && (flag2) == 1) {
            for (k = 0; k < pointer1->vn_len; k++) {
                if (pointer->production[i].head[0] == pointer1->vn[k]) {
                    flag = 0;
                    break;
                }
                else {
                    flag = 1;
                }
            }
            if (flag == 1) {
                pointer1->vn[pointer1->vn_len] = pointer->production[i].head[0];
                pointer1->vn_len++;
            }

            pointer1->production[pointer1->production_num].head[0] =
                pointer->production[i].head[0];

            for (k = 0; k < pointer->production[i].tail_len; k++) {
                pointer1->production[pointer1->production_num].tail[k] =
                    pointer->production[i].tail[k];
                pointer1->production[pointer1->production_num].tail_len =
                    pointer->production[i].tail_len;
            }
            pointer1->production_num++;
            pointer->production[i].choose_flag = 1;
        }
    }

    displayGrammar(pointer1, 1);

    return ;
}

void deleteUselessGrammar2(struct Grammar *pointer1, struct Grammar *pointer2)
{
    int i, j, k;
    int flag, flag1, flag2, flag3;

    // Initialize grammar2's data
    pointer2->vn_len = 0;
    pointer2->vt_len = 0;
    pointer2->production_num = 0;

    pointer2->s = pointer1->s;
    pointer2->vn[0] = pointer1->s;
    pointer2->vn_len = 1;

    // Match the left hand side of productions and move the right hand side of
    // productions to grammar2's vn or vt, and also move productions itself to
    // grammar2
    for (i = 0; i < pointer1->production_num; i++) {
        for (j = 0; j < pointer2->vn_len; j++) {
            if (pointer1->production[i].head[0] == pointer2->vn[j]) {
                flag = 1;
                break;
            }
            else {
                flag = 0;
            }
        }
        if (flag == 1) {
            for (j = 0; j < pointer1->production[i].tail_len; j++) {
                for (k = 0; k < pointer1->vt_len; k++) {
                    if (pointer1->production[i].tail[j] == pointer1->vt[k]) {
                        flag1 = 1;
                        flag2 = 0;
                        flag3 = 0;
                        break;
                    }
                    else {
                        flag1 = 0;
                        flag2 = 1;
                        flag3 = 0;
                    }
                }
                // Move the Lower case character to grammar2's vt
                if (flag1 == 1 && flag2 == 0) {
                    for (k = 0; k < pointer2->vt_len; k++) {
                        if (pointer1->production[i].tail[j] == pointer2->vt[k]) {
                            flag3 = 1;
                            break;
                        }
                        else {
                            flag3 = 0;
                        }
                    }
                    if (flag3 == 0) {
                        pointer2->vt[pointer2->vt_len] =
                            pointer1->production[i].tail[j];
                        pointer2->vt_len++;
                    }
                }
                // Move the capital character to grammar2's vn
                if (flag1 == 0 && flag2 == 1) {
                    for (k = 0; k < pointer2->vn_len; k++) {
                        if (pointer1->production[i].tail[j] == pointer2->vn[k]) {
                            flag3 = 1;
                            break;
                        }
                        else {
                            flag3 = 0;
                        }
                    }
                    if (flag3 == 0) {
                        pointer2->vn[pointer2->vn_len] =
                            pointer1->production[i].tail[j];
                        pointer2->vn_len++;
                    }
                }
            }
            pointer2->production[pointer2->production_num].head[0] =
                pointer1->production[i].head[0];

            for (k = 0; k < pointer1->production[i].tail_len; k++) {
                pointer2->production[pointer2->production_num].tail[k] =
                    pointer1->production[i].tail[k];
                pointer2->production[pointer2->production_num].tail_len =
                    pointer1->production[i].tail_len;
            }
            pointer2->production_num++;
            pointer1->production[i].choose_flag = 1;
        }
    }

    // Match the left or right hand side of productions on grammar2' vn and vt
    // and move the productions to grammar2
    for (i = 0; i < pointer1->production_num; i++) {
        if (pointer1->production[i].choose_flag == 1) {
            continue;
        }
        for (j = 0; j < pointer2->vn_len; j++) {
            if (pointer1->production[i].head[0] == pointer2->vn[j]) {
                flag = 1;
                break;
            }
            else {
                flag = 0;
            }
        }
        if (flag == 1) {
            for (j = 0; j < pointer1->production[i].tail_len; j++) {
                for (k = 0; k < pointer2->vt_len; k++) {
                    if (pointer1->production[i].tail[j] == pointer2->vt[k]) {
                        flag1 = 1;
                        flag2 = 0;
                        flag3 = 0;
                        break;
                    }
                    else {
                        flag1 = 0;
                        flag2 = 1;
                        flag3 = 0;
                    }
                }
                if (flag1 == 1 && flag2 == 0) {
                    for (k = 0; k < pointer2->vt_len; k++) {
                        if (pointer1->production[i].tail[j] == pointer2->vt[k]) {
                            flag3 = 1;
                            break;
                        }
                        else {
                            flag3 = 0;
                        }
                    }
                    if (flag3 == 0) {
                        pointer2->vt[pointer2->vt_len] = pointer1->production[i].tail[j];
                        pointer2->vt_len++;
                    }
                }
                if (flag1 == 0 && flag2 == 1) {
                    for (k = 0; k < pointer2->vn_len; k++) {
                        if (pointer1->production[i].tail[j] == pointer2->vn[k]) {
                            flag3 = 1;
                            break;
                        }
                        else {
                            flag3 = 0;
                        }
                    }
                    if (flag3 == 0) {
                        pointer2->vn[pointer2->vn_len] = pointer1->production[i].tail[j];
                        pointer2->vn_len++;
                    }
                }
            }
            pointer2->production[pointer2->production_num].head[0] =
                pointer1->production[i].head[0];

            for (k = 0; k < pointer1->production[i].tail_len; k++) {
                pointer2->production[pointer2->production_num].tail[k] =
                    pointer1->production[i].tail[k];
                pointer2->production[pointer2->production_num].tail_len =
                    pointer1->production[i].tail_len;
            }
            pointer2->production_num++;
            pointer1->production[i].choose_flag = 1;
        }
    }

    displayGrammar(pointer2, 2);

    return ;
}

int main()
{
    int i;

    struct Grammar *pointer;
    struct Grammar *pointer1;
    struct Grammar *pointer2;
    pointer  = (struct Grammar *)malloc(sizeof(struct Grammar));
    pointer1 = (struct Grammar *)malloc(sizeof(struct Grammar));
    pointer2 = (struct Grammar *)malloc(sizeof(struct Grammar));

    printf("Grammar[Vn, Vt, P, S] Test\n");

    printf("Input(1: Use built-in example 2: Input random grammar): ");
    scanf("%d", &i);

    if (i == 1) {
        // Initialize grammar's data
        pointer->vn_len = 4;
        pointer->vt_len = 3;
        pointer->production_num = 7;

        pointer->vn[0] = 'S';
        pointer->vn[1] = 'U';
        pointer->vn[2] = 'V';
        pointer->vn[3] = 'W';

        pointer->vt[0] = 'a';
        pointer->vt[1] = 'b';
        pointer->vt[2] = 'c';

        pointer->s = 'S';

        pointer->production[0].tail_len = 2;
        pointer->production[1].tail_len = 1;
        pointer->production[2].tail_len = 1;
        pointer->production[3].tail_len = 1;
        pointer->production[4].tail_len = 2;
        pointer->production[5].tail_len = 2;
        pointer->production[6].tail_len = 2;
        pointer->production[0].head[0] = 'S';
        pointer->production[0].tail[0] = 'a';
        pointer->production[0].tail[1] = 'S';
        pointer->production[1].head[0] = 'S';
        pointer->production[1].tail[0] = 'W';
        pointer->production[2].head[0] = 'S';
        pointer->production[2].tail[0] = 'U';
        pointer->production[3].head[0] = 'U';
        pointer->production[3].tail[0] = 'a';
        pointer->production[4].head[0] = 'V';
        pointer->production[4].tail[0] = 'b';
        pointer->production[4].tail[1] = 'V';
        pointer->production[5].head[0] = 'V';
        pointer->production[5].tail[0] = 'a';
        pointer->production[5].tail[1] = 'c';
        pointer->production[6].head[0] = 'W';
        pointer->production[6].tail[0] = 'a';
        pointer->production[6].tail[1] = 'W';

        for (i = 0; i < 7; i++) {
            pointer->production[i].choose_flag = 0;
        }
    }
    else if (i == 2) {
        inputGrammar(pointer);
    }
    else {
        printf("Error, choice is not within the specified range!");
        exit(0);
    }

    displayGrammar(pointer, 0);

    deleteUselessGrammar1(pointer, pointer1);
    deleteUselessGrammar2(pointer1, pointer2);

    return 0;
}
