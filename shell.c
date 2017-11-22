#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

char ** parse_args( char * line, char * parse_for ) {
    char** args = (char **)calloc(6, sizeof(char *));
    int i;
    for(i = 0; line; i++) {
        args[i] = strsep(&line, parse_for);
    }
    args[i] = NULL;
    return args;
}

int main(int argc, char *argv[]) {
  while (1) {
    printf("Input a command\n");
    char command[256];
    fgets(command, 256, stdin);
    char **args = parse_args(command, "\n");//removing newlines from fgets retval

    args = parse_args(command, " "); //parses through the string by " "
    
    if (!fork()) { //child process
      execvp(args[0], args);  
    }
    else { //parent process
      int status;
      waitpid(-1, &status ,0);
    }
  }

  return 0;
  
}
