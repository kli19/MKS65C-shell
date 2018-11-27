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
void execute(char * line){
  if(line[0]==0){
    strcat(line, " ");
  }

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
      else{
	int status;
	wait(&status);
      }
    }
  }
}


int main(){
      
  //allocates space to read in commands
  char * line = malloc(100 * sizeof(char));
  
  //prints path
  char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);
  
  while(1){
    printf("my_shell:~%s$ ", cwd);
    fgets(line, 100, stdin);
    execute(line);
       
  }
  

  return 0;
}
