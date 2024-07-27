#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    printf("Number of commandline args: %i\n", argc);
    int i;
    for (i = 0; i < argc;  i++){
        printf("%i. argument is %s\n", i, argv[i]);
    }
    return 0;
}
