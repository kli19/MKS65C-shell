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

int my_pipe(char * command){
  //make copy of files 0 and 1
  int stdout_fd = dup(STDOUT_FILENO);
  int stdin_fd = dup(STDIN_FILENO);

  //reset
  dup2(stdout_fd, STDOUT_FILENO);
  dup2(stdin_fd, STDIN_FILENO);
}
