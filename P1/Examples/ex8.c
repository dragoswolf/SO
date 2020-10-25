/*
*
*   This program will test the catching and processing of the signal sent by ctrl+c
*   We will need a controller function which will take the signal.
*   The controller function will take the signal by default.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


//* Prototyping
void controller(int);



int main(void)
{
    if(signal(SIGINT, controller)==SIG_ERR){
        perror("Signal Error: ");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(1){
        pause();
    }
}



void controller(int signCode){
    printf("\nYou will not exit this program with CTRL+C.\nIn order to exit, use CTRL+Z\n");
    printf("Signal code: %d\n", signCode);
}

