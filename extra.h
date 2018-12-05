#ifndef INCL_EXTRA
#define INCL_EXTRA

char * tabby(char * line, int a);
int getch();
void history(char * line);
char * keyFinder(char * current, int a);
char * split( char * line );
char ** listFiles(char * path);
char * removeLast(char* name);

#endif
