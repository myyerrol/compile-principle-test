#include "delete_code_comment.h"

int main(int argc, char **argv)
{
    FILE *in_file;
    FILE *out_file;
    int  ch, flag;
    int  index = 0;
    int  state = 0;

    if ((argc < 3) || (argc == 4) || (argc > 5)) {
        printf("Error! Please input such as: %s -f xxx.c [-t yyy.c]\n", argv[0]);
        return 0;
    }
    else if (argc == 3) {
        if (strcmp(argv[1], "-f") == 0) {
            flag = 1;
            if ((fopen_s(&in_file, argv[2], "rb")) != 0) {
                perror(argv[2]);
                return 0;
            }
        }
        else {
            printf("Error! Please input -f instead of %s\n", argv[1]);
            return 0;
        }
    }
    else if (argc == 5) {
        if (strcmp(argv[1], "-f") == 0) {
            if (strcmp(argv[3], "-t") == 0) {
                if ((fopen_s(&in_file, argv[2], "rb")) != 0) {
                    perror(argv[2]);
                    return 0;
                }
                if ((fopen_s(&out_file, argv[4], "wb")) != 0) {
                    perror(argv[4]);
                    return 0;
                }
            }
            else {
                printf("Error! Please input-t instead of %s\n", argv[3]);
                return 0;
            }
        }
        else if (strcmp(argv[1], "-t") == 0) {
            if (strcmp(argv[3], "-f") == 0) {
                if ((fopen_s(&in_file, argv[4], "rb")) != 0) {
                    perror(argv[2]);
                    return 0;
                }
                if ((fopen_s(&out_file, argv[2], "wb")) != 0) {
                    perror(argv[4]);
                    return 0;
                }
            }
            else {
                printf("Error! Please input -f instead of %s\n", argv[3]);
                return 0;
            }
        }
        else {
            printf("Error! Please input -f/-t instead of %s\n", argv[1]);
            return 0;
        }
    }

    while ((ch = fgetc(in_file)) != EOF) {
        if (ch == '/') {
            index = 0;
        }
        else if (ch == '*') {
            index = 1;
        }
        else if (ch == '\n') {
            index = 2;
        }
        else if (ch == '\'') {
            index = 3;
        }
        else if (ch == '\"') {
            index = 4;
        }
        else if (ch == '\\') {
            index = 5;
        }
        else {
            index = 6;
        }

        state = dfa_state_transition[state][index];

        // According to comment's requirement, cut off some branchs of state
        // transition graph that are not meet the conditions.
        if ((state == 0 && ch != '/') ||
            (state == 1 && ch != '*' && ch != '/') ||
            (state == 5) || (state == 7) ||
            (state == 6) || (state == 8)) {
            if (flag == 1) {
                putchar(ch);
            }
            else if (flag == 2 || flag == 3) {
                fputc(ch, out_file);
            }
        }
    }

    if (flag == 1) {
        fclose(in_file);
    }
    else if (flag == 2 || flag == 3) {
        fclose(in_file);
        fclose(out_file);
    }

    return 0;
}
