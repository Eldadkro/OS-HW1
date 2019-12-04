#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>


#define N 3
#define M 100

//parseIn is a function that deduse the command to arguments 
//input: input from command-line , vector of command 
//output: puts in the vector the command to interpet , returns the command size or -i if too long
int parseIn(char input[M], char **vector);


int main(){
    char* argv[N+1];
    char t[N+1][M] = {0};
    for(int i=0;i<N+1;i++)
        argv[i] = &t[i];
    int tmp;
    int i;
    char buffer[M],con;
    printf("Shell2$** ");
    int size = gets(buffer);
    printf(buffer);
    while(strcmp("Esc",buffer) != 0){
        size = parseIn(buffer,argv);
        if(size < 2 || size == -1){
            printf("invalid command\n");
            printf("Shell2$** ");
            gets(buffer);
            continue;
        }
        int pid =(int)fork();
        if(pid == 0){
            execvp(argv[0],argv);
            printf("ERROR running program\n");    
        }
        wait(&tmp);
        printf("Shell2$** ");
        gets(buffer);
    }

    execl("shell",NULL);
    return 0;
}


int parseIn(char input[M], char **vector){

   const char s[2] = " ";
   char *token;
   int i=0;
   /* get the first token */
   token = strtok(input, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
        vector[i] = token;
        token = strtok(NULL, s);
        i++;
        if(i >= N+1)
            return -1;
   }
    vector[i] = NULL;
    return i;    
}
