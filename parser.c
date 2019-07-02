#include "parser.h"

static int graphql_parser_init(graphql_parser_t *, const char *, int, int);

int graphql_parse(const char *src, int no_loc, int no_src, graphql_ast_document_t *doc)
{
    int err;
    graphql_parser_t parser;
    err = graphql_parser_init(&parser, src, no_loc, no_src);
    if (err < 0) {
        return err;
    }

    // TODO

    return 0;
}

static int graphql_parser_init(graphql_parser_t *parser, const char *src, int no_loc, int no_src)
{
    int err;
    parser->src = src;
    parser->opt.no_loc = no_loc;
    parser->opt.no_src = no_src;
    parser->prev_end = 0;
    err = graphql_lex_init(&parser->lexer, src);
    if (err < 0) {
        return err;
    }
    err = parser->lexer.cb(&parser->lexer, &parser->tok, 0);
    if (err < 0) {
        return err;
    }

    return 0;
}

