/*

    This program will make alarms. That's it.

    Oh and it will print "RING" on the screen.


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int counter=0; //unfortunately, we need a global variable for this one

void controller();
void alarmFunc(int);


int main(int argc, char *argv[])
{
    if(signal(SIGALRM, controller)==SIG_ERR){
        perror("Signal error: ");
        fprintf(stderr, "Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    alarmFunc(5);
    alarmFunc(3);
    for(;;) alarmFunc(1);



    return 0;
}


void controller(){
    printf("RING\n");

    counter ++;

    if(counter==4){
        kill(getpid(), SIGKILL);
    }
}

void alarmFunc(int seconds){
    alarm(seconds);
    pause();

    //return(alarm(0));
}

