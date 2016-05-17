#ifndef TOP_DOWN_FORECAST_ANALYSIS_H
#define TOP_DOWN_FORECAST_ANALYSIS_H

#define SIZE 10

typedef struct Production {
    char head;
    char tail[5];
    int  tail_len;
} Production;

typedef struct LL1FirstFollowSet {
    Production production;
    char       first[SIZE];
    char       follow[SIZE];
    int        first_len;
    int        follow_len;
} LL1FirstFollowSet;

typedef struct LL1AnalysisMartix {
    Production production;
} LL1AnalysisMartix;

typedef struct LL1AnalysisStack {
    char ch;
    struct LL1AnalysisStack *next;
} LL1AnalysisStackNode, *LL1AnalysisStackList;

LL1AnalysisMartix ll1_analysis_martix[7][8];

void createLL1AnalysisMartix(LL1FirstFollowSet *p_ll1_first_follow_set);
void createLL1AnalysisStack(LL1AnalysisStackList *p_head_stack_list);
void pushToLL1AnalysisStack(LL1AnalysisStackList *p_head_stack_list, char ch);
void popFromAnalysisStack(LL1AnalysisStackList *p_head_stack_list);
void printAnalysisStack(LL1AnalysisStackList *p_head_stack_list);
void analysizeInputChar(char *curr_char);

#endif // TOP_DOWN_FORECAST_ANALYSIS_H
