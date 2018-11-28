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

void retrieve(){
  int ch1, ch2;
  printf("PRESS A KEY TO CONTINUE \n");
  ch1 = getch();
  ch2 = 0;
  if (ch1 == 0xE0) { // a scroll key was pressed
    ch2 = getch();
    // determine what it was
    switch(ch2)
    {
      case 72: printf("UP WAS PRESSED\n"); break;
      case 80: printf("DOWN WAS PRESSED\n"); break;
      case 75: printf("LEFT WAS PRESSED\n"); break;
      case 77: printf("RIGHT WAS PRESSED\n"); break;
      // ... we can set also others like HOME, END, PGUP, PGDOWN, ...
      default:
      printf("SOME OTHER SCROLL KEY PRESSED: %d %d\n", ch1, ch2); break;
    };
  }
  else
  printf("key pressed: %d %c\n", ch1, ch2);
  system("pause");
}
