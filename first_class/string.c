#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char **argv){

    char str1[] = "Hello";
    printf("Content of variable str1: \'%s\'\n", str1);
    printf("Array 11th element is: %c", str1[4]);

// todo: beírni a valós értékeket a behelyettesítésre
    printf("str is %s, lentgth with custom function is: %i, and with buildt is: %i ");

    char *str2;

    str2 = (char *) malloc(80 * sizeof(char));
    str2[0] = 'A';
    str2[0] = '1';
    str2[0] = 0;

    free(str2);


    return 0;
}


int length(char *str){
    int l = 0;
    while (* str++ != 0){
        l++;
    }
    return l;
}
    