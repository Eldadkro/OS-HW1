#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>


/*  TODO:
        1) check valid input in function CheckIn(char str[],int n);
        1.1) use strchr(S,char) =(pointer to first acurance) look for space 
                in order to determind more values then permited    
*/

int main(){

    int tmp;
    char buffer[100];
    printf("Shell1$");
    scanf("%s",&buffer); 
    while(strcmp(buffer,"exit")){
        
        if(strcmp("Esc",buffer) == 0)
            execl("shell",NULL);
        int pid =(int)fork();
        if(pid == 0){
            execlp(buffer,buffer,NULL);
            printf("ERROR ERROR ERROR\n");    
        }
        wait(&tmp);
        printf("Shell1$**");
        scanf("%s",&buffer);
    }

    
    return 0;
}