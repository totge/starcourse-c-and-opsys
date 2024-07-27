
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <errno.h> 





int main(){
    int status;
    int common_value = 1;

    printf("Current value is %i before forking\n", common_value);

    pid_t child = fork();

    if (child < 0){
        perror("The fork calling failed.\n");

        
    }
    if (child > 0){
        waitpid(child, &status, 0);
        printf("Current value in parent is %i after forking\n", common_value);
    }
    else {
        common_value = 5;
        printf("Current value in child is %i after forking\n", common_value);
    }


    return 0;
}