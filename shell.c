#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>


int main(){

    int tmp;
    char buffer[100];
    printf("Shell$** ");
    scanf("%s",&buffer);
    while(strcmp("Exit",buffer)){
        if(strcmp("shell1",buffer) == 0)
            execl("shell1",NULL);
        else if(strcmp("shell2",buffer) == 0)
            execl("shell2",NULL);
        else if(strcmp("shell3",buffer) == 0)
            execl("shell3",NULL);
        else
            printf("Invalid input\n");
        printf("shell$** ");
        scanf("%s",&buffer);
    }
    return 0;
}