#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include "extra.h"


void tabby(char * line){

}

void history(char * line){
  /*
  O_RDONLY: read only, O_WRONLY: write only, O_RDWR: read and write,
  O_CREAT: create file if it doesn’t exist, O_EXCL: prevent creation if it already exists
  */
  size_t filedesc = open("history.txt", O_RDWR | O_CREAT);
  if(filedesc > 0){
      printf("file has been opened\n");
  }
  else{
    printf("error opening file\n");
  }

  // size_t write(int filedesc, const void *buf, size_t nbytes);
  if(write (filedesc, line, strlen(line)) >= 0){
    printf("file has been written\n");
  }
  else{
    printf("error writing file\n");
  }

  // size_t read (int fd, void* buf, size_t cnt);
  if(read (filedesc, line, strlen(line)) >= 0){
    printf("file has been read\n");
  }
  else{
    printf("error reading file\n");
  }

  if(close(filedesc) == 0){
    printf("file has been closed\n");
  }
  else{
    printf("error closing file\n");
  }
}

int getch(void){
  int ch;
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
  newt = oldt; /* copy old settings to new settings */
  newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
  ch = getchar(); /* standard getchar call */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
  return ch; /*return received char */
}

void keyFinder(){
  int char1, char2;
  printf("PRESS A KEY TO CONTINUE \n");
  char1 = getch();
  char2 = 0;
  while (1) { // checks to see if scrollkey was pressed
    char2 = getch();
    // determines the key

    switch(char2)
    {
      case 72: printf("UP WAS PRESSED\n"); break; //up ascii value = 72
      case 80: printf("DOWN WAS PRESSED\n"); break; //down ascii value = 80
      case 75: printf("LEFT WAS PRESSED\n"); break; //left ascii value = 75
      case 77: printf("RIGHT WAS PRESSED\n"); break; //right ascii value = 77

      default:
      printf("SOME OTHER SCROLL KEY PRESSED: %d %d\n", char1, char2); break;
    };
  }
  else
  printf("key pressed: %d %c\n", char1, char2);
}

int main(){
  keyFinder();
  return 0;
}
