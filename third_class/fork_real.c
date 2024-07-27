#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <errno.h> 

pid_t main_process_value = 0;
int common_value = 1;

pid_t child(){
    pid_t process = fork();

    if(process == -1){
        exit(-1);
    }
    if(process > 0 ){
        return process;
    }
    // this only gets executed when we are in the child process

    common_value = 5;
    printf("The common vaule is %i in child after forking.\n", common_value);

    // exiting child process so that it doesn't return to main, this also lets the parent continue its process.
    exit(0);
}

int main(){
    common_value = 2;
    printf("The common vaule is %i before forking.\n", common_value);
    main_process_value = getpid();
    // outsource forking to a function
    child();
    // wait untill child process terminates
    wait(NULL);


    return 0;
}