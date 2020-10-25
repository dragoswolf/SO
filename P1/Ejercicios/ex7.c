/*
    This program will create a child and send him a SIGUSR1 every second.
    Each time the child receives a signal, a printf must be casted out.
    In order to make the child receive a signal each second, we must use a loop inside the child
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>



void controller();


int main(int argc, char const *argv[])
{
    int status;
    pid_t pid;

    switch(pid=fork()){
        case -1:
            perror("Error forking: ");
            fprintf(stderr, "Error code: %d\n", errno);
            exit(EXIT_FAILURE);
        case 0:
            if(signal(SIGUSR1, controller)==SIG_ERR){
                perror("Signal error: ");
                fprintf(stderr, "Error code: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            for(int i=0; i<5; i++) pause();
            exit(EXIT_SUCCESS);
        default:

            for(int i=0; i<5; i++){
                sleep(1);
                kill(pid, SIGUSR1);
            }

            pid=wait(&status);
            
            if(pid>0){
                if(WIFEXITED(status)){
                    printf("Child %d exited succesfully. Status code: %d\n", pid, WEXITSTATUS(status));
                }
                if(WIFSIGNALED(status)){
                    printf("Child %d killed. Status code: %d\n", pid, WTERMSIG(status));
                }
                if(WIFSTOPPED(status)){
                    printf("Child %d stopped. Status code: %d\n", pid, WSTOPSIG(status));
                }
            }
            else{
                perror("Error calling wait(): ");
                fprintf(stderr, "Error code: %d\n", errno);
                exit(EXIT_FAILURE);
            }
    }
    return 0;
}

void controller(){
    printf("Signal received!\n");
}

