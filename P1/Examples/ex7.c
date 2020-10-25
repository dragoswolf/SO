/*
*
*   In this program we will demonstrate the use of the alarm.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
*
*   This next #include will include the needed library for working with signals
*
*/
#include <signal.h>


//* Prototyping
void sigControl(int);
unsigned int alarmMethod(unsigned int);



//* This will be our controller function

void sigControl(int signStatus){
    printf("This is from the controller. It works.\n");
    printf("Signal code: %d\n", signStatus);
    return;
}

unsigned int alarmMethod(unsigned int seconds){

    alarm(seconds);
    pause();

    /*
    *
    * Let's explain how this function works.
    * alarm(nSeconds) is the function that will send the alarm signal after the counter reaches 0.
    * In the meanwhile, the program will continue to function until the counter reaches 0.
    * In order to avoid that, we pause() the program
    * The pause() function pauses the thread until a signal is received. The signal will be the alarm.
    * 
    */

    return(alarm(0)); //Turns off the timer and returns unslept time

}




int main(){

    //First, we will check if the signal doesn't receive any error and if our controler is capable of receive the signal
    if(signal(SIGALRM, sigControl)==SIG_ERR){
        perror("Error creating signal: ");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }


    printf("Alarm in 3 seconds...\n");
    alarmMethod(3);
    printf("Alarm in 2 seconds...\n");
    alarmMethod(2);

    printf("Program succesfully concluded\n");

    exit(EXIT_SUCCESS);
}