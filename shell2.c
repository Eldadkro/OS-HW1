#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>

#define N 3
#define M 100

//parseIn is a function that deduse the command to arguments 
//input: input from command-line , vector of command , sizes n*m of the vector and k size of input
//output: puts in the vector the command to interpet , returns the command size 
int parseIn(char input[M], char *(vector[M]));

//copy from src to dest till space or end of string and put '\0' in the end
//output: i>0 is the amount copied 
//        i = -1 if it is the end of the string and their is nothing left
int copyTillSpace(char *src,char *dest);

//input: string that starts with spaces
//output: i>0 is the first acurence of contant after the space 
//        i = -1 if it is the end of the string and their is nothing left
int skipSpace(char *src);


int main(){
    char **argv =(char**)malloc(sizeof(char*)*N);
    for(int i=0;i<N;i++)
        argv[i] = (char*)malloc(sizeof(char)*M);
    int tmp;
    int i;
    char buffer[M];
    printf("Shell2$** ");
    scanf("%s",&buffer); 
    while(strcmp("Esc",buffer) != 0){
        
        int size = parseIn(buffer,argv);
        int pid =(int)fork();
        if(pid == 0){
            execvp(buffer,argv);
            printf("ERROR running program\n");    
        }
        wait(&tmp);
        printf("Shell2$** ");
        scanf("%s",&buffer);
    }

    execl("shell",NULL);
    for(int i=0;i<N;i++)
        free(argv[i]);
    free(argv);
    return 0;
}

int parseIn(char input[M], char *(vector[M])){
    int i=0;
    int step;
    
    while(i < N-1){
        step = skipSpace(input);
        if(step == -1)
            break;
        input = input + step;
        if((step = copyTillSpace(input,vector[i])) == -1)
            break;
        input += step;
        i++;
    }
    vector[i] = NULL;
    return i;
    
}


int skipSpace(char *src){
    int i=0;
    while(src[i] == ' ' && i<N){
        i++;
    }
    if(src[i] == '\0')
        return -1;
    return i;
}

int copyTillSpace(char *src,char *dest){

    int i=0;
    while(src[i] != ' ' && src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    if(src[i] == '\0')
        return -1;
    return i;
}