#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 0;
    
    // go through each string in argv
    // we're skipping zero because it will just return the executable's name
    for(i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas",
        NULL, NULL
    };

    int num_states = 6;

    for(i = 0; i < num_states; i++) {
        printf("state %d: %s, %p\n", i, states[i], &(states[i]));
    };

    return 0;
}
