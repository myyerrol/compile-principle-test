#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "top_down_forecast_analysis.h"

void createLL1AnalysisMartix(LL1FirstFollowSet *p_ll1_first_follow_set)
{
    int  i, j, k;
    int  row = 0;
    int  col = 0;
    int  flag = 0;
    int  tail_len = 0;
    char head_char;
    char first_char;
    char follow_char;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 8; j++) {
            ll1_analysis_martix[i][j].production.head = '0';
            ll1_analysis_martix[i][j].production.tail_len = 0;
        }
    }

    for (i = 0; i < 12; i++) {
        tail_len  = p_ll1_first_follow_set[i].production.tail_len;
        head_char = p_ll1_first_follow_set[i].production.head;
        // Match the index of row in martix.
        if (head_char == 'E') {
            row = 0;
        }
        else if (head_char == 'B') {
            row = 1;
        }
        else if (head_char == 'T') {
            row = 2;
        }
        else if (head_char == 'C') {
            row = 3;
        }
        else if (head_char == 'F') {
            row = 4;
        }
        else if (head_char == 'A') {
            row = 5;
        }
        else if (head_char == 'M') {
            row = 6;
        }
        for (j = 0; j < p_ll1_first_follow_set[i].first_len; j++) {
            first_char  = p_ll1_first_follow_set[i].first[j];
            // Match the index of col in martix.
            if (first_char != 'e') {
                if (first_char == 'i') {
                    col = 0;
                }
                else if (first_char == '+') {
                    col = 1;
                }
                else if (first_char == '-') {
                    col = 2;
                }
                else if (first_char == '*') {
                    col = 3;
                }
                else if (first_char == '/') {
                    col = 4;
                }
                else if (first_char == '(') {
                    col = 5;
                }
                else if (first_char == ')') {
                    col = 6;
                }
                else if (first_char == '#') {
                    col = 7;
                }
                // Copy production to martix.
                ll1_analysis_martix[row][col].production.head =
                    p_ll1_first_follow_set[i].production.head;
                ll1_analysis_martix[row][col].production.tail_len = tail_len;
                for (k = 0; k < tail_len; k++) {
                    ll1_analysis_martix[row][col].production.tail[k] =
                    p_ll1_first_follow_set[i].production.tail[k];
                }
            }
            else {
                for (j = 0; j < p_ll1_first_follow_set[i].follow_len; j++) {
                    follow_char = p_ll1_first_follow_set[i].follow[j];
                    if (follow_char == 'i') {
                        col = 0;
                    }
                    else if (follow_char == '+') {
                        col = 1;
                    }
                    else if (follow_char == '-') {
                        col = 2;
                    }
                    else if (follow_char == '*') {
                        col = 3;
                    }
                    else if (follow_char == '/') {
                        col = 4;
                    }
                    else if (follow_char == '(') {
                        col = 5;
                    }
                    else if (follow_char == ')') {
                        col = 6;
                    }
                    else if (follow_char == '#') {
                        col = 7;
                    }
                    ll1_analysis_martix[row][col].production.head =
                        p_ll1_first_follow_set[i].production.head;
                    ll1_analysis_martix[row][col].production.tail_len =
                        tail_len;
                    for (k = 0; k < tail_len; k++) {
                        ll1_analysis_martix[row][col].production.tail[k] =
                            p_ll1_first_follow_set[i].production.tail[k];
                    }
                }
            }
        }
    }
}

void createLL1AnalysisStack(LL1AnalysisStackList *p_head_stack_list)
{
    int i;
    char ch[2] = {'#', 'E'};

    LL1AnalysisStackList p_new_stack_list;
    *p_head_stack_list =
        (LL1AnalysisStackList)malloc(sizeof(LL1AnalysisStackNode));
    (*p_head_stack_list)->next = NULL;

    for (i = 0; i < 2; i++) {
        p_new_stack_list =
            (LL1AnalysisStackList)malloc(sizeof(LL1AnalysisStackNode));
        p_new_stack_list->ch = ch[i];
        p_new_stack_list->next = (*p_head_stack_list)->next;
        (*p_head_stack_list)->next = p_new_stack_list;
    }
}

void pushToLL1AnalysisStack(LL1AnalysisStackList *p_head_stack_list, char ch)
{
    LL1AnalysisStackList p_new_stack_list;
    p_new_stack_list =
        (LL1AnalysisStackList)malloc(sizeof(LL1AnalysisStackNode));

    p_new_stack_list->ch = ch;
    p_new_stack_list->next = (*p_head_stack_list)->next;
    (*p_head_stack_list)->next = p_new_stack_list;
}

void popFromAnalysisStack(LL1AnalysisStackList *p_head_stack_list)
{
    LL1AnalysisStackList p_kill_stack_list;

    p_kill_stack_list = (*p_head_stack_list)->next;
    (*p_head_stack_list)->next = (*p_head_stack_list)->next->next;
    free(p_kill_stack_list);
}

void printAnalysisStack(LL1AnalysisStackList *p_head_stack_list)
{
    int  i, j = 0;
    int  count = 0;
    char ch_forward[SIZE];
    char ch_traverse[SIZE];

    LL1AnalysisStackList p_search_stack_list;
    p_search_stack_list = (*p_head_stack_list)->next;

    while (p_search_stack_list != NULL) {
        ch_forward[count] = p_search_stack_list->ch;
        p_search_stack_list = p_search_stack_list->next;
        count++;
    }

    for (i = count - 1; i >= 0; i--) {
        ch_traverse[j] = ch_forward[i];
        j++;
    }

    ch_traverse[j] = '\0';
    printf("%-16s  ", ch_traverse);
}

void analysizeInputChar(char *curr_char)
{
    int  i;
    int  row = 0;
    int  col = 0;
    int  step = 0;
    int  tail_len = 0;
    int  tail_index = 0;
    char stack_top_char;

    LL1AnalysisStackList *p_head_stack_list;
    p_head_stack_list =
        (LL1AnalysisStackList *)malloc(sizeof(LL1AnalysisStackNode));

    createLL1AnalysisStack(p_head_stack_list);
    printf("[step]  [analysis stack]  [input string]  [production]\n");

    while (1) {
        step++;
        printf("%-6d  ", step);
        printAnalysisStack(p_head_stack_list);
        printf("%14s  ", curr_char);
        stack_top_char = (*p_head_stack_list)->next->ch;
        // Match one character of string successfully.
        if (stack_top_char == *curr_char) {
            // Match all characters of string successfully.
            if (stack_top_char == '#') {
                printf("Yes!\n");
                return ;
            }
            printf("\n");
            curr_char++;
            popFromAnalysisStack(p_head_stack_list);
        }
        else {
            if (stack_top_char == 'E') {
                row = 0;
            }
            else if (stack_top_char == 'B') {
                row = 1;
            }
            else if (stack_top_char == 'T') {
                row = 2;
            }
            else if (stack_top_char == 'C') {
                row = 3;
            }
            else if (stack_top_char == 'F') {
                row = 4;
            }
            else if (stack_top_char == 'A') {
                row = 5;
            }
            else if (stack_top_char == 'M') {
                row = 6;
            }
            if (*curr_char == 'i') {
                col = 0;
            }
            else if (*curr_char == '+') {
                col = 1;
            }
            else if (*curr_char == '-') {
                col = 2;
            }
            else if (*curr_char == '*') {
                col = 3;
            }
            else if (*curr_char == '/') {
                col = 4;
            }
            else if (*curr_char == '(') {
                col = 5;
            }
            else if (*curr_char == ')') {
                col = 6;
            }
            else if (*curr_char == '#') {
                col = 7;
            }
            // Exist the production in martix.
            if (ll1_analysis_martix[row][col].production.head != '0') {
                tail_len = ll1_analysis_martix[row][col].production.tail_len;
                printf("%c->", ll1_analysis_martix[row][col].production.head);
                for (i = 0; i < tail_len; i++) {
                    printf("%c",
                        ll1_analysis_martix[row][col].production.tail[i]);
                }
                printf("\n");
                // The production deduces empty set.
                if (ll1_analysis_martix[row][col].production.tail[0] == 'e') {
                    popFromAnalysisStack(p_head_stack_list);
                    continue ;
                }
                // Push all elements of the right hand of production to stack
                // in reverse order.
                tail_index = tail_len - 1;
                (*p_head_stack_list)->next->ch =
                    ll1_analysis_martix[row][col].production.tail[tail_index];
                for (i = tail_index - 1; i >= 0; i--) {
                    pushToLL1AnalysisStack(
                        p_head_stack_list,
                        ll1_analysis_martix[row][col].production.tail[i]);
                }
            }
            else {
                printf("No!\n");
                return ;
            }
        }
    }
}

int main(int argc, char **argv)
{
    LL1FirstFollowSet ll1_first_follow_set[12], *p_ll1_first_follow_set;
    p_ll1_first_follow_set = ll1_first_follow_set;

    // Initialize the first and follow set of production.
    p_ll1_first_follow_set[0].production.head = 'E';
    p_ll1_first_follow_set[0].production.tail[0] = 'T';
    p_ll1_first_follow_set[0].production.tail[1] = 'B';
    p_ll1_first_follow_set[0].production.tail_len = 2;
    p_ll1_first_follow_set[0].first[0] = '(';
    p_ll1_first_follow_set[0].first[1] = 'i';
    p_ll1_first_follow_set[0].follow[0] = ')';
    p_ll1_first_follow_set[0].follow[1] = '#';
    p_ll1_first_follow_set[0].first_len = 2;
    p_ll1_first_follow_set[0].follow_len = 2;

    p_ll1_first_follow_set[1].production.head = 'B';
    p_ll1_first_follow_set[1].production.tail[0] = 'A';
    p_ll1_first_follow_set[1].production.tail[1] = 'T';
    p_ll1_first_follow_set[1].production.tail[2] = 'B';
    p_ll1_first_follow_set[1].production.tail_len = 3;
    p_ll1_first_follow_set[1].first[0] = '+';
    p_ll1_first_follow_set[1].first[1] = '-';
    p_ll1_first_follow_set[1].follow[0] = ')';
    p_ll1_first_follow_set[1].follow[1] = '#';
    p_ll1_first_follow_set[1].first_len = 2;
    p_ll1_first_follow_set[1].follow_len = 2;

    p_ll1_first_follow_set[2].production.head = 'B';
    p_ll1_first_follow_set[2].production.tail[0] = 'e';
    p_ll1_first_follow_set[2].production.tail_len = 1;
    p_ll1_first_follow_set[2].first[0] = 'e';
    p_ll1_first_follow_set[2].follow[0] = ')';
    p_ll1_first_follow_set[2].follow[1] = '#';
    p_ll1_first_follow_set[2].first_len = 1;
    p_ll1_first_follow_set[2].follow_len = 2;

    p_ll1_first_follow_set[3].production.head = 'T';
    p_ll1_first_follow_set[3].production.tail[0] = 'F';
    p_ll1_first_follow_set[3].production.tail[1] = 'C';
    p_ll1_first_follow_set[3].production.tail_len = 2;
    p_ll1_first_follow_set[3].first[0] = '(';
    p_ll1_first_follow_set[3].first[1] = 'i';
    p_ll1_first_follow_set[3].follow[0] = '+';
    p_ll1_first_follow_set[3].follow[1] = '-';
    p_ll1_first_follow_set[3].follow[2] = ')';
    p_ll1_first_follow_set[3].follow[3] = '#';
    p_ll1_first_follow_set[3].first_len = 2;
    p_ll1_first_follow_set[3].follow_len = 4;

    p_ll1_first_follow_set[4].production.head = 'C';
    p_ll1_first_follow_set[4].production.tail[0] = 'M';
    p_ll1_first_follow_set[4].production.tail[1] = 'F';
    p_ll1_first_follow_set[4].production.tail[2] = 'C';
    p_ll1_first_follow_set[4].production.tail_len = 3;
    p_ll1_first_follow_set[4].first[0] = '*';
    p_ll1_first_follow_set[4].first[1] = '/';
    p_ll1_first_follow_set[4].follow[0] = '+';
    p_ll1_first_follow_set[4].follow[1] = '-';
    p_ll1_first_follow_set[4].follow[2] = ')';
    p_ll1_first_follow_set[4].follow[3] = '#';
    p_ll1_first_follow_set[4].first_len = 2;
    p_ll1_first_follow_set[4].follow_len = 4;

    p_ll1_first_follow_set[5].production.head = 'C';
    p_ll1_first_follow_set[5].production.tail[0] = 'e';
    p_ll1_first_follow_set[5].production.tail_len = 1;
    p_ll1_first_follow_set[5].first[0] = 'e';
    p_ll1_first_follow_set[5].follow[0] = '+';
    p_ll1_first_follow_set[5].follow[1] = '-';
    p_ll1_first_follow_set[5].follow[2] = ')';
    p_ll1_first_follow_set[5].follow[3] = '#';
    p_ll1_first_follow_set[5].first_len = 1;
    p_ll1_first_follow_set[5].follow_len = 4;

    p_ll1_first_follow_set[6].production.head = 'F';
    p_ll1_first_follow_set[6].production.tail[0] = '(';
    p_ll1_first_follow_set[6].production.tail[1] = 'E';
    p_ll1_first_follow_set[6].production.tail[2] = ')';
    p_ll1_first_follow_set[6].production.tail_len = 3;
    p_ll1_first_follow_set[6].first[0] = '(';
    p_ll1_first_follow_set[6].follow[0] = '+';
    p_ll1_first_follow_set[6].follow[1] = '-';
    p_ll1_first_follow_set[6].follow[2] = '*';
    p_ll1_first_follow_set[6].follow[3] = '/';
    p_ll1_first_follow_set[6].follow[4] = '*';
    p_ll1_first_follow_set[6].follow[5] = '#';
    p_ll1_first_follow_set[6].first_len = 1;
    p_ll1_first_follow_set[6].follow_len = 6;

    p_ll1_first_follow_set[7].production.head = 'F';
    p_ll1_first_follow_set[7].production.tail[0] = 'i';
    p_ll1_first_follow_set[7].production.tail_len = 1;
    p_ll1_first_follow_set[7].first[0] = 'i';
    p_ll1_first_follow_set[7].follow[0] = '+';
    p_ll1_first_follow_set[7].follow[1] = '-';
    p_ll1_first_follow_set[7].follow[2] = '*';
    p_ll1_first_follow_set[7].follow[3] = '/';
    p_ll1_first_follow_set[7].follow[4] = '*';
    p_ll1_first_follow_set[7].follow[5] = '#';
    p_ll1_first_follow_set[7].first_len = 1;
    p_ll1_first_follow_set[7].follow_len = 6;

    p_ll1_first_follow_set[8].production.head = 'A';
    p_ll1_first_follow_set[8].production.tail[0] = '+';
    p_ll1_first_follow_set[8].production.tail_len = 1;
    p_ll1_first_follow_set[8].first[0] = '+';
    p_ll1_first_follow_set[8].follow[0] = '(';
    p_ll1_first_follow_set[8].follow[1] = 'i';
    p_ll1_first_follow_set[8].first_len = 1;
    p_ll1_first_follow_set[8].follow_len = 2;

    p_ll1_first_follow_set[9].production.head = 'A';
    p_ll1_first_follow_set[9].production.tail[0] = '-';
    p_ll1_first_follow_set[9].production.tail_len = 1;
    p_ll1_first_follow_set[9].first[0] = '-';
    p_ll1_first_follow_set[9].follow[0] = '(';
    p_ll1_first_follow_set[9].follow[1] = 'i';
    p_ll1_first_follow_set[9].first_len = 1;
    p_ll1_first_follow_set[9].follow_len = 2;

    p_ll1_first_follow_set[10].production.head = 'M';
    p_ll1_first_follow_set[10].production.tail[0] = '*';
    p_ll1_first_follow_set[10].production.tail_len = 1;
    p_ll1_first_follow_set[10].first[0] = '*';
    p_ll1_first_follow_set[10].follow[0] = '(';
    p_ll1_first_follow_set[10].follow[1] = '#';
    p_ll1_first_follow_set[10].first_len = 1;
    p_ll1_first_follow_set[10].follow_len = 2;

    p_ll1_first_follow_set[11].production.head = 'M';
    p_ll1_first_follow_set[11].production.tail[0] = '/';
    p_ll1_first_follow_set[11].production.tail_len = 1;
    p_ll1_first_follow_set[11].first[0] = '/';
    p_ll1_first_follow_set[11].follow[0] = '(';
    p_ll1_first_follow_set[11].follow[1] = '#';
    p_ll1_first_follow_set[11].first_len = 1;
    p_ll1_first_follow_set[11].follow_len = 2;

    if (argc < 3 || argc > 3) {
        printf("Error, please input arguments such as [xxx.txt i+i*i]\n");
        return -1;
    }

    createLL1AnalysisMartix(p_ll1_first_follow_set);
    analysizeInputChar(argv[2]);

    return 0;
}
