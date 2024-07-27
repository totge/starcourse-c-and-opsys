#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    int num1 = 5;
    int num2 = 6;
    char char1 = 'C';

    printf("Values are %i, %i\n", num1, num2);
    printf("Character is %c and is ascii value is %i\n", char1, char1);

    int result = 0;
    result = num1 + num2;

    printf("Sum is %i", result);
    return 0;
}
