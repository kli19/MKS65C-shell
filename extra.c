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

char * keyFinder(){
  int char1;
  // printf("PRESS A KEY TO CONTINUE \n");
  char1 = getch();

  if (char1 == 27) { // checks to see if scrollkey was pressed
    // determines the key
    int char2, char3;
    char2 = getch();
    char3 = getch();

    switch(char3)
    {
      case 65: printf("UP KEY\n"); return "up"; break;
      case 66: printf("DOWN KEY\n"); return "down"; break;
      // case 67: printf("RIGHT KEY\n"); return "right"; break;
      // case 68: printf("LEFT KEY\n"); return "left"; break;

      default:
      printf("ERROR OTHER SCROLLKEY: %d %d %d\n", char1, char2, char3); break;
    }
  } else if (char1 == 10){
    // printf("end\n");
    return "end";
  } else if (char1 == 127){
    // printf("backspace\n\n");
    return "back";
  } else if (char1 == 9){
    printf("the tab\n");
    return "tab";
  } else {
  // printf("key pressed: %d %c\n", char1, char1);
  char * ans = malloc(sizeof(char1));
  ans[0] = char1;
  printf("%s", ans);
  return ans;
  }
  return "alex";
}

char * removeLast(char* name){
  int i = 0;
  for (i = 0; i< strlen(name); i++){
    if(i > 1){
      name[i- 1] = '\0';
    }
  }
  return name;
}

//
// int main(){
//   keyFinder();
//   return 0;
// }
