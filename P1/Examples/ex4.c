#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(){

    pid_t pid, childpid;
    int status;
    pid=fork();
    switch(pid){

        case -1: //error
            perror("Fork error: ");
            printf("Error code: %d\n", errno);
            exit(EXIT_FAILURE);
            break;
        
        case 0: //Father and child process
            printf("Father process: %ld\nChild process: %ld\n", (long)getppid(), (long)getpid());
            if(execlp("ls", "ls", "-l", NULL)==-1){ //We execute ls -l. The parameters are: file name, path(in this case is declared in the PATH variable), and arguments (don't forget to nullify the last parameter)
                printf("Error executing ls -l.\n");
                printf("Error code: %d", errno);
                perror("Error: ");
                exit(EXIT_FAILURE);
            }
            break;
        
        default: //Father process only
            printf("Father process: %ld\n",(long)getppid());

            childpid=wait(&status);
            if(childpid>0){
                if(WIFEXITED(status)){
                    printf("Child %d exited succesfuly. Status code: %d\n", getppid(), WEXITSTATUS(status));
                }
                else if(WIFSTOPPED(status)){
                    printf("Cild %d stopped. Status code: %d\n", getppid(), WSTOPSIG(status));
                }
                else if(WIFSIGNALED(status)){
                    printf("Child %d killed. Status code: %d\n", getppid(), WTERMSIG(status));
                }
            }
            else{
                printf("Error summoning wait()\n");
                exit(EXIT_FAILURE);
            }
    }
    printf("End of the program. PID of the process executing this line: %ld.\n", (long)getpid());
    return 0;

}