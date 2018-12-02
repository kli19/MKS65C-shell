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

int redirect(char * command, int * fd){

  //make copy of files 0 and 1
  int stdout_fd = dup(STDOUT_FILENO);
  int stdin_fd = dup(STDIN_FILENO);
  
  int files[3] = { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
  int flags[3] = {O_CREAT|O_WRONLY|O_TRUNC, O_APPEND|O_CREAT|O_WRONLY, O_RDONLY};

  char * command_symbol = redirect_symbol(command);
  
  char * command1 = malloc(10);
  char * command2 = malloc(10);
  
  //printf("command: %s\n", command);
  
  strcpy(command1, command);
  command1 = trim(strsep(&command1, command_symbol));
  //printf("command1: %s\n", command1);
  
  char ** temp = parse_args(command);
  while(*temp && *(temp+1)){
    if (strstr(*temp, command_symbol)){
      command2 = *(temp+1);
    }
    temp++;
  }
  //printf("command2: %s\n", command2);

  //printf("fd: %d\n", *fd);
  //printf("direction: %d\n", files[direction(command_symbol)]);
 
  *fd = open(command2, flags[flag(command_symbol)], 0777);
  dup2(*fd, files[direction(command_symbol)]);
  execute(command1);
  
  //reset
  dup2(stdout_fd, STDOUT_FILENO);
  dup2(stdin_fd, STDIN_FILENO);
  return *fd;
}

char * redirect_symbol(char * command){
  char * symbol = 0;
  if (strstr(command, ">")){
    symbol = ">";
  }
  if (strstr(command, "<")){
    symbol = "<";
  }
  if (strstr(command, ">>")){
    symbol = ">>";
  }
  /*
  if (strstr(command, "<<")){
    symbol = "<<";
  }
  */
  return symbol;

}

int direction(char * symbol){
  if (!strcmp(symbol,">") || !strcmp(symbol, ">>")){
    return 1;
  }
  return 0; 
}

int flag(char * symbol){
  if (!strcmp(symbol,">")){
    return 0;
  }
  if (!strcmp(symbol,">>")){
    return 1;
  }
  return 2;
}
