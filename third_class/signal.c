#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 

void handler(int signum){
    printf("Signal number is %i", signum);
}

void handler_sigkill(int signum){
    printf("Signal number is %i", signum);
}
int main(){
    int i = 0;
    signal(SIGTERM, handler);
    signal(SIGKILL, handler_sigkill);
    while(1){
        printf("i = %i", i);
        i++;
        sleep(1);
    }
    return 0;
}