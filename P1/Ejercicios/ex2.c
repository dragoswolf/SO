/*
    Exercise 2
    In this exercise we will "zombify" a process by creating one and killing it
    without allowing the father to take the exit code.
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>



int main(int argc, char *argv[])
{

    switch(fork()){
        case -1:
            printf("Fork error.\n"),
            perror("");
            printf("Error code: %d\n", errno);
            exit(EXIT_FAILURE);
            break;
        case 0:
            printf("Child %ld\nFather %ld\n", (long)getpid(), (long)getppid());
            exit(0);
            break;
        default:
            sleep(10); 
            /*
                While the father is asleep, we can check the child process with "ps -a"
                We will see that the child process is in zombie mode.
                The father will end without checking on the child process nor killing it.
                The init() process will take the child and kill it (jesus christ, this sounds soo evil)
            */
            exit(EXIT_SUCCESS);
    }
    printf("\nFather has ended. Child has been killed by init.\n");
    return 0;
}


