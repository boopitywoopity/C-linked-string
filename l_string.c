#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct l_string_node{
    char c;
    struct l_string_node *next;
} l_string;

static char get_putc();

/*
 * @param first the first node making up the string
 * @in the character added to the string
 */
void create_lstring(l_string *first, char in){
    // keeps the nodes so you dont have to cycle through them each time
    static l_string *first_s = NULL;
    static l_string *last_s = NULL;

    // Initial assignment when function is first ran
    if (first_s == NULL ){
        first_s = first;
        first_s->c = in;
        first_s->next = NULL;
        last_s = first_s;
    }

    // a previous string addition occured and the first_s and last_s need to be reasigned
    else if (first_s != first){
        first_s = first;
        if (first_s->c == '\0'){
            first_s->c = in;
            first_s->next = NULL;
            last_s = first_s;
        }
        else {
            last_s = first_s;
            while (last_s->next != NULL){
                last_s = last_s->next;
            }

            last_s->next = malloc(sizeof(l_string));
            if (last_s->next == NULL){
                perror("Memory allocation failed");
                exit(1);
            }
            // sets the last no
            last_s = last_s->next;
            last_s->c = in;
            last_s->next = NULL;
        }
    }
    else { // if this string is already defined and the static values are correct
        last_s->next = malloc(sizeof(l_string));
        if (last_s->next == NULL){
            perror("Memory allocation failed");
            exit(1);
        }
        // sets the last node
        last_s = last_s->next;
        last_s->c = in;
        last_s->next = NULL;
    }
}

void destroy_lstring(l_string *first){
    l_string *current = first;
    while (current != NULL){
        l_string *tmp = current;
        current = current->next;
        free(tmp);
    }
}


l_string *initialize_lstring(){
    l_string *str = malloc(sizeof(l_string));
    str->c = '\0';
    str->next = NULL;
    return str;
}

/*
 * Reads in a character and prints it back to stdout
 * Used when the terminal settings have been modified to disable echoing
 * @return character from stdin
*/
static char get_putc(){
    char in = getchar();
    putc(in, stdout);
    return in;
}

/*
 * @param b_char an input character signaling when the input should stop reading
 * @return the l_string struct marking the first element in the string
 */
static l_string *read_string(char b_char) {
    // Creates the string
    l_string *str = initialize_lstring();

    char in;
    while ( (in = get_putc()) != EOF) {
        if (in == b_char)
            break;
        create_lstring(str, in);
    }

    putc('\n', stdout); // outputs a newline because taking in input is finished
    return str;
}


/*
 * @param b_char an input character signaling when the input should stop reading
 * @return the l_string struct marking the first element in the string
*/
l_string *read_lstring_bchar(char b_char) {
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);  // Get the current terminal settings
    newt = oldt;  // Copy the settings
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply the new settings

    l_string *str = read_string(b_char);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old terminal settings
    return str;
}

#define read_lstring() read_lstring_bchar('\n')

void print_lstring(l_string *first){
    l_string *tmp = first;
    while (tmp != NULL){
        putc(tmp->c, stdout);
        tmp = tmp->next;
    }
}



