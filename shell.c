#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#define READ 0
#define WRITE 1


char ** parse_args( char * line, char * parse_for ) {
    char** args = (char **)calloc(6, sizeof(char *));
    int i;
    for(i = 0; line; i++) {
        args[i] = strsep(&line, parse_for);
    }
    args[i] = NULL;
    return args;
}

int run( char * a, char **b ) {

  if (!strcmp(a, "exit")) {
    return 10; //10 for exit
  }
  else if (!strcmp(a, "cd")) {
    return 11; //11 for cd
  }
  execvp(a, b);
}

void cd( char *command[]) {

  char *directory = command[1];
  //int d_ret;
  //d_ret = chdir(directory);
  chdir(directory);
  
}

int main(int argc, char *argv[]) {

  char command[256];
  char **args;
  
  int status;
  int cpid;
  unsigned char *ret;
  
  int fds[2];
  pipe(fds);

  int i;
  int counter;
  
  while (1) {
    printf("Input a command:\n");
    fgets(command, 256, stdin);


    //printf("args = %s\n", args[0]);
    args = parse_args(command, "\n");//removing newlines from fgets retval
    args = parse_args(command, " "); //parses through the string by " "
    args = parse_args(command, ";"); //parses through the string by ;
    
    while(args[counter]) {
	 
      if (!fork()) { //child process
	//close(fds[READ]);
	return(run(args[counter][0], args[counter]));
	//write(fds[WRITE], &i, 4);
      }
      else { //parent process
	//close(fds[WRITE]);
	//read(fds[READ], &i, 4);
	//printf("%d", i);
	cpid = waitpid(-1, &status, 0);
	ret = (unsigned char *) &status;
	ret++;

	if (*ret == 10) {//exit
	  exit(SIGSTOP);
	}
	else if (*ret == 11) {//cd
	  cd(args[counter]);
	}
      }

      counter++;
    }
    
    return 0;
  
  }
}
