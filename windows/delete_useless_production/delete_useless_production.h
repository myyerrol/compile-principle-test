#ifndef DELETE_USELESS_PRODUCTION_H_
#define DELETE_USELESS_PRODUCTION_H_

#define size 20

struct Production {
    char head[size];
    char tail[size];
    int  tail_len;
    int  choose_flag;
};

struct Grammar {
    char vn[size];
    char vt[size];
    char s;
    int  vn_len;
    int  vt_len;
    int  production_num;
    struct Production production[size];
};

#endif // DELETE_USELESS_PRODUCTION_H_
