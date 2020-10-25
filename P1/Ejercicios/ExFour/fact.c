/*
    This program will take a number from the CLI and calculate its factorial.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for sleep()

void Factorial(int);


void Factorial(int number){
    if(number<3){
        printf("Input a number bigger than 2\n");
        exit(EXIT_FAILURE);
    }

    long fact=1;

    for (int i=1; i<=number; i++){
        fact*=i;
    }

    printf("Result is: %ld\n", fact);

}


int main(int argc, char *argv[])
{

    if (argc!=2){
        printf("Usage: <programName> <number>\n");
        exit(EXIT_FAILURE);
    }

    Factorial(atoi(argv[1]));
    
    return 0;
}


