#include <stdio.h>

typedef struct l_string_node{
    char c;
    struct l_string_node *next;
} l_string;


void create_lstring(l_string *first, char in);

void destroy_lstring(l_string *first);

l_string *initialize_lstring();

l_string *read_lstring(char b_char);

void print_lstring(l_string *first);
