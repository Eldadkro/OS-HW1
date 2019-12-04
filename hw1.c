#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define N 3
#define M 100

void shell();
void shell1();
void shell2();
void shell3();

//parseIn is a function that deduse the command to arguments 
//input: input from command-line , vector of command , maximum argument of a command
//output: puts in the vector the command to interpet , returns the command size or -i if too long
int parseIn(char input[M], char **vector,int n);

//
//
int copyF(char **argv,int n);

int deleteF(char **argv,int n);

int main(){
    shell();
}


void shell(){
    int tmp;
    char buffer[100];
    printf("\nEnter <shell1> to run linux commands without parameters\n");
	printf("Enter <shell2> to run linux commands with parameters\n");
	printf("Enter <shell3 to> run commands to file editing\n");
	printf("Shell$** ");
    gets(buffer);
    while(strcmp("Exit",buffer)){

        if(strcmp("shell1",buffer) == 0)
            shell1();
        else if(strcmp("shell2",buffer) == 0)
            shell2();
        else if(strcmp("shell3",buffer) == 0)
            shell3();
        else
            printf("Invalid input\n");
        printf("shell$** ");
        scanf("%s",&buffer);
    }
    exit(0);
}


void shell1(){
    int tmp;
    char buffer[100];
    char *argv[2];
    printf("Shell1$** ");
    gets(buffer);
    while(strcmp(buffer,"esc")){
        int size = parseIn(buffer,argv,1);
        if(size != 1){
            printf("invalid command\n");
            printf("Shell1$** ");
            gets(buffer);
            continue;
        }
        int pid =(int)fork();
        if(pid == 0){
            execvp(argv[0],argv);
            printf("ERROR ERROR ERROR\n");    
        }
        wait(&tmp);
        printf("Shell1$** ");
        gets(buffer);
    }

    shell();
}


void shell2(){

    char* argv[N+1];
    int tmp;
    int i;
    char buffer[M],con;
    printf("Shell2$** ");
    int size = gets(buffer);
    while(strcmp("esc",buffer) != 0){
        size = parseIn(buffer,argv,N);
        if(size < 2 || size == -1){
            printf("Not Supported\n");
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

    shell();
}


int parseIn(char input[M], char **vector, int n){

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
        if(i > n)
            return -1;
   }
    vector[i] = NULL;
    return i;    
}

void shell3(){
    char **argv;
    char buffer[M];
    printf("shell3$** ");
    gets(buffer);
    while(strcmp("esc",buffer)){
        int size = parseIn(buffer,argv,3);
        if(strcmp(argv[0],"copy") == 0)
            copyF(argv,size);
        else if(strcmp(argv[0],"delete") == 0)
            deleteF(argv,size);
        else 
            printf("Not Supported\n");
        printf("shell3$** ");
        gets(buffer);
    }
    shell();
}


int copyF(char **argv,int n){

    char buffer[2];
    int output,input;

    if(n<2){
        printf("not enough arguments\n");
        return -1;
    }
    if(n == 2)
        output = 1;
    else
        if((output = open(argv[2],O_CREAT|O_WRONLY,S_IRWXU|S_IRWXG|S_IRWXO)) == -1){
            printf("couldn't open output file\n");
            return -1;
        }
    
    if((input = open(argv[1],O_RDONLY)) == -1){
        printf("couldn't open input\n");
        return -1;
    }
    while(read(input,buffer,1) != 1){
            write(output,buffer,1);
    }  
}

int deleteF(char **argv,int n){
    if(n == 1){
        printf("not enough arguments");
        return -1;
    }
    return remove(argv[1]);
}


