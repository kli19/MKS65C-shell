#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
# include <sys/wait.h>
# include <fcntl.h>

char ** parse_args( char * line ) {
  printf("Went to parse_args\n");
  char ** arr = malloc(5 * sizeof(char *));
  int i = 0;
  while(line){
    arr[i] = strsep(&line, " ");
    i++;
    printf("While works in parse_args\n\n");
  }
  return arr;
}

char *** multi_cmd( char * line, char *** ans ){
  printf("Went to multi_cmd ");
  int i = 0;
  ans[0][0] = line;
  if (strchr(line, ';')){
    printf("\nIn if statement!!!! ");
    while(line){
      printf("While works in multi_cmd  ");
      ans[i][0] = strsep(&line, ";");
      printf("%s\n", ans[i][0]);
      i++;
    }
  }
  printf("Evaluated\n" );
  return ans;
}

char *** finalCmd( char * line ){
  // ,printf("%s\n", line);

  // saving memory
  char *** arr = (char ***) malloc(4 * sizeof(char ***));
  for (int i = 0; i< 4; i++) {

    arr[i] = (char **) malloc(20*sizeof(char *));

    for (int j = 0; j < 20; j++) {

      arr[i][j] = (char *)malloc(20*sizeof(char));
    }

  }

  //
  int i = 0;
  arr = multi_cmd(line, arr);
  while (arr[i] || !i){
    printf("While1 works in finalCmd\n\n");

    char * temp = arr[i][0];
    arr[i] = parse_args(temp);
    // int j = 0;
    // while (arr[i][j] || !j){
    //   printf("While2 works in finalCmd\n\n");
    //   printf("%s\n", arr[i][j]);
    //   j++;
    // }
    printf("%dth COMMAND: %s\n", i, arr[i][0]);
    execvp(arr[i][0], arr[i]);
    i++;
  }
  printf("End of finalCmd\n");
  return arr;
}


int main(){
            // char *** test = malloc(100 * sizeof(char *));
            // char * hel = "hello";
            // printf("Init works\n");
            // test[0][0] = hel;
            // printf("entering works\n");
            // printf("%s\n", test[0][0]);
  while(1){
    int f = fork();

    if(f==-1){
      printf("error");
    }

    if(f==0){
      char line[100];
      printf("Enter Command: ");
      scanf("%[^\n]%*c", line);
      // char ** args = parse_args(line);
      // execvp(args[0], args);
      finalCmd(line);
    }

    int status;
    wait(&status);
  }
  return 0;
}
