/** Split one shell command line into words, punctuation, and quoted strings. */
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"

static bool is_special(char c) {
    return c == '(' || c == ')' || c == '<' || c == '>' ||
            c == ';' || c == '|';
}

/** Add exactly the characters in [start, end) as a new token. */
static void add_span(vect_t *tokens, const char *start, const char *end) {
    size_t length = (size_t)(end - start);
    char *word = malloc(length + 1);
    assert(word != NULL);
    memcpy(word, start, length);
    word[length] = '\0';
    vect_add(tokens, word);
    free(word);
}

vect_t *tokenize(const char *input) {
    assert(input != NULL);
    vect_t *tokens = vect_new();
    const char *p = input;

    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
        p++;
        } else if (is_special(*p)) {
        add_span(tokens, p, p + 1);
        p++;
        } else if (*p == '"') {
        const char *start = ++p;
        while (*p != '\0' && *p != '"') p++;
        add_span(tokens, start, p);
        if (*p == '"') p++;
        } else {
        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p) &&
                !is_special(*p) && *p != '"') p++;
        add_span(tokens, start, p);
        }
    }
    return tokens;
}
