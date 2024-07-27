#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <errno.h> 

pid_t main_process_value = 0;
int common_value = 1;

enum message {
    counting
};

pid_t child(int pipe_id_rec, int pipe_id_send){
    pid_t process = fork();

    if(process == -1){
        exit(-1);
    }
    if(process > 0 ){
        return process;
    }
    // this only gets executed when we are in the child process

    enum message sing;
    int counter = 1;

    while (counter < 4){
        read(pipe_id_rec, &sing, sizeof(enum message));
        sleep(1);
        printf("Child message: %i", counter);
        counter++;
    }

    // exiting child process so that it doesn't return to main, this also lets the parent continue its process.
    exit(0);
}

int main(){
    common_value = 2;
    printf("The common vaule is %i before forking.\n", common_value);
    main_process_value = getpid();

    int io_pipes1[2];
    int succ = pipe(io_pipes1);

    if (succ == -1){
        exit(-1);
    }

    // outsource forking to a function
    child(io_pipes1[0], io_pipes1[1]);

    enum message puffer = counting;
    
    int main_counter = 1;
    while (main_counter < 4){
        sleep(1);
        printf("Parent message: %i", main_counter);
        write(io_pipes1, &puffer, sizeof(enum message));
        main_counter++;
    }
    

    // wait untill child process terminates
    wait(NULL);


    return 0;
}