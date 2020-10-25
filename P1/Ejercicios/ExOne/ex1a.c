/*
    Exercise 1B
    In this exercise we will create a hand fan of processes.
    We will need to pass the number of processes as an argument.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>



int main(int argc, char *argv[])
{

    int status;
    pid_t childPid;

    if(argc!=2){
        printf("Usage: <programName> <numberOfProcesses>\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<atoi(argv[1]); i++){
        switch(fork()){
            case -1:
                printf("Error forking.\n");
                perror("");
                printf("Error code: %d\n", errno);
                exit(EXIT_FAILURE);
                break;
            case 0:
                printf("Child %ld with father %ld.\n", (long)getpid(), (long)getppid());
                exit(0);
                break;
        }
           
    }

    for(int i=0; i<atoi(argv[1]); i++){
     printf("\nFather %ld\n", (long)getpid());

                childPid=wait(&status);

                if(WIFEXITED(status)){
                    printf("Child %d exited succesfully. Status code: %d\n", childPid, WEXITSTATUS(status));
                }
                else if(WIFSIGNALED(status)){
                    printf("Child %d killed. Status code: %d\n", childPid, WTERMSIG(status));
                }
                else if(WIFSTOPPED(status)){
                    printf("Child %d stopped. Status code: %d\n", childPid, WSTOPSIG(status));
                }
                else{
                    printf("Error summoning wait().\n");
                    perror("");
                    printf("Error code: %d\n", errno);
                    exit(EXIT_FAILURE);
                }
    }
    



    return 0;
}
