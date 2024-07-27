#include <stdlib.h>
#include <stdio.h>
#include <strings.h>


int main(){

    FILE* fp = fopen("names.txt", "r");

    if (fp == NULL){
        printf("Error happend during file opening.");
        return -1;
    }

    

    
    return 0;
}