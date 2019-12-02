#include <string.h>
#include <stdio.h>



int parseIn(char* input, char **vector,int n,int m,int k){
    int i=0;
    int step;
    while(i < n-1){
        step = skipSpace(input,k);
        if(step == -1)
            break;
        input = input + step;
        k = k-step;
        if((step = copyTillSpace(input,vector[i])) == -1)
            break;
        input += step;
        k -= step;
        i++;

    }
    vector[i] = NULL;
    return i;
    
}


int skipSpace(char *src,int n){
    int i=0;
    while(src[i] == ' ' && i<n){
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
    char arg[3][100];
    char input[] = "ls -la";
    char arg[3][40] = {"ls","-l",NULL};
    char *vector[40] = arg;
    printf(vector[0]);
    printf(vector[1]);
    
}
