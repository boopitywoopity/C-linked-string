#include <stdio.h>
#include "l_string.c"


void create_lstring(l_string *first, char in);

void destroy_lstring(l_string *first);

l_string *initialize_lstring();

l_string *read_lstring_bchar(char b_char);

void print_lstring(l_string *first);
