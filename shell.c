#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include "shell.h"
#include "parse.h"

//executes commands
void execute(){
  //allocates space to read in commands
  char * line = malloc(5 * sizeof(char));
  scanf("%[^\n]%*c", line);

  while(line){
    //separates the line into individual commands
    char * command = strsep(&line, ";");

    //strip the unwanted whitespace
    command = trim(command);

    //if the command is cd
    if (!strncmp("cd ", command, 3)){
      chdir(command+3);
    }

    //if the command is exit
    if (!strncmp("exit", command, 4)){
      exit(0);
    }

    else{
      //read the arguments of the command into an array
      char ** args = parse_args(command);
      int f = fork();

      //something went wrong with forking
      if(f==-1){
	printf("error");
      }

      //execute the command in the child process
      if(f==0){
	execvp(args[0], args);
      }

      //wait until the child process is done
      int status;
      wait(&status);
    }
  }
}


int main(){
  while(1){
 
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);
    printf("my_shell:~%s$ ", cwd);
    execute();

  }

  return 0;
}
