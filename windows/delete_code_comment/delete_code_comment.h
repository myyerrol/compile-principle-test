#ifndef DELETE_CODE_COMMENT_H
#define DELETE_CODE_COMMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DFA State Transition Martix
// Row[0]: INITIAL_STATE
// Row[1]: MAYBE_START_COMMENT_STATE
// Row[2]: START_MULTI_COMMENT_STATE
// Row[3]: MAYBE_END_MULTI_COMMENT_STATE
// Row[4]: START_SINGLE_COMMENT_STAETE
// Row[5]: START_CHAR_STATE
// Row[6]: START_ESC_A_STATE
// Row[7]: START_STRING_STATE
// Row[8]: START_ESC_B_STATE
// Column[0]: /
// Column[1]: *
// Column[2]: /n
// Column[3]: '
// Column[4]: "
// Column[5]: \
// Column[6]: other
int dfa_state_transition[9][7] = {
    {1, 0, 0, 5, 7, 0, 0},
    {4, 2, 0, 0, 0, 0, 0},
    {2, 3, 2, 2, 2, 2, 2},
    {0, 2, 2, 2, 2, 2, 2},
    {4, 4, 0, 4, 4, 4, 4},
    {5, 5, 5, 0, 5, 6, 5},
    {5, 5, 5, 5, 5, 5, 5},
    {7, 7, 7, 7, 0, 8, 7},
    {7, 7, 7, 7, 7, 7, 7}
};

#endif
