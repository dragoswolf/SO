#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
*
*   Test this program with ./ex5 tar -cf file1 file2 fileN
*
*/

int main(int argc, char **argv){
   pid_t pid, childPid;
   int status;
   pid=fork();

   switch(pid){
        case -1:
            perror("Error: ");
            printf("Error code: %d.\n", errno);
            exit(EXIT_FAILURE);
            break;

        case 0:
            printf("\nCHILD PROCESS:\n");
            printf("Child ID: %ld\n", (long)getpid());

            //This time, we will be using execvp. Let's explain the parameters:
            /*
            *
            * This method takes two parameters:
            *   1: const char *file
            *       This will be the name of the file we want to execute.
            *   2: char *const argv[]
            *       This will be an array containing all the arguments we want to pass to the program we're calling
            *       through the method.
            *  
            */

            if(execvp(argv[1], &argv[1])<0){
               perror("Error: ");
               printf("Error code: %d\n", errno);
               exit(EXIT_FAILURE);
            }
            /*
            *
            * NOTHING WILL EXECUTE FROM HERE ON, NOT EVEN THE BREAK
            * The reason for that is that execvp() replaces this child with the program we're summoning
            * Once the program is finished, it will not retake the child where it was left, instead
            * it terminates it and returns a status code.  
            * 
            */
            break;
        
        default:
            printf("FATHER PROCESS.");
            printf("\nFather ID: %ld\n", (long)getppid());

            childPid=wait(&status);

            if(childPid>0){
                if(WIFEXITED(status)){
                    printf("Child %ld exited succesfully. Status code: %d.\n", (long)getpid(), WEXITSTATUS(status));
                }
                else if(WIFSTOPPED(status)) {
                    printf("Child %ld stopped. Status code: %d\n", (long)getppid(), WEXITSTATUS(status));
                }
                else if(WIFSIGNALED(status)){
                    printf("Child %ld killed. Status code: %d\n", (long)getppid(), WTERMSIG(status));
                }
            }
   }
   printf("Program terminated. Process executing this line: %ld\n", (long)getppid());
   exit(EXIT_SUCCESS); 
}