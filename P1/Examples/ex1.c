/*
*
*   This example will be about creating a child process and identifying IDs.
*
*/


//=========================== INCLUDES ============================
#include <sys/types.h>
/*
*
* We will need this include in order to summon pid_t type.
* pid_t will be used in order to declare the processes themselves.
*
*/

#include <unistd.h>
/*
*
* This library has the necessary functions in order to work with processes.
* The function we'll use here is 'fork()' which is from this library.
*
*/

#include <sys/wait.h>
/*
*
* This library will give us the necessary function for error handling support.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


//=================================================================


//=========================== MAIN ============================

int main(int argc, char const *argv[])
{
    pid_t pid, childPid;
    int status; //we will use this to check on the process

    // First, we shall fork the main process:
    pid=fork();

    // Now, we must check if the fork has concluded succesfully.

    switch(pid){

        case -1:
            perror("Fork error: ");
            printf("Error code: %d\n", errno);
            exit(EXIT_FAILURE);

        case 0: // Forked (child) process
            printf("\n\n\tCASE 0\n");
            printf("Child process ID: %d\nFather process ID: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
            /*
            *
            *   getpid(): retrieves the ID for the forked (child) process.
            *   getppid(): retrieves the ID for the father of the forked process. 
            * 
            */

        default: // Father process
            printf("\n\n\tDEFAULT\n");
            printf("Father process: %d\nFather of father process: %d\n", getpid(), getppid()); //here we find out who's the father of the father process.

            childPid=wait(&status);

            if(childPid>0){
                if(WIFEXITED(status)){ //child exited succesfully
                    printf("Child %d exited succesfully. Status: %d\n", childPid, WEXITSTATUS(status));
                }
                else if(WIFSIGNALED(status)){ //child killed by signal
                    printf("Child %d killed by signal %d.\n", childPid, WTERMSIG(status));
                }
                else if(WIFSTOPPED(status)){ //child stopped
                    printf("Child %d stopped by signal %d.\n", childPid, WSTOPSIG(status));
                }

            }

            else{
                perror("Error summoning wait: ");
                printf("Error code: %d\n", errno);
                exit(EXIT_FAILURE);
            }

            //If everything went ok, we will exit the program from the default
            exit(EXIT_SUCCESS);
    
    }
}

/*
*
*   Let's talk about process completion status macros.
*   
*   WIFEXITED: Returns a non-zero value if the child terminated normally.
*   WEXITSTATUS: If WIFEXITED is true, this macro returns the status code.
*
*   WIFSIGNALED: Returns a non-zero value if the child terminated because of a not handled signal.
*   WTERMSIG: If WIFSIGNALED is true, this macro returns the status code.
*
*   WCOREDUMP: Returns a non-zero value if the child terminated and produced a core dump.
*   
*   WIFSTOPPED: Returns a non-zero value if the child was stopped.
*   WSTOPSIG: If WIFSTOPPED is true, this macro returns the status code.
*
*/


//=================================================================

/*
*
* Another way of doing this would be with if statements instead of switch statements (obviously)
* As we already know, whenever we create a process and fork it, the father will receive
* the son PID while the son will receive PID=0
* Knowing this, we can make an if statement in order to work with processes.
*
*/

/*
*
*   if(pid == -1){
*       Error forking    
*   }
*   else if(pid==0){
*       Child process 
*   }
*   else{
*       Father process 
*   }
*
*/
