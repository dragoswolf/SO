#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    pid_t pid, childPid;
    int status;
    
    int var =1; //We will change the variable inside the child process and then outside of it as well.

    pid=fork();

    switch(pid){
        case -1:
            perror("Error: ");
            printf("Error code: %d\n", errno);
            exit(EXIT_FAILURE);
            break;

        case 0:
            printf("Child ID: %ld\n", (long)getppid());
            var=5;
            printf("Var is %d\n", var);
            sleep(5);
            exit(0); //This method also accepts an int number which will be returned as the status code. Any int will go

        default:
            sleep(1); //we are giving the child process a second to wrap up everything

            childPid=wait(&status);
            if(childPid>0){
                if(WIFEXITED(status)){
                    printf("Child %ld succesfully exited. Status code: %d\n", (long)getpid(), WEXITSTATUS(status));
                }
                else if(WIFSTOPPED(status)){
                    printf("Child %ld stopped. Status code: %d\n", (long)getpid(), WEXITSTATUS(status));
                }
                else if(WIFSIGNALED(status)){
                    printf("Child %ld killed. Status code: %d\n", (long)getpid(), WTERMSIG(status));
                }
            }
    }
    printf("Program terminated succesfully. Variable is %d. Process ID executing this line is %ld.\n", var, (long)getppid());
    exit(EXIT_SUCCESS);

    /*
    *
    * As we will see once the program is executed, we change the variable inside the child process,
    * but the variable outside the child process will remain being the same as the one declared at the beginning.
    * 
    */
}