/*

    This program will receive two numbers from the CLI. Each number will be 
    passed to a process. Each process will call the fact.c program and calculate
    the factorial of both numbers.

    We will use sleep to diferentiate between the processes themselves.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


void calcFact(char *);


void calcFact(char *number){
    char *programName="./fact";

    if(execl(programName, programName, number, NULL)==-1){
        perror("Exec error: ");
        printf("Error code: %d\n",errno);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
    if(argc!=3){
        printf("Usage: <programName> <numberOne> <numberTwo>\n");
        exit(EXIT_FAILURE);
    }

    int status;
    pid_t childPid;


    //Why do we use the magical number "2" here? Because we only receive two arguments. 
    //For a dynamic solution, just use (argc-1) and you're good to go
    for (int i=1; i<=2; i++){

        switch(fork()){
            case -1:
                perror("Error calling fork(): ");
                printf("Error code: %d\n", errno);
                exit(EXIT_FAILURE);

            case 0:
                calcFact(argv[i]);
                exit(EXIT_SUCCESS);
        }

        sleep(1);


    }
     

     //Father process
     //Once again, if you want to make it dynamic, remember, argc-1
    for(int i=0; i<2; i++){
        childPid=wait(&status);

        if(childPid>0){
            if(WIFEXITED(status)){
                printf("Child %d exited succesfully. Status code: %d\n", childPid, WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status)){
                printf("Child %d killed. Status code: %d\n", childPid, WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("Child %d was stopped. Status code: %d\n", childPid, WSTOPSIG(status));
            }
        }
        else{
            perror("Error when calling wait(): ");
            printf("Error code: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }





    return 0;
}
