#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
# include <sys/wait.h>
# include <fcntl.h>

char ** parse_args( char * line ) {
  //printf("Went to parse_args\n");
  char ** arr = malloc(5 * sizeof(char *));
  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    i++;
    //printf("While works in parse_args\n\n");
  }
  return arr;
}

void execute(){
  char * line = malloc(5 * sizeof(char));
  scanf("%[^\n]%*c", line);

  while(line){
    char * command = strsep(&line, ";");
    char ** args = parse_args(command);
    int f = fork();
    if(f==-1){
      printf("error");
    }

    if(f==0){
      execvp(args[0], args);
    }
    int status;
    wait(&status);
  }
}


int main(){
  while(1){
    int f = fork();
    
    if(f==-1){
      printf("error");
    }

    if(f==0){
      printf("Enter Command: ");
      execute();
    }

    int status;
    wait(&status);
  }

  return 0;
}
