#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include "shell.h"
#include "parse.h"
#include "redirect.h"
#include "extra.h"
#include "pipe.h"

void execute(char * command){
  //read the arguments of the command into an array
  char ** args = parse_args(command);

  //fork to execute the command and return
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

//executes commands
void execute_all(char * line){
  if(line[0]==0){
    strcat(line, " ");
  }
  //for redirection
  int stdout_fd = dup(STDOUT_FILENO);
  int stdin_fd = dup(STDIN_FILENO);

  while(line){
    //separates the line into individual commands
    char * command = strsep(&line, ";");

    //strip the unwanted whitespace
    command = trim(command);

    //if the command is cd
    if (!strncmp("cd ", command, 3)){
      //skips the cd and find the path to input into chdir
      chdir(command+3);
    }

    //if the command is exit
    else if (!strncmp("exit", command, 4)){
      exit(0);
    }

    // for redirection
    else if (redirect_symbol(command)){
      int fd = 0;
      //printf("we are redirecting now\n");
      close(redirect(command, &fd));

    }

    // for piping
    else if (strstr(command, "|")){
      //printf("we are piping now\n");
      my_pipe(command);
    }

    else{
      execute(command);
    }
  }

  //reset redirection stuff
  dup2(stdout_fd, STDOUT_FILENO);
  dup2(stdin_fd, STDIN_FILENO);
}


int main(){

  //allocates space to read in commands
  char * line = malloc(100 * sizeof(char));
  int spa = 0;

  while(1){

    //prints path
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);
    if (isatty(0)){
      printf("my_shell:~%s$ ", cwd);
    }
    // while (1){
    //   char * temp = keyFinder(line, 0);
    //   char * tabu = tabby(line, 1);
    //   // printf("%s\n", temp);
    //   // if (strcmp(temp,"back") == 0){
    //   //   execute("clear");
    //   //   printf("\nmy_shell:~%s$ ", cwd);
    //   //   char * temp = malloc(sizeof(line));
    //   //   temp = removeLast(line);
    //   //   printf("BEFORE          \n");
    //   //   // strcpy(line, temp);
    //   //   line = temp;
    //   //   printf("AFTER          \n");
    //   //   printf("%s\n", line);
    //   // } else
    //   if (strcmp(temp,"multiple") == 0){
    //     // printf("%s\n", temp);
    //     // printf("%d\n", strcmp(temp,"multiple"));
    //     printf("\nPlease be more specific\n");
    //     break;
    //   }
    //   else if (strcmp(temp,"true") == 0){
    //     printf("%s\n", temp);
    //     printf("%d\n", strcmp(temp,"true"));
    //     printf("KEYFINDER 1: %s\n", tabu);
    //     strcat(line, tabu);
    //     printf("%s\n", line);
    //     break;
    //   }
    //   else if (strcmp(temp,"space") == 0){
    //     printf("SAPCE ADDED\n");
    //     // line[strlen(line)] = ' '; // overwrite null termination
    //     // line[strlen(line) + 1] = '\0'; // add a new null termination
    //     strcat(line, " .");
    //     spa = 1;
    //   }
    //   else if (strcmp(temp,"end")){
    //     // printf("TEMP: %s\n", temp);
    //     // printf("%d\n", strcmp(temp,"end"));
    //     if (spa){
    //       strcpy( line+strlen(line) + 1, temp );
    //       spa = 0;
    //     } else{
    //       strcat(line, temp);
    //     }
    //   }
    //   else {
    //     // printf("LINE: %s\n", line);
    //     break;
    //   }
    // }

    fgets(line, 100, stdin);
    //printf("\012");
    // printf("end line; %s\n", line);
    execute_all(line);
    //strcpy(line,"");
  }

  return 0;
}
