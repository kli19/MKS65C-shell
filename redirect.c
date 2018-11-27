#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "redirect.h"

int redirect(char * source, char * fd, int direction, int flag){
  int files[3] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
  int flags[2] = {O_CREAT|O_WRONLY, O_APPEND|O_CREAT|O_WRONLY};
  *fd = open(source, flags[flag]);
  dup2(*fd, files[direction]);
  return *fd;
}

