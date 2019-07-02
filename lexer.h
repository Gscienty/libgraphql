#ifndef _LIBGRAPHQL_LEXER_H
#define _LIBGRAPHQL_LEXER_H

#define EOF          0
#define BANG         1
#define DOLLAR       2
#define PAREN_L      3
#define PAREN_R      4
#define SPREAD       5
#define COLON        6
#define EQUALS       7
#define AT           8
#define BRACKET_L    9
#define BRACKET_R    10
#define BRACE_L      11
#define PIPE         12
#define BRACE_R      13
#define NAME         14
#define INT          15
#define FLOAT        16
#define STRING       17
#define BLOCK_STRING 18
#define AMP          19

#define GRAPHQL_MAKE_TOKEN_EOF(t, p) \
    ({ \
        (t)->kind  = EOF; \
        (t)->start = (p); \
        (t)->end   = (p); \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BANG(t, p) \
    ({ \
        (t)->kind  = BANG; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_DOLLAR(t, p) \
    ({ \
        (t)->kind  = DOLLAR; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_AMP(t, p) \
    ({ \
        (t)->kind  = AMP; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_PAREN_L(t, p) \
    ({ \
        (t)->kind  = PAREN_L; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_PAREN_R(t, p) \
    ({ \
        (t)->kind  = PAREN_R; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_COLON(t, p) \
    ({ \
        (t)->kind  = COLON; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_EQUALS(t, p) \
    ({ \
        (t)->kind  = EQUALS; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_AT(t, p) \
    ({ \
        (t)->kind  = AT; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACKET_L(t, p) \
    ({ \
        (t)->kind  = BRACKET_L; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACKET_R(t, p) \
    ({ \
        (t)->kind  = BRACKET_R; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACE_L(t, p) \
    ({ \
        (t)->kind  = BRACE_L; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_PIPE(t, p) \
    ({ \
        (t)->kind  = PIPE; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACE_R(t, p) \
    ({ \
        (t)->kind  = BRACE_R; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_SPREAD(t, p) \
    ({ \
        (t)->kind  = SPREAD; \
        (t)->start = (p); \
        (t)->end   = (p) + 3; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN(t, k, s, p, v) \
    ({ \
        (t)->kind  = (k); \
        (t)->start = (s); \
        (t)->end   = (p); \
        (t)->val   = (v); \
     })

typedef struct graphql_token_s graphql_token_t;
struct graphql_token_s {
    int kind;
    int start;
    int end;
    const char *val;
};

typedef struct graphql_lexer_ctx_s graphql_lexer_ctx_t;
typedef int (*graphql_lexer_ctx_fptr) (graphql_lexer_ctx_t *, graphql_token_t *, int);
struct graphql_lexer_ctx_s {
    int prev_pos;
    const char *src;
    graphql_lexer_ctx_fptr cb;
};

int graphql_lex_init(graphql_lexer_ctx_t *ctx, const char *src);

#endif
