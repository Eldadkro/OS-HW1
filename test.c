#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>

#define N 3
#define M 100

int parseIn(char input[M], char **vector){
    int i=0;
    int step;
    
    while(i < N){
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

int main(){
    char buffer[100] = "ls -l";
    char* argv[N+1];
    char t[N+1][M] = {0};
    for(int i=0;i<N+1;i++)
        argv[i] = &t[i];
    parseIn;
}