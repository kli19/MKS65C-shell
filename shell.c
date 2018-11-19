#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>


char ** parse_args( char * line) {
  char ** arr = malloc(5 * sizeof(char *));

  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    i++;
  }

  return arr;
}


int main(){
  char line[100]="ls -a -l --color";
  //scanf("%s", line);
  char ** args = parse_args(line);
  
  execvp(args[0], args);
      
  return 0; 
} 
