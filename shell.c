#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
# include <sys/wait.h>
# include <fcntl.h>

//parses a single command
char ** parse_args( char * line ) {
  char ** arr = malloc(5 * sizeof(char *));
  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    i++;
  }
  return arr;
}


//strips string of unwanted whitespace
char * strip_string(char * line){
  //strips whitespace in beginning of string
  while((*line) == ' '){
    line++;
  }
  return line;
}

//executes commands
void execute(){
  //allocates space to read in commands
  char * line = malloc(5 * sizeof(char));
  scanf("%[^\n]%*c", line);

  //so the code doesn't break when there is no command
  if(!line){
    return;
  }
 
  while(line){
    //separates the line into individual commands
    char * command = strsep(&line, ";");

    //strip the unwanted whitespace
    command = strip_string(command);

    //if the command is cd
    if (!strncmp("cd ", command, 3)){
      chdir(command+3);
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
    printf("shell$: ");
    execute();
  }

  return 0;
}
