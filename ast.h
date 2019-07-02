#ifndef _LIBGRAPHQL_AST_H
#define _LIBGRAPHQL_AST_H

#include "string.h"
#include "linked_list.h"

typedef struct graphql_ast_loc_s graphql_ast_loc_t;
struct graphql_ast_loc_s {
    int start;
    int end;
    const char *src;
};

typedef struct graphql_ast_node_s graphql_ast_node_t;
struct graphql_ast_node_s {
    graphql_linked_list_t lh;
    int kind;
    graphql_ast_loc_t loc;
};

typedef struct graphql_ast_name_s graphql_ast_name_t;
struct graphql_ast_name_s {
    graphql_ast_node_t node;
    graphql_str_t val;
};

typedef struct graphql_ast_value_s graphql_ast_value_t;
struct graphql_ast_value_s {
    graphql_ast_node_t node;
};

typedef struct graphql_ast_object_field_s graphql_ast_object_field_t;
struct graphql_ast_object_field_s {
    graphql_ast_node_t node;
    graphql_ast_name_t name;
    graphql_ast_value_t val;
};

typedef struct graphql_ast_variable_s graphql_ast_variable_t;
struct graphql_ast_variable_s {
    graphql_ast_value_t super;
    graphql_ast_name_t name;
};

typedef struct graphql_ast_int_value_s graphql_ast_int_value_t;
struct graphql_ast_int_value_s {
    graphql_ast_value_t super;
    graphql_str_t val;
};

typedef struct graphql_ast_float_value_s graphql_ast_float_value_t;
struct graphql_ast_float_value_s {
    graphql_ast_value_t super;
    graphql_str_t val;
};

typedef struct graphql_ast_string_value_s graphql_ast_string_value_t;
struct graphql_ast_string_value_s {
    graphql_ast_value_t super;
    graphql_str_t val;
};

typedef struct graphql_ast_bool_value_s graphql_ast_bool_value_t;
struct graphql_ast_bool_value_s {
    graphql_ast_value_t super;
    int val;
};

typedef struct graphql_ast_enum_value_s graphql_ast_enum_value_t;
struct graphql_ast_enum_value_s {
    graphql_ast_value_t super;
    graphql_str_t val;
};

typedef struct graphql_ast_list_value_s graphql_ast_list_value_t;
struct graphql_ast_list_value_s {
    graphql_ast_value_t super;
    graphql_linked_list_t val;
};

typedef struct graphql_ast_list_value_item_s graphql_ast_list_value_item_t;
struct graphql_ast_list_value_item_s {
    graphql_linked_list_t lh;
    graphql_ast_value_t val;
};

typedef struct graphql_ast_object_field_value_s graphql_ast_object_field_value_t;
struct graphql_ast_object_field_value_s {
    graphql_ast_value_t super;
    graphql_linked_list_t val;
};

typedef struct graphql_ast_object_field_value_item_s graphql_ast_object_field_value_item_t;
struct graphql_ast_object_field_value_item_s {
    graphql_linked_list_t lh;
    graphql_ast_object_field_t val;
};

typedef struct graphql_ast_arg_s graphql_ast_arg_t;
struct graphql_ast_arg_s {
    graphql_ast_node_t node;
    graphql_ast_name_t name;
    graphql_ast_value_t val;
};

typedef struct graphql_ast_directive_s graphql_ast_directive_t;
struct graphql_ast_directive_s {
    graphql_ast_node_t node;
    graphql_ast_name_t name;
    graphql_linked_list_t args;
};

typedef struct graphql_ast_args_item_s graphql_ast_args_item_t;
struct graphql_ast_args_item_s {
    graphql_linked_list_t lh;
    graphql_ast_arg_t arg;
};

typedef struct graphql_ast_dirs_item_s graphql_ast_dirs_item_t;
struct graphql_ast_dirs_item_s {
    graphql_linked_list_t lh;
    graphql_ast_directive_t dir;
};

typedef struct graphql_ast_selection_set_s graphql_ast_selection_set_t;
typedef struct graphql_ast_selection_s graphql_ast_selection_t;

struct graphql_ast_selection_set_s {
    graphql_ast_node_t node;
    graphql_linked_list_t selections;
};

struct graphql_ast_selection_s {
    int kind;
    graphql_linked_list_t lh;

    graphql_ast_selection_set_t selection_set;
};

typedef struct graphql_ast_field_s graphql_ast_field_t;
struct graphql_ast_field_s {
    graphql_ast_selection_t selection;
    graphql_ast_node_t node;

    graphql_ast_name_t alias;
    graphql_ast_name_t name;
    graphql_linked_list_t args;
    graphql_linked_list_t dirs;
};

typedef struct graphql_ast_fragment_spread_s graphql_ast_fragment_spread_t;
struct graphql_ast_fragment_spread_s {
    graphql_ast_selection_t selection;
    graphql_ast_node_t node;

    graphql_ast_name_t name;
    graphql_linked_list_t dirs;
};

typedef struct graphql_ast_inline_fragment_s graphql_ast_inline_fragment_t;
struct graphql_ast_inline_fragment_s {
    graphql_ast_selection_t selection;
    graphql_ast_node_t node;

    graphql_ast_name_t type_condition;
    graphql_linked_list_t dirs;
};

typedef struct graphql_ast_document_s graphql_ast_document_t;
struct graphql_ast_document_s {
    graphql_ast_node_t node;
    graphql_linked_list_t definitions;
};

#endif
