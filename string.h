#ifndef _LIBGRAPHQL_STRING_H
#define _LIBGRAPHQL_STRING_H

typedef struct graphql_str_s graphql_str_t;
struct graphql_str_s {
    char *str;
    int len;
};

#endif
