#ifndef CALCULATE_UNSIGNED_NUMBER_H
#define CALCULATE_UNSIGNED_NUMBER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define DIGIT  0
#define POINT  1
#define EXP    2
#define PLUS   3
#define MINUS  4
#define OTHER  5
#define ERROR  -1
#define END    7

// w: Mantissa accumulator
// p: Exponential accumulator
// n: Number of decimal digits counter
// e: Exponential symbol
// d: Input digit
struct DFAActionInfo {
    int w;
    int p;
    int n;
    int e;
    int d;
};

struct DFAActionState {
    int next_state;
    double (*dfa_action_handler)(struct DFAActionInfo *p_dfa_action_info);
};

struct DFAActionState *getDFAActionState(int curr_state, int curr_char);
double assignValuesA(struct DFAActionInfo *p_dfa_action_info);
double assignValuesB(struct DFAActionInfo *p_dfa_action_info);
double handleInteger(struct DFAActionInfo *p_dfa_action_info);
double handleDecimal(struct DFAActionInfo *p_dfa_action_info);
double handleExpSign(struct DFAActionInfo *p_dfa_action_info);
double handleExpNum(struct DFAActionInfo *p_dfa_action_info);
double returnInteger(struct DFAActionInfo *p_dfa_action_info);
double returnRealNum(struct DFAActionInfo *p_dfa_action_info);
double jumpToNextState(struct DFAActionInfo *p_dfa_action_info);
double recognizeError(struct DFAActionInfo *p_dfa_action_info);

// Row: State(0)~State(6)
// Column: '0~9', '.', 'E/e', '+', '-', other
// State(-1): Error, State(7): End
struct DFAActionState dfa_action_state[7][6] = {
    {{1, assignValuesA},   {3, assignValuesB},   {0, recognizeError},
     {-1, recognizeError}, {-1, recognizeError}, {-1, recognizeError}},
    {{1, handleInteger},   {2, jumpToNextState}, {4, jumpToNextState},
     {7, returnInteger},   {7, returnInteger},   {7, returnInteger}},
    {{2, handleDecimal},   {7, returnRealNum},   {4, jumpToNextState},
     {7, returnRealNum},   {7, returnRealNum},   {7, returnRealNum}},
    {{2, handleDecimal},   {-1, recognizeError}, {-1, recognizeError},
     {-1, recognizeError}, {-1, recognizeError}, {-1, recognizeError}},
    {{6, handleExpNum},    {-1, recognizeError}, {-1, recognizeError},
    {5, jumpToNextState},  {5, handleExpSign},   {-1, recognizeError}},
    {{6, handleExpNum},    {-1, recognizeError}, {-1, recognizeError},
     {-1, recognizeError}, {-1, recognizeError}, {-1, recognizeError}},
    {{6, handleExpNum},    {7, returnRealNum},   {7, returnRealNum},
     {7, returnRealNum},   {7, returnRealNum},   {7, returnRealNum}}
};

#endif
