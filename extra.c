#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <dirent.h> //to read driectory info
#include <termios.h> //for getch()
#include <errno.h>
#include "extra.h"
#include "parse.h"
#include "shell.h"

//lists all the files in directory
char ** listFiles(char * path){
  char ** list = malloc(100 * sizeof(char *));
  int i = 0;
  DIR * d;
  d = opendir(path);
  //printf("OPENED\012");
  struct dirent * entry;
  entry = readdir(d);
  if (strcmp(entry->d_name, ".DS_Store") != 0){
    while (entry){
      if (entry->d_type == DT_DIR){
        // printf("%s \104irectory: %s\012", path ,entry->d_name);
        // printf("%s \n",entry->d_name);
        list[i] = entry->d_name;
        i++;

        //Recursive portion for sub direcories
        // if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0){
        //   listFiles(entry->d_name);
        // }

      }
      else {
        // printf("File: %s\012", entry->d_name);
        // printf("%s\n",entry->d_name);
        list[i] = entry->d_name;
        i++;
      }
      entry = readdir(d);
    }
  }
  closedir(d);
  return list;
}

//parses a single command
char * split( char * line ) {
  char ** arr = malloc(100 * sizeof(char *));
  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    //line = strip_string(line);
    i++;
  }
  return arr[i - 1];
}


char * tabby(char * line, int a){
  char * current = split(line);
  printf("THE CURRENT LINE: %s \n", current);
  int counter = 0;
  char * ans = (char *) malloc(sizeof(char *));
  char * cptr = (char *) malloc(sizeof(char *));
  char * final = (char *) malloc(sizeof(char *));

  //to get the final portion of the commandline
  char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);
  char ** list = listFiles(cwd);
  int i = 0;
  //
  printf("VALUE OF A:%d\n", a);

  while (list[i]){
    cptr = strstr(list[i], current);
    if (cptr){
      if (strcmp(cptr, list[i]) == 0){
        // printf("CPTR: %s", cptr);
        // printf ("%d", strcmp(cptr, list[i]) );
        strcpy(ans, list[i]);
        if (!a){
          printf("%s  ", ans);
        }
        counter++;
      }
    }
    i++;
  }
  if (counter > 1){
    return "multiple";
  } else if (counter == 1){

    // printf("CUR: %s\n", current);
    // printf("LENGTH %lu\n", strlen(current));
    final = ans + strlen(current);
    // printf("FINAL: %s\n", final);

    free(cptr);
    if (a){
      return final;
    } else{
      return "true";
    }
  } else {
    return "";
  }
}


int getch(){
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

char * keyFinder(char * current, int a){
  int char1;
  // printf("PRESS A KEY TO CONTINUE \n");
  char1 = getch();
  printf("%d\n", char1);

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
  } else if (char1 == 10){ //enter key
    // printf("end\n");
    return "end";
  } else if (char1 == 127){ //backspace key
    // printf("backspace\n\n");
    return "back";
  } else if (char1 == 9){ //tab key
    printf("the tab\n");
    return tabby(current, a);
    // return "tab";
  } else if (char1 == 32){ //the space
    printf("THE SPACE\n");
    // char * spa = malloc(sizeof(char1));
    // strcpy(spa, "  ");
    return "space";
  } else { //char keys
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

//
// int main(){
//   keyFinder();
//   return 0;
// }
