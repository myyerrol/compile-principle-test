#include "simulate_nfa.h"

void backtrackNFA(int char_num_index, int char_num, int end_state,
                  int input_char[SIZE], int input_char_num, int curr_state,
                  char *curr_char, NFAStateMartix nfa_state_martix[SIZE][SIZE])
{
    int i;
    int col_index;
    int state_num;
    int flag = 0;

    if (*curr_char != NULL) {
        printf("%-14d %-15d %-13d %s\n", char_num_index, curr_state, end_state,
            curr_char);
    }
    else {
        printf("%-14d %-15d %-13d null\n", char_num_index, curr_state,
            end_state);
    }

    // The match is successful.
    if (char_num_index == char_num && curr_state == end_state) {
        printf("Yes\n");
        exit(0);
    }
    // The match is unsuccessful, backtrack to parent node.
    else if (char_num_index == char_num && curr_state != end_state) {
        return ;
    }
    // Don't arrive the leaf node, recurse to get there.
    else if (char_num_index < char_num) {
        for (i = 0; i < input_char_num; i++) {
            if (*curr_char == input_char[i]) {
                flag = 1;
                col_index = i;
                break ;
            }
        }
        // Input char don't exist in nfa.
        if (flag == 0) {
            printf("No\n");
            exit(0);
        }
        state_num = nfa_state_martix[curr_state][col_index].state_num;
        if (state_num == 0) {
            // There is no way to go at the root(start) node.
            if (char_num_index == 0) {
                printf("No\n");
                exit(0);
            }
            // Backtrack to parent node.
            else {
                return ;
            }
        }
        else {
            for (i = 0; i < state_num; i++) {
                curr_state = nfa_state_martix[curr_state][col_index].state[i];
                backtrackNFA(char_num_index + 1, char_num, end_state,
                             input_char, input_char_num, curr_state,
                             curr_char + 1, nfa_state_martix);
            }
        }
    }
    // Traverse all conditions, but there is not a solution.
    if (char_num_index == 0) {
        printf("No\n");
        exit(0);
    }
}

int main(int argc, char **argv)
{
    FILE *input_file;
    int ch;
    int i;
    int j;
    int flag = 0;
    int state_char[SIZE];
    int input_char[SIZE];
    int end_char[SIZE];
    int state_char_num = 0;
    int input_char_num = 0;
    int end_char_num   = 0;
    int start_char;
    int row_index;
    int col_index;
    int state_index;
    int state_num;
    NFAStateMartix nfa_state_martix[SIZE][SIZE];

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            nfa_state_martix[i][j].state_num = 0;
        }
    }

    i = 0;

    if (argc == 3) {
        if ((fopen_s(&input_file, argv[1], "r")) != 0) {
            perror(argv[1]);
            return 0;
        }
    }
    else {
        printf("Please input: simulate_nfa test.txt string\n");
        return 0;
    }

    while ((ch = fgetc(input_file)) != '\n') {
        if (ch == '{') {
            flag++;
        }
        if (ch == '}') {
            i = 0;
        }
        if (ch >= 'A' && ch <= 'Z') {
            if (flag == 1) {
                state_char[i] = ch;
                state_char_num++;
                i++;
            }
            else if (flag == 2) {
                start_char = ch;
            }
            else if (flag == 3) {
                end_char[i] = ch;
                end_char_num++;
                i++;
            }
        }
        if (ch >= 'a' && ch <= 'z' && ch != 'f') {
            input_char[i] = ch;
            input_char_num++;
            i++;
        }
    }

    while ((ch = fgetc(input_file)) != EOF) {
        if (ch != '\n') {
            if (ch == '=') {
                flag = 0;
            }
            if (ch >= 'A' && ch <= 'Z') {
                if (flag == 0) {
                    for (i = 0; i < state_char_num; i++) {
                        if (ch == state_char[i]) {
                            state_index = i;
                            break ;
                        }
                    }
                }
                else {
                    for (i = 0; i < state_char_num; i++) {
                        if (ch == state_char[i]) {
                            row_index = i;
                            break ;
                        }
                    }
                }
            }
            if (ch >= 'a' && ch <= 'z' && ch != 'f') {
                for (i = 0; i < input_char_num; i++) {
                    if (ch == input_char[i]) {
                        col_index = i;
                        break ;
                    }
                }
            }
        }
        else {
            state_num = nfa_state_martix[row_index][col_index].state_num;
            nfa_state_martix[row_index][col_index].state[state_num] = state_index;
            nfa_state_martix[row_index][col_index].state_num++;
            row_index = 0;
            col_index = 0;
            flag = 1;
        }
    }

    for (i = 0; i < end_char_num; i++) {
        for (j = 0; j < state_char_num; j++) {
            if (end_char[i] == state_char[j]) {
                printf("[char's index] [current state] [final state] [remaining char]\n");
                backtrackNFA(0, strlen(argv[2]), j, input_char, input_char_num, 0,
                             argv[2], nfa_state_martix);
            }
        }
    }

    return 0;
}
