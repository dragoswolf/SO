/*
*
*   This example will be about creating and using processes.
*
*/


//=========================== INCLUDES ============================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//=================================================================

int main(int argc, char const *argv[])
{
    pid_t pid, childPid;
    int status;
    int i, j;

    pid=fork();

    switch(pid){

        case -1:
            perror("Fork error: ");
            printf("Error status code: %d\n", errno);
            exit(EXIT_FAILURE);

        case 0:
            i=0;
            printf("I'm the child (PID: %ld, PPID: %ld). My variable is even and initialized at %d.\n", (long)getpid(), (long)getppid(), i);
            for(j=0; j<5; j++){
                i++;
                i++;
                printf("The variable is now: %d.\n", i);
            }
        break;

        default:
            i=1;
            printf("I'm the father (PID: %ld). My variable is odd and initialized at %d.\n", (long)getpid(), i);
            for(j=0; j<5; j++){
                i++;
                i++;
                printf("The variable is now: %d.\n", i);
            }

            childPid=wait(&status);

            if(childPid>0){
                if(WIFEXITED(status)){
                    printf("Child %d exited succesfully. Exit status: %d.\n", childPid, WEXITSTATUS(status));
                }
                else if(WIFSIGNALED(status)){
                    printf("Child %d killed by unhandled signal. Exit status: %d.\n", childPid, WTERMSIG(status));
                }
                else if(WIFSTOPPED(status)){
                    printf("Child %d stopped by unhandled signal. Exit status: %d.\n", childPid, WSTOPSIG(status));
                }
            }
            else{
                perror("Error summoning wait(): ");
                printf("Error code: %d.\n", errno);
                exit(EXIT_FAILURE);
            }

    }
    //Whatever we put here will be executed by both the child and the father process.
    printf("End of execution.\n\n");
    exit(EXIT_SUCCESS);
}
