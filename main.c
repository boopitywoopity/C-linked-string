#include "l_string.h"

int main(int argc, char **argv){
    l_string *str = read_lstring();

    print_lstring(str);

    destroy_lstring(str);
    return 0;
}
