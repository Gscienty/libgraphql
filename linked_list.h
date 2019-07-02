#ifndef _LIBGRAPHQL_LINKED_LIST_H
#define _LIBGRAPHQL_LINKED_LIST_H

typedef struct graphql_linked_list_s graphql_linked_list_t;
struct graphql_linked_list_s {
    graphql_linked_list_t *next;
    graphql_linked_list_t *prev;
};

#endif
