#include <stdio.h>

int main(int argc, char *argv[]) {
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w'
    };   
   
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";
    char *pointer;

    areas[6] = 22;
    areas[7] = 23;
    areas[8] = name[0];
    areas[9] = 24;

    printf("%d, %d, %d, %c", areas[6], areas[7], areas[9], areas[8]);

    // Warning: On some systems you may have to change the 
    // %ld in this code to a %u since it will use unsigned ints
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The number of ints in areas: %ld\n", 
            sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d. \n", areas[10], areas[1]);

    printf("The size of a char: %ld\n", sizeof(char));
    printf("The size of a name (char[]): %ld\n", sizeof(name));
    printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));
    printf("The size of full name (char[]): %ld\n", sizeof(full_name));
    printf("The number of chars: %ld\n", sizeof(full_name) / sizeof(char));
    printf("The size of a double: %ld\n", sizeof(double));
    printf("The size of a short: %ld\n", sizeof(short));
    printf("The size of a long: %ld\n", sizeof(long));
    printf("The size of a void: %ld\n", sizeof(void));
    printf("The size of a pointer: %ld\n", sizeof(pointer)); 


    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}
