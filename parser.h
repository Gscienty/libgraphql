#ifndef _LIBGRAPHQL_PARSER_H
#define _LIBGRAPHQL_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct graphql_parse_options_s graphql_parse_options_t;
struct graphql_parse_options_s {
    int no_loc;
    int no_src;
};

typedef struct graphql_parser_s graphql_parser_t;
struct graphql_parser_s {
    graphql_lexer_ctx_t lexer;    
    const char *src;
    graphql_parse_options_t opt;
    int prev_end;
    graphql_token_t tok;
};

int graphql_parse(const char *src, int no_loc, int no_src, graphql_ast_document_t *doc);

#endif
