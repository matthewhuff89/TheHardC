#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight) {
    struct Person x;
    x.name = name;
    x.age = age;
    x.height = height;
    x.weight = weight;
    return x;
};

void Person_print(struct Person dude) {
    printf("Name: %s\n", dude.name);
    printf("Age: %d\n", dude.age);
    printf("Height: %d\n", dude.height);
    printf("Weight: %d\n", dude.weight);
}

int main(int argc, char *argv[]) {
    struct Person murok = Person_create("Murok Crunkstorm", 27, 82, 190);
    struct Person agora = Person_create("Agora Crunkstorm", 27, 76, 170);

    printf("Murok is at memory location %p:\n", &murok);
    printf("Agora is at memory location %p:\n", &agora);

    Person_print(murok);
    Person_print(agora);

    return 0;
}
