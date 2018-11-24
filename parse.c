#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

//parses a single command
char ** parse_args( char * line ) {
  char ** arr = malloc(5 * sizeof(char *));
  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    //line = strip_string(line);
    i++;
  }
  return arr;
}


//strips string of unwanted whitespace
char * trim(char * line){
  //strips whitespace in beginning of string
  while((*line) == ' '){
    line++;
  }

  char * end = line+strlen(line)-1;
  int whitespace = 0;

  while(end > line && (*end) == ' '){
    end--;
    whitespace++;
  }
  
  char * newStr = calloc(1, strlen(line)-whitespace);
  strncpy(newStr, line, strlen(line)-whitespace);
  
  return newStr;
}
