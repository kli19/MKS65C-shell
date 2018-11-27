#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "redirect.h"

int redirect(char * source,  int * fd, int direction, int flag){
  printf("%d%d\n", direction, flag);
  int files[3] = {STDOUT_FILENO, STDIN_FILENO, STDERR_FILENO};
  int flags[2] = {O_CREAT|O_WRONLY, O_APPEND|O_CREAT|O_WRONLY};
  *fd = open(source, flags[flag], 0777);
  dup2(*fd, files[direction]);
  return *fd;
}

int direction(char * symbol){
  if (symbol==">" || symbol==">>"){
    return 0;
  }
  return 1; 
}

int flag(char * symbol){
  if (symbol==">" || symbol==">>"){
    return 0;
  }
  return 1; 
}
