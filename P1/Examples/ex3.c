#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main(){

    printf("Variables de entorno:\n");
    for (int i=0; environ[i]!=NULL; i++){
        printf("environ[%d]=%s\n", i, environ[i]);
    }

    // Now we will summon a specific enviromental variable
    printf("\n\n\n");

    char *home=NULL;

    home=getenv("HOME"); //We get the variable with the "getenv()" function. We need to pass it the name of the variable

    if(home==NULL){
        printf("There is no defined \"$HOME\" variable.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("$HOME value is %s\n", home);
    }
}