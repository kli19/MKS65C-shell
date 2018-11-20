#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>
# include <sys/wait.h>
# include <fcntl.h>

char ** parse_args( char * line) {
  char ** arr = malloc(5 * sizeof(char *));
  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    i++;
  }
  return arr;
}


int main(){
  while(1){
    int f = fork();

    if(f==-1){
      printf("error");
    }

    if(f==0){
      char line[100];
      scanf("%[^\n]%*c", line);
      char ** args = parse_args(line);  
      execvp(args[0], args);
    }

    int status;
    wait(&status);
  }
  return 0; 
} 
