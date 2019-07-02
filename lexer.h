#ifndef _LIBGRAPHQL_LEXER_H
#define _LIBGRAPHQL_LEXER_H

#define GQL_EOF          0
#define GQL_BANG         1
#define GQL_DOLLAR       2
#define GQL_PAREN_L      3
#define GQL_PAREN_R      4
#define GQL_SPREAD       5
#define GQL_COLON        6
#define GQL_EQUALS       7
#define GQL_AT           8
#define GQL_BRACKET_L    9
#define GQL_BRACKET_R    10
#define GQL_BRACE_L      11
#define GQL_PIPE         12
#define GQL_BRACE_R      13
#define GQL_NAME         14
#define GQL_INT          15
#define GQL_FLOAT        16
#define GQL_STRING       17
#define GQL_BLOCK_STRING 18
#define GQL_AMP          19

#define GRAPHQL_MAKE_TOKEN_EOF(t, p) \
    ({ \
        (t)->kind  = GQL_EOF; \
        (t)->start = (p); \
        (t)->end   = (p); \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BANG(t, p) \
    ({ \
        (t)->kind  = GQL_BANG; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_DOLLAR(t, p) \
    ({ \
        (t)->kind  = GQL_DOLLAR; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_AMP(t, p) \
    ({ \
        (t)->kind  = GQL_AMP; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_PAREN_L(t, p) \
    ({ \
        (t)->kind  = GQL_PAREN_L; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_PAREN_R(t, p) \
    ({ \
        (t)->kind  = GQL_PAREN_R; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_COLON(t, p) \
    ({ \
        (t)->kind  = GQL_COLON; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_EQUALS(t, p) \
    ({ \
        (t)->kind  = GQL_EQUALS; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_AT(t, p) \
    ({ \
        (t)->kind  = GQL_AT; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACKET_L(t, p) \
    ({ \
        (t)->kind  = GQL_BRACKET_L; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACKET_R(t, p) \
    ({ \
        (t)->kind  = GQL_BRACKET_R; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACE_L(t, p) \
    ({ \
        (t)->kind  = GQL_BRACE_L; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_PIPE(t, p) \
    ({ \
        (t)->kind  = GQL_PIPE; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_BRACE_R(t, p) \
    ({ \
        (t)->kind  = GQL_BRACE_R; \
        (t)->start = (p); \
        (t)->end   = (p) + 1; \
        (t)->val   = ""; \
     })

#define GRAPHQL_MAKE_TOKEN_SPREAD(t, p) \
    ({ \
        (t)->kind  = GQL_SPREAD; \
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
