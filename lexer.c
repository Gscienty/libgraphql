#include "lexer.h"
#include <stddef.h>
#include <stdio.h>

static int graphql_lexer_ctx_inner_exector(graphql_lexer_ctx_t *, graphql_token_t *, int);
static int graphql_lexer_read_token(graphql_lexer_ctx_t *, int, graphql_token_t *);
static void graphql_lexer_pos_after_whitespace(const char *, int, int *);
static int graphql_make_token_number(graphql_token_t *, graphql_lexer_ctx_t *, int, const char);
static int graphql_make_token_digits(graphql_lexer_ctx_t *, int, const char);
static int graphql_make_token_name(graphql_token_t *, graphql_lexer_ctx_t *, int);

int graphql_lex_init(graphql_lexer_ctx_t *ctx, const char *src)
{
    if (ctx == NULL) {
        return -1;
    }
    ctx->prev_pos = 0;
    ctx->src = src;
    ctx->cb = graphql_lexer_ctx_inner_exector;
    return 0;
}

static int graphql_lexer_ctx_inner_exector(graphql_lexer_ctx_t *ctx, graphql_token_t *tok, int pos)
{
    if (tok == NULL) {
        return -1;
    }
    if (pos == 0) {
        pos = ctx->prev_pos;
    }
    int err = graphql_lexer_read_token(ctx, pos, tok);
    if (err != 0) {
        return err;
    }
    ctx->prev_pos = tok->end;
    return 0;
}

static int graphql_lexer_read_token(graphql_lexer_ctx_t *ctx, int fpos, graphql_token_t *tok)
{
    int pos;
    graphql_lexer_pos_after_whitespace(ctx->src, fpos, &pos);

    if (ctx->src[pos] == 0x00) {
        GRAPHQL_MAKE_TOKEN_EOF(tok, pos);
        return 0;
    }
    char code = ctx->src[pos];
    if (code < 0x20 && code != 0x09 && code != 0x0A && code != 0x0D) {
        return -1;
    }

    switch (code) {
    case '!':
        GRAPHQL_MAKE_TOKEN_BANG(tok, pos);
        return 0;

    case '$':
        GRAPHQL_MAKE_TOKEN_DOLLAR(tok, pos);
        return 0;

    case '&':
        GRAPHQL_MAKE_TOKEN_AMP(tok, pos);
        return 0;

    case '(':
        GRAPHQL_MAKE_TOKEN_PAREN_L(tok, pos);
        return 0;

    case ')':
        GRAPHQL_MAKE_TOKEN_PAREN_R(tok, pos);
        return 0;

    case ':':
        GRAPHQL_MAKE_TOKEN_COLON(tok, pos);
        return 0;

    case '=':
        GRAPHQL_MAKE_TOKEN_EQUALS(tok, pos);
        return 0;

    case '@':
        GRAPHQL_MAKE_TOKEN_AT(tok, pos);
        return 0;

    case '[':
        GRAPHQL_MAKE_TOKEN_BRACKET_L(tok, pos);
        return 0;

    case ']':
        GRAPHQL_MAKE_TOKEN_BRACKET_R(tok, pos);
        return 0;

    case '{':
        GRAPHQL_MAKE_TOKEN_BRACE_L(tok, pos);
        return 0;

    case '}':
        GRAPHQL_MAKE_TOKEN_BRACE_R(tok, pos);
        return 0;

    case '|':
        GRAPHQL_MAKE_TOKEN_PIPE(tok, pos);
        return 0;

    case '.':
        if (ctx->src[pos + 1] == '.' && ctx->src[pos + 2] == '.') {
           GRAPHQL_MAKE_TOKEN_SPREAD(tok, pos);
           return 0;
        }
        break;

    case '-':
    case '0' ... '9':
        return graphql_make_token_number(tok, ctx, pos, code);

    case '_':
    case 'a' ... 'z':
    case 'A' ... 'Z':
        return graphql_make_token_name(tok, ctx, pos);
    }

    return -1;
}

static void graphql_lexer_pos_after_whitespace(const char *src, int spos, int *pos)
{
    *pos = spos;

    for ( ; src[*pos]; ) {
        char code = src[*pos];
        if (code == 0x09
            || code == 0x20
            || code == 0x0A
            || code == 0x0D
            || code == 0x2C) {
            (*pos)++;
        }
        else if (code == '#') {
            (*pos)++;
            for ( ;src[*pos]
                  && (code > 0x1F || code == 0x09)
                  && code != 0x0A && code != 0x0D; (*pos)++) {
                code = src[*pos];
            }
        }
        else {
            break;
        }
    }
}

static int graphql_make_token_number(graphql_token_t *tok, graphql_lexer_ctx_t *ctx, int start, const char first)
{
    char code = first;
    const char *src = ctx->src;
    int pos = start;
    int is_float = 0;

    if (code == '-') {
        code = src[++pos];
    }
    if (code == '0') {
        code = src[++pos];
        if (code >= '0' && code <= '9') {
            return -1;
        }
    }
    else {
        int dpos = graphql_make_token_digits(ctx, pos, code);    
        if (dpos < 0) {
            return dpos;
        }
        pos = dpos;
        code = src[pos];
    }
    if (code == '.') {
        is_float = 1;
        code = src[++pos];
        int dpos = graphql_make_token_digits(ctx, pos, code);
        if (dpos < 0) {
            return dpos;
        }
        pos = dpos;
        code = src[pos];
    }
    if (code == 'E' || code == 'e') {
        is_float = 1;
        code = src[++pos];
        if (code == '+' || code == '-') {
            code = src[++pos];
        }
        int dpos = graphql_make_token_digits(ctx, pos, code);
        if (dpos < 0) {
            return dpos;
        }
        pos = dpos;
    }

    GRAPHQL_MAKE_TOKEN(tok, is_float ? FLOAT : INT, start, pos, ctx->src + start);

    return 0;
}

static int graphql_make_token_digits(graphql_lexer_ctx_t *ctx, int start, const char first)
{
    const char *src = ctx->src;
    int pos = start;
    char code = first;

    if ('0' <= code && code <= '9') {
        for (; '0' <= code && code <= '9'; ) {
            code = src[++pos];
        }
        return pos;
    }
    return -1;
}

static int graphql_make_token_name(graphql_token_t *tok, graphql_lexer_ctx_t *ctx, int spos)
{
    int epos = spos;
    char code;

    do {
        code = ctx->src[++epos];
    } while (code != 0
             && ctx->src[epos] != 0
            && (code == '_'
                || ('0' <= code && code <= '9')
                || ('a' <= code && code <= 'z')
                || ('A' <= code && code <= 'Z')));

    GRAPHQL_MAKE_TOKEN(tok, NAME, spos, epos, ctx->src + spos);
    return 0;
}

