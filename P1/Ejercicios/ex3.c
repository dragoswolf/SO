/*
    Exercise 3
    This program will create two processes.
    The first one will summon a calculator.
    The second one will summon a text editor with N text files.
    All arguments must be passed through the CLI
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

void calcProcess(char *);
void editorProcess(char **);


int main(int argc, char *argv[])
{
    int status;
    pid_t childPid;
    if(argc<4){
        printf("Usage: <programName> <calculator> <textEditor> <textFile1> <textFileN>");
        exit(EXIT_FAILURE);
    }

    //We're making a for loop with a maximum of 2 because we are summoning 2 processes
    for(int i=0; i<2; i++){
        switch(fork()){
            case -1:
                printf("Error forking.\n");
                perror("");
                printf("Error code: %d\n", errno);
                exit(EXIT_FAILURE);
                break;
            case 0:
                if(i==0) calcProcess(argv[1]);
                else editorProcess(argv + 2); //we take all arguments starting from argv[2]
                exit(EXIT_SUCCESS);
                break;
        }
    }

    //Father process
    for(int i=0; i<2; i++){
        childPid=wait(&status);

        if(WIFEXITED(status)){
            printf("Child %d exited succesfully. Status code: %d\n", childPid, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("Child %d was killed. Status code: %d\n", childPid, WTERMSIG(status));
        }
        else if(WIFSTOPPED(status)){
            printf("Child %d was stopped. Status code: %d\n", childPid, WSTOPSIG(status));
        }
        else{
            printf("Error summoning wait()\n");
            perror("");
            printf("Error code: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}


void calcProcess(char *calcName){
    execlp(calcName, calcName, NULL);
}

void editorProcess(char *args[]){
    execvp(args[0], args);
}
