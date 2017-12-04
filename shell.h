#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>

char ** parse_args( char *, char *);
int run( char * , char ** );
void exit_cmd( char *);
void cd( char **);
char * trim(char *);
void redirect_out(char *args[256]);
int piping(char *args[256]);
void execute();
