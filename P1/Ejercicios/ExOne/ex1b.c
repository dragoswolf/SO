/*

    Exercise 1A.
    We will implement a program that creates many processes.
    We will need to give it the number of processes as argument

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
    pid_t pid, childPid;
    int status;
    if (argc!=2){
        printf("Error. Usage is: <programName> <numberOfThreads>\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<atoi(argv[1]); i++){
        pid=fork();
        switch (pid){
            case -1:
                perror("Error: ");
                printf("Error code: %d\n", errno);
                exit(EXIT_FAILURE);
                break;
            case 0:
                printf("Process %d: Child %ld with father %ld.\n", i+1, (long)getpid(), (long)getppid());
                exit(0);
            default:
                printf("\nFather process: %ld\n", (long)getpid());
                
                childPid=wait(&status);

                if(WIFEXITED(status)){
                    printf("Child process %d terminated succesfully. Status code: %d\n", childPid, WEXITSTATUS(status));
                }
                
                else if(WIFSIGNALED(status)){
                    printf("Child process %d killed. Status code: %d\n", childPid, WTERMSIG(status));
                }

                else if(WIFSTOPPED(status)){
                    printf("Child process %d stopped. Status code: %d\n", childPid, WSTOPSIG(status));
                }
                else{
                    printf("Error when summoning wait().\n");
                    perror("");
                    printf("Error code: %d\n", errno);
                    exit(EXIT_FAILURE);
                }
        }
    }
    return 0;
}
