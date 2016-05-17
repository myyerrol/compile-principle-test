/**********************************************************************
* Copyright (C) 2011 RCDP Group HuaWei and NWPU China.
* All rights reserved.
*
* rcdp_state.c
* 定义rlink的状态机，
* 提供设置rlink状态机的函数
* 提供读取rlink状态机的函数
*
***********************************************************************/

#include "rcdp_include.h"

#define RCDP_MSG_PREFIX "State"

/* 主端rlink改变状态机的action */
static int g_p_action[RCDP_MAX_P_ACTION] =
{
        RCDP_ACTION_STOP,
        RCDP_ACTION_START_AUTOSYNC,
        RCDP_ACTION_START_SKIP,
        RCDP_ACTION_START_FAST,
        RCDP_ACTION_NET_ERR,
        RCDP_ACTION_NET_OK,
        RCDP_ACTION_LV_OVERFLOW,
        RCDP_ACTION_DONE
};

/* 主端rlink的状态列表 */
static int g_p_rlink_status[RCDP_MAX_P_RLINK_STATUS] =
{
        E_N_C,
        E_D_I,
        E_L_I,
        R_N_C,
        R_D_I,
        R_A_I,
        R_L_I,
        T_D_I,
        T_A_I,
        T_L_I,
        AE_D_I,
        AR_D_I,
        AT_D_I
};

/* 主端rlink的状态机 */
static int g_p_status_change[RCDP_MAX_P_RLINK_STATUS][RCDP_MAX_P_ACTION] =
{
        /*             STOP    START_AUTOSYN START_SKIP  START_FAST     NET_ERR    NET_OK      LV_OVERFLOW    DONE   */
        /*E_N_C  */  { E_N_C,    AR_D_I,     -1,           R_A_I,         -1,        -1,        -1,           -1     },
        /*E_D_I  */  { E_D_I,    AR_D_I,     -1,           R_D_I,         -1,        -1,        -1,           -1     },
        /*E_L_I  */  { E_L_I,    AR_D_I,     -1,           R_L_I,         -1,        -1,        -1,           -1     },
        /*R_N_C  */  { E_N_C,    -1,         -1,           -1,            T_A_I,     R_N_C,     R_D_I,        R_N_C  },
        /*R_D_I  */  { E_D_I,    -1,         -1,           -1,            T_D_I,     R_D_I,     R_D_I,        R_A_I  },
        /*R_A_I  */  { E_N_C,    -1,         -1,           -1,            T_A_I,     R_A_I,     R_D_I,        R_L_I  },
        /*R_L_I  */  { E_L_I,    -1,         -1,           -1,            T_L_I,     R_L_I,     R_D_I,        R_N_C  },
        /*T_D_I  */  { E_D_I,    -1,         -1,           -1,            T_D_I,     R_D_I,     -1,           -1     },
        /*T_A_I  */  { E_N_C,    -1,         -1,           -1,            T_A_I,     R_A_I,     -1,           -1     },
        /*T_L_I  */  { E_L_I,    -1,         -1,           -1,            T_L_I,     R_L_I,     -1,           -1     },
        /*AE_D_I */  { AE_D_I,   AR_D_I,     R_N_C,        AR_D_I,        -1,        -1,        -1,           -1     },
        /*AR_D_I */  { AE_D_I,   -1,         -1,           -1,            AT_D_I,    AR_D_I,    AR_D_I,       R_A_I  },
        /*AT_D_I */  { AE_D_I,   -1,         -1,           -1,            AT_D_I,    AR_D_I,    -1,           -1     }
};

/* 从端rlink改变状态机的action */
static int g_s_action[RCDP_MAX_S_ACTION] =
{
        RCDP_ACTION_START,
        RCDP_ACTION_START_DCM,
        RCDP_ACTION_START_ATOMIC,
        RCDP_ACTION_START_LV2DV,
        RCDP_ACTION_NET_ERR,
        RCDP_ACTION_DONE,
        RCDP_ACTION_CANCEL
};

/* 从端rlink的状态列表 */
static int  g_s_rlink_status[RCDP_MAX_S_RLINK_STATUS] =
{
        E_N_C,
        E_D_I,
        E_A_I,
        R_N_C,
        R_D_I,
        R_A_I,
        R_L_I
};

/* 从端rlink的状态机 */
static int g_s_status_change[RCDP_MAX_S_RLINK_STATUS][RCDP_MAX_S_ACTION] =
{
        /*              START    START_DCM  START_ATOMIC  START_LV2DV   NET_ERR   DONE     CANCEL */
        /*E_N_C*/  {    R_N_C,    -1,        -1,          -1,            -1,       -1,      -1      },
        /*E_D_I*/  {    R_N_C,    R_D_I,     -1,          -1,            -1,       -1,      -1      },
        /*E_A_I*/  {    -1,       R_D_I,     R_A_I,       -1,            -1,       -1,      -1      },
        /*R_N_C*/  {    -1,       R_D_I,     R_A_I,       -1,            E_N_C,    -1,      -1      },
        /*R_D_I*/  {    -1,       R_D_I,     R_A_I,       -1,            E_D_I,    -1,      R_N_C   },
        /*R_A_I*/  {    -1,       R_D_I,     -1,          R_L_I,         E_A_I,    -1,      R_N_C   },
        /*R_L_I*/  {    -1,       R_D_I,     -1,          -1,            -1,       R_N_C,   -1      },
};

/*****************************************************
* 功能：取得主端rlink当前状态机所在列表的行号
*
* 参数：
*     [IN]rlink：              rlink的状态机
*
* 返回值：
*     状态机行号
*
******************************************************/
static int rcdp_get_p_status_index(struct rcdp_rlink *rlink)
{
    int loop = 0;
    int status_val = 0;

    status_val = RCDP_STATUS2VAL(rlink->rlink_disk.dfa_status);
    for(loop = 0; loop < RCDP_MAX_P_RLINK_STATUS; loop++) {
        if (status_val == g_p_rlink_status[loop]) {
            return loop;
        }
    }
    return -1;
}

/*****************************************************
* 功能：取得从端rlink当前状态机所在列表的行号
*
* 参数：
*     [IN]rlink：              rlink的状态机
*
* 返回值：
*     状态机行号
*
******************************************************/
static int rcdp_get_s_status_index(struct rcdp_rlink *rlink)
{
    int loop = 0;
    int status_val = 0;

    status_val = RCDP_STATUS2VAL(rlink->rlink_disk.dfa_status);
    for (loop = 0; loop < RCDP_MAX_S_RLINK_STATUS; loop++) {
        if (status_val == g_s_rlink_status[loop]) {
            return loop;
        }
    }
    return -1;
}

/*****************************************************
* 功能：取得主端rlink当前状态机所在列表的列号
*
* 参数：
*     [IN]rlink：              rlink的状态机
*
* 返回值：
*     状态机列号
*
******************************************************/
static int rcdp_get_p_action_index (int action)
{
    int loop = 0;

    for(loop = 0; loop < RCDP_MAX_P_ACTION; loop++) {
        if(action == g_p_action[loop]) {
            return loop;
        }
    }
    return -1;
}

/*****************************************************
* 功能：取得从端rlink当前状态机所在列表的列号
*
* 参数：
*     [IN]rlink：              rlink的状态机
*
* 返回值：
*     状态机列号
*
******************************************************/
static int rcdp_get_s_action_index (int action)
{
    int loop = 0;

    for(loop = 0; loop < RCDP_MAX_S_ACTION; loop++) {
        if(action == g_s_action[loop]) {
            return loop;
        }
    }
    return -1;
}

/*****************************************************
* 功能：用index来强制设置rlink的状态机
*
* 参数：
*     [IN]rlink：              rlink的状态机
*     [IN]status_val： 状态机的index
*
* 返回值：
*     无
*
******************************************************/
static void rcdp_set_status_by_index (struct rcdp_rlink *rlink, int status_val)
{
	RCDP_VAL2STATUS(rlink->rlink_disk.dfa_status, status_val);
}

/*****************************************************
* 功能：用action来改变rlink的状态机
*
* 参数：
*     [IN]rlink：              rlink的状态机
*     [IN]action：           改变 状态机的action
*
* 返回值：
*     无
*
******************************************************/
void rcdp_change_rlink_status(struct rcdp_rlink *rlink, int action)
{
    int status = 0;
    int act = 0;
    int status_val = 0;

    if (RCDP_IS_RVG_ROLE_PRIMARY(rlink->rvg->rvg_disk.role)) {
        status = rcdp_get_p_status_index(rlink);
        act = rcdp_get_p_action_index(action);
        status_val = g_p_status_change[status][act];

    } else {
        status = rcdp_get_s_status_index(rlink);
        act = rcdp_get_s_action_index(action);
        status_val = g_s_status_change[status][act];
    }

    if (status_val < 0) {
    	RCDP_INFO("invalid status change");
        status_val = 0;
    }
    rcdp_set_status_by_index(rlink, status_val);

    rcdp_write_rlink_to_lv(rlink->rvg->lv, &rlink->rlink_disk);

    RCDP_INFO("change_status action is %d",action);
    RCDP_INFO("status is %d, %d, %d", rlink->rlink_disk.dfa_status.rlink_status,
    		rlink->rlink_disk.dfa_status.lv_status, rlink->rlink_disk.dfa_status.dv_status);
}

/*****************************************************
* 功能：判断rlink是否处于正常连接状态
*
* 参数：
*     [IN]rlink：              rlink的状态机
*
* 返回值：
*     1:正常连接
*     0:未连接
*
******************************************************/
int rcdp_is_rlink_connected(struct rcdp_rlink *rlink)
{
     return (rlink->rlink_disk.dfa_status.rlink_status == RCDP_STATUS_RLINK_RUN ||
             rlink->rlink_disk.dfa_status.rlink_status == RCDP_STATUS_RLINK_AUTOSYNC_RUN);
}
