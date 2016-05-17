#include "calculate_unsigned_number.h"

struct DFAActionState *getDFAActionState(int curr_state, int curr_char)
{
    return &dfa_action_state[curr_state][curr_char];
}

double assignValuesA(struct DFAActionInfo *p_dfa_action_info)
{
    p_dfa_action_info->n = 0;
    p_dfa_action_info->p = 0;
    p_dfa_action_info->e = 1;
    p_dfa_action_info->w = p_dfa_action_info->d;
    return 0;
}

double assignValuesB(struct DFAActionInfo *p_dfa_action_info)
{
    p_dfa_action_info->w = 0;
    p_dfa_action_info->n = 0;
    p_dfa_action_info->p = 0;
    p_dfa_action_info->e = 1;
    return 0;
}

double handleInteger(struct DFAActionInfo *p_dfa_action_info)
{
    p_dfa_action_info->w = p_dfa_action_info->w * 10 + p_dfa_action_info->d;
    return 0;
}

double handleDecimal(struct DFAActionInfo *p_dfa_action_info)
{
    (p_dfa_action_info->n)++;
    p_dfa_action_info->w = p_dfa_action_info->w * 10 + p_dfa_action_info->d;
    return 0;
}

double handleExpSign(struct DFAActionInfo *p_dfa_action_info)
{
    p_dfa_action_info->e = -1;
    return 0;
}

double handleExpNum(struct DFAActionInfo *p_dfa_action_info)
{
    p_dfa_action_info->p = p_dfa_action_info->p * 10 + p_dfa_action_info->d;
    return 0;
}

double returnInteger(struct DFAActionInfo *p_dfa_action_info)
{
    return p_dfa_action_info->w;
}

double returnRealNum(struct DFAActionInfo *p_dfa_action_info)
{
    return p_dfa_action_info->w * pow(10, p_dfa_action_info->e *
        p_dfa_action_info->p - p_dfa_action_info->n);
}

double recognizeError(struct DFAActionInfo *p_dfa_action_info)
{
    return -1;
}

double jumpToNextState(struct DFAActionInfo *p_dfa_action_info)
{
    return 0;
}

int main()
{
    int prev_state = 0;
    int curr_state = 0;
    int curr_char  = 0;
    int digit      = 0;
    double result  = 0;

    struct DFAActionState *p_dfa_action_state;
    struct DFAActionInfo  *p_dfa_action_info;
    p_dfa_action_state =
        (struct DFAActionState *)malloc(sizeof(struct DFAActionState));
    p_dfa_action_info  =
        (struct DFAActionInfo *)malloc(sizeof(struct DFAActionInfo));

    printf("Calucate Unsigned Number Test\n");

    while (1)
    {
        printf("Input unsigned number<q/Q: Quit>: ");
        while ((curr_char = getchar()) != EOF) {
            if (curr_char == 'q' || curr_char == 'Q') {
                exit(0);
            }
            else if (isdigit(curr_char)) {
                digit = curr_char - '0';
                p_dfa_action_info->d = digit;
                curr_char = DIGIT;
            }
            else if (curr_char == '.') {
                curr_char = POINT;
            }
            else if (curr_char == 'E' || curr_char == 'e') {
                curr_char = EXP;
            }
            else if (curr_char == '+') {
                curr_char = PLUS;
            }
            else if (curr_char == '-') {
                curr_char = MINUS;
            }
            else {
                curr_char = OTHER;
            }

            p_dfa_action_state = getDFAActionState(curr_state, curr_char);
            prev_state = curr_state;
            curr_state = p_dfa_action_state->next_state;
            result = p_dfa_action_state->dfa_action_handler(p_dfa_action_info);

            if (curr_state == ERROR) {
                curr_state = 0;
                printf("Error, recognize failed!\n");
                break;
            }
            else if (curr_state == END) {
                curr_state = 0;
                if (prev_state == 1) {
                    printf("Integer Number: %lf\n", result);
                }
                else {
                    printf("Real Number: %lf\n", result);
                }
                break;
            }
        }
    }

    return 0;
}
