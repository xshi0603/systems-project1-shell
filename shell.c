#include "shell.h"

char ** parse_args( char * line, char * parse_for ) {
    char** args = (char **)calloc(6, sizeof(char *));
    int i;
    for(i = 0; line; i++) {
        args[i] = strsep(&line, parse_for);
	args[i] = trim(args[i]);
    }
    args[i] = NULL;
    return args;
}

int run( char * a, char **b ) {
  
  execvp(a, b);
  exit(0);
  
}

void exit_cmd( char *command) {

  if (!strcmp(command, "exit")) {
    exit(0);
  }

}

void cd( char **command) {

  if (!strcmp(command[0], "cd") && command[1]) {
    chdir(command[1]);
  }
  
}

char * trim(char *command) {

  char * end = command + strlen(command) - 1;
  
  while (*command && isspace(*command)) {
    command++;
  }

  while (isspace(*end)) {
    *end-- = '\0';
  }
  
  return command;

}

void redirect_out(char *args[256]) {
    int i;
    for (i = 0; args[i]; i++) {

      int new_file;


      if (args[i][0] == '>') {
	char* file_name = args[i+1];
	new_file = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	dup2(new_file, 1);
	close(new_file);
	args[i] = 0;
      }

    }
}

int piping(char *args[256]) {
    int counter;
    int ran = -1;
    
    char *command = (char*)calloc(256, sizeof(char));

    for (counter = 0; args[counter]; counter++){//finding |
        int counter2;
        for (counter2 = 0; args[counter][counter2]; counter2++) {
            if (args[counter][counter2] == '|') {
                ran = 0;
            }
        }
        strcat(command,args[counter]);
    }

    if (!ran) {
        FILE *pipe;
        pipe = popen(command, "w");
        char buf[256];
        fgets(buf, sizeof(buf), pipe);
        buf[sizeof(buf) - 1] = 0;
        pclose(pipe);
    }

    return ran;
}

void execute() {

  char *commands = malloc(256);
  
  printf("Input a command:\n");
  fgets(commands, 256, stdin);

  size_t len = strlen(commands); 
  
  if(commands[len - 1] == '\n'){
    commands[len - 1] = '\0';
  }

  char **args = parse_args(commands, ";");
  
  int counter = 0;
  while (args[counter]) {

    char * command = trim(args[counter]);
    
    exit_cmd(command);
    
    char ** args = parse_args(command, " ");
    
    cd(args);

    int piped = piping(args);
    
    if (piped) {
    
      if (!fork()) { //child process

	redirect_out(args);
	run(args[0], args);

      }
     }
    //parent process

    int status;
    int cpid = waitpid(-1, &status, 0);
    counter++;
      
  }

  free(commands);
  
  return;
}

int main(int argc, char *argv[]) {

  while (1) {
    execute();
  }
        
  return 0;
  
}
