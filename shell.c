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

char * strip_string(char * line){
  //strips whitespace in beginning of string
  while((*line) == ' '){
    line++;
    //printf("%s\n", line); 
  }
  return line;
}

void execute(){
  char * line = malloc(5 * sizeof(char));
  scanf("%[^\n]%*c", line);

  if(!line){
    return;
  }

  while(line){
    char * command = strsep(&line, ";");
    command = strip_string(command);
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
  printf("%s\n", strip_string("      hello"));
  while(1){
    int f = fork();
    
    if(f==-1){
      printf("error");
    }

    if(f==0){
      printf("Enter Command: ");
      execute();
      return f;
    }

    int status;
    wait(&status);
  }

  return 0;
}
