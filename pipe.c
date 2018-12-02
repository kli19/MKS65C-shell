#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "redirect.h"
#include "shell.h"
#include "parse.h"

void my_pipe(char * command){
  //make copy of files 0 and 1
  int stdout_fd = dup(STDOUT_FILENO);
  int stdin_fd = dup(STDIN_FILENO);

  int fds[2];
  pipe(fds);
  //printf("0: %d\n", fds[0]);
  //printf("1: %d\n", fds[1]);

  char * command_temp = malloc(10);
  strcpy(command_temp, command);
  
  char * command1 = malloc(10);
  command1 = trim(strsep(&command_temp, "|"));
  //printf("command1: %s\n", command1);  
  char * command2 = malloc(10);
  command2 = trim(command_temp);
  //printf("command2: %s\n", command2);
  char ** args1 = parse_args(command1);
  char ** args2 = parse_args(command2);
  
  //fork 
  int f = fork();

  //something went wrong with forking
  if(f==-1){
    printf("error");
  }

  //fork again in the first child so there are two children
  if(f==0){
    //printf("first child!\n");
    f = fork();

    //second child
    if (f==0){
      //printf("second child!\n");
      dup2(fds[1], STDOUT_FILENO);
      close(fds[0]);
      execvp(args1[0], args1);
    }

    else{
      //printf("first child again!\n");
      wait(NULL);
      dup2(fds[0], STDIN_FILENO);
      close(fds[1]);
      execvp(args2[0], args2);
    }
  }

  //wait until the child process is done
  else{
    int status = 0;
    close(fds[0]);
    close(fds[1]);
    wait(&status);
  }
 

  //reset
  dup2(stdout_fd, STDOUT_FILENO);
  dup2(stdin_fd, STDIN_FILENO);
}
