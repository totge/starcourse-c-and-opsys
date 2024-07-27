#include "sys/types.h"
#include "unistd.h"
#include "stdlib.h"
#include "signal.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "sys/wait.h"
#include "sys/ipc.h"
#include "sys/msg.h"
#include "sys/shm.h"
#include "sys/sem.h"
#include "sys/stat.h"

pid_t mainProcessValue = 0;
int childReady = 0;
int readyToContinue = 0;
int messageQueue;
int semid;
struct sharedData *s;

struct message 
{
    long mtype;
    char mtext[250];
};

struct sharedData
{
    char text[1024];
};

int semaphoreCreation(const char *pathname, int semaphoreValue)
{
    int semid;
    key_t key;

    key = ftok(pathname, 1);
    if((semid = semget(key, 1, IPC_CREAT | S_IRUSR | S_IWUSR)) < 0)
        perror("semget");
    if(semctl(semid, 0, SETVAL, semaphoreValue) < 0)
        perror("semctl");
    return semid;
}

void semapthoreOperation(int semid, int op) 
{
    struct sembuf opreration;

    opreration.sem_num = 0;
    opreration.sem_op = op;
    opreration.sem_flg = 0;

    if(semop(semid, &opreration, 1) < 0)
        perror("semop");
}

void semaphoreDelete(int semid) 
{
    semctl(semid, 0, IPC_RMID);
}


void childrenReadyHandler(int sig) {
    if(sig == SIGUSR1) {
        childReady++;
    }
}

void readyToContinueHandler(int sig) {
    if(sig == SIGUSR2) {
        readyToContinue = 1;
    }
}

pid_t child1(int pipe_id_rec, int pipe_id_send) 
{
    pid_t process = fork();
    if(process == -1)
        exit(-1);
    if(process > 0)
    {
        return process;
    }

    printf("Első érdeklődő olvassa a kiírást.\n");
    kill(mainProcessValue, SIGUSR1);

    char question[] = "Csak egy alkalom elérhető, vagy lesz több nap is?";
    write(pipe_id_send, question, sizeof(question));
    char puffer[250];
    read(pipe_id_rec, puffer, sizeof(puffer));
    printf("Kapott válasz: %s\n", puffer);
    kill(mainProcessValue, SIGUSR2);

    exit(0);
}


pid_t child2() 
{
    pid_t process = fork();
    if(process == -1)
        exit(-1);
    if(process > 0)
    {
        return process;
    }

    printf("Második érdelődő olvassa a kiírást.\n");
    kill(mainProcessValue, SIGUSR1);

    int status;

    // waiting for signal from the parent process to continue
    while(readyToContinue == 0);
    readyToContinue = 0;

    struct message ms = {5, "Rendben, nem a legjobb, de megoldható."};
    status = msgsnd(messageQueue, &ms, strlen(ms.mtext) + 1, 0);
    if(status < 0)
    {
        perror("msgsnd");
    }


    char secondMessage[250] = "Módosítanom kell a naptáram, de így is részt tudok majd venni.";
    semapthoreOperation(semid, -1);
    strcpy(s->text, secondMessage);
    semapthoreOperation(semid, 1);
    shmdt(s);
    exit(0);
}


int main(int argc, char **argv)
{
    mainProcessValue = getpid();
    signal(SIGUSR1, childrenReadyHandler);
    signal(SIGUSR2, readyToContinueHandler);

    int status;
    key_t mainKey;

    mainKey = ftok(argv[0], 1);
    messageQueue = msgget(mainKey, 0600 | IPC_CREAT);
    if(messageQueue < 0)
    {
        perror("msgget");
        return 1;
    }

    int sh_mem_id;
    sh_mem_id = shmget(mainKey, sizeof(s), IPC_CREAT | S_IRUSR | S_IWUSR);
    s = shmat(sh_mem_id, NULL, 0);

    semid = semaphoreCreation(argv[0], 1);

    int io_pipes[2];
    int succ = pipe(io_pipes);
    if(succ == -1)
        exit(-1);

    int io_pipes1[2];
    int succ1 = pipe(io_pipes1);
    if(succ1 == -1)
        exit(-1);

    pid_t childProcess1 = child1(io_pipes1[0], io_pipes[1]);
    pid_t childProcess2 = child2();

    while(childReady < 1)
        ;
    puts("Első érdeklődő elolvasta a kiírást.");
    while(childReady < 2)
        ;
    puts("Második érdeklődő is elolvasta a kiírást.");

    char puffer[250];
    read(io_pipes[0], puffer, sizeof(puffer));
    printf("Első érdeklődő kérdezi: %s\n", puffer);

    char answear[] = "Egyenlőre csak egy opcionális időpont van.";

    write(io_pipes1[1], answear, sizeof(answear));
    
    // waiting for the first child process to send a signal that the message is recived and processed
    while (readyToContinue == 0);
    readyToContinue = 0;

    kill(childProcess2, SIGUSR2);

    struct message ms;

    status = msgrcv(messageQueue, &ms, 250, 5, 0);
    if(status < 0)
    {
        perror("msgrcv");
    }
    else 
    {
        printf("Hozzászólás a második érdeklődőtől: %s \n", ms.mtext);
    }

    semapthoreOperation(semid, -1);
    printf("Második édeklődő döntése: %s\n", s->text);
    semapthoreOperation(semid, 1);

    shmdt(s);
    wait(NULL);
    wait(NULL);
    semaphoreDelete(semid);
    close(io_pipes[0]);
    close(io_pipes1[0]);
    close(io_pipes[1]);
    close(io_pipes1[1]);
    status = msgctl(messageQueue, IPC_RMID, NULL);
    if(status < 0)
    {
        perror("msgctl");
    }
    return 0;
}