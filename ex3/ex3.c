#include <stdio.h>

int main(){
    int age = 10;
    int height = 72;
    char quantity = '1';
    char quantities[3] = "10";
    int bros = 5;
    float floaties = 9.99;
    double cheeseburger = 50.52345;

    printf("I am %d years old \n", age);
    printf("I am %d inches tall\n", height);
    printf("I am %c bird.\n", quantity);
    printf("Stop (form) feeding noob!!\f");
    printf("I am %s birds.\n", quantities);
    printf("I am %i brothers deep outchea.\n", bros);
    printf("Alert alert!!\a");
    printf("Return some \r carriages!\n");
    printf("--------------------------------\n");
    printf("Where da \v tabs at\t\n");
    printf("--------------------------------\n");
    printf("My octals are like %o!!\n", bros);
    printf("My hexas are crazy bruh, i'm talking %x, bruh...\n", height);
    printf("I got them floats goin for %f!!!\n", floaties);
    printf("Yo dawg i got these cheeseburgers...%lf a pop...\n", cheeseburger);
    return 0;
}
