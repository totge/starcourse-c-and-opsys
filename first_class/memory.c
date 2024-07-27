#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    int n; 
    n = 25;

    int *k = &n;
    printf("n is %i\n", n);
    printf("k is %i\n", *k);

    return 0;
}