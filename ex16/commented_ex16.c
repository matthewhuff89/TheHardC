// Include the Standard I/O library, giving me access to methods that allow me to interact with the input, output, and error streams of the computer.
#include <stdio.h>
// Include the Assert() macro, which tests an expression and terminates the process it's located in if it returns false. It doesn't do anything if the expression is true.
#include <assert.h>
// Include the Standard Library, giving access to conversion functions, memory allocation functions and some extra variable types and macros like NULL
#include <stdlib.h>
// Gives access to a lot of functinos for manipulating Strings
#include <string.h>

// Creating a new structure with four elements, defining it as a Person.
struct Person {
    // Declaring a char pointer named 'name' to be a part of my Person struct
    char *name;
    // Declaring an integer variable named age
    int age;
    // Declaring an integer variable named height
    int height;
    // Declaring an integer variable named weight
    int weight;
};

// Defining a function pointer of type struct Person, that takes in a character pointer, and 3 integers. This function returns a pointer 
struct Person *Person_create(char *name, int age, int height, int weight) {
    // Declaring a pointer of type 'struct Person' named 'who', and set equal to a to the address/pointer of a block of memory allocated for the size of a Person struct 
    struct Person *who = malloc(sizeof(struct Person));
    // Check to make sure who is not null
    assert(who != NULL);
    
    // Dereference who's name pointer and set it equal to a duplicate of the name string
    who->name = strdup(name);
    // Dereference age and set it equal to age
    who->age = age;

    // Dereference height and set it equal to passed height value
    who->height = height;
    // Dereference weight and set it equal to passed weight value
    who->weight = weight;

    // Return who pointer
    return who;
}

// Define function that returns no value and takes a Person pointer as an argument
void Person_destroy(struct Person *who) {
    // Checks to make sure who pointer is valid
    assert(who != NULL);
    // deallocate/free up memory from name pointer
    free(who->name);
    // deallocate/free up memory from who pointer's value
    free(who);
}

// Define a function named Person_print that returns nothing and takes in a struct Person pointer as an argument
void Person_print(struct Person *who) {
    // Print to output stream our who structure's dereferenced data property name
    printf("Name: %s\n", who->name);
    // print to output stream: dereferenced data member who.age
    printf("Age: %d\n", who->age);
    // print to output stream the dereferenced, accessed data who.height
    printf("Height: %d\n", who->height);
    // print to output stream data who.weight
    printf("Weight: %d\n", who->weight);
}

// Define main function of script 
int main(int argc, char *argv[]) {
    // make two people structures
    // Create pointer of type 'Person' named Joe set to address of returned value of Person_create
    struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
    // Create pointer of type 'Person' named Frank set to address of returned value of Person_create
    struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    // Calling person_print to dereference, access, and print joe pointer's values
    Person_print(joe);
    // Same as above
    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    // Dereference, access, and add 20 to value of joe.age
    joe->age +=20;
    // Dereference, access, and subtract 2 from value of joe.height
    joe->height -= 2;
    // Dereference, access, and add 40 to value of joe.weight
    joe->weight += 40;
    // Print Joe's values again
    Person_print(joe);
    
    // Dereference, access, and add 20 to value of frank.age
    frank->age += 20;
    // Dereference, access, and add 20 to value of frank.weight
    frank->weight += 20;
    // Print frank's values again
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);
    // Return value from function
    return 0;
}
