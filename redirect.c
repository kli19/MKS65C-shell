#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "redirect.h"
#include "shell.h"

int redirect(char * command1, char * command2,  int * fd, int direction, int flag){
  //make copy of files 0 and 1
  int stdout_fd = dup(STDOUT_FILENO);
  int stdin_fd = dup(STDIN_FILENO);
  
  int files[3] = { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
  int flags[2] = {O_CREAT|O_WRONLY, O_APPEND|O_CREAT|O_WRONLY};
  
  printf("direction: %d\n", files[direction]);
  printf("flag: %d\n", flag);
  printf("command1: %s\n", command1);
  printf("command2: %s\n", command2);
  printf("fd: %d\n", *fd);
  
  *fd = open(command2, flags[flag], 0777);
  dup2(*fd, files[direction]);
  execute(command1);
  
  //reset
  dup2(stdout_fd, STDOUT_FILENO);
  dup2(stdin_fd, STDIN_FILENO);
  return *fd;
}

int direction(char * symbol){
  if (!strcmp(symbol,">") || !strcmp(symbol, ">>")){
    return 1;
  }
  return 0; 
}

int flag(char * symbol){
  if (!strcmp(symbol,">") || !strcmp(symbol, ">>")){
    return 0;
  }
  return 1; 
}
