#include <stdio.h>

int index_print(int ages[], char *names[]){
    int j = 0;
    int print_count = sizeof(*ages) / sizeof(int);

    printf("%d", print_count);

    for(j = 0; ages[j] != '\0'; j++){
        printf("%s has %d years alive.\n", names[j], ages[j]);
    }
    return 0;
};

int cur_print(int *cur_age, char **cur_name) {
  int j = 0;  
  for(j = 0; cur_age[j] != '\0'; j++) {
    printf("%s is %d years old.\n", cur_name[j], cur_age[j]);
  }  

  return 0;
}

int main(int argc, char *argv[]) {
    // create two arrays that we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };
    
    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    index_print(ages, names); 

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
     
    // second way using pointers
    cur_print(cur_age, cur_name); 

    printf("---\n");

    // third way, pointers are just arrays
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for(cur_name = names, cur_age = ages; 
           (cur_age - ages) < count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
    // print out addresses for this exercises pointers
    for(i = 0; i < count; i++) {
        printf("address %d: age - %p, name - %p\n", i, &cur_age[i], &cur_name[i]);
    }
    return 0;


}

/* WHAT MATT THINKS A POINTER DOES:
 * A Pointer points to an address in memory where an array is storing other addresses to characters and integers
 */
