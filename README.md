Shell

by Xing Tao Shi

Features:

	Forks and executes commands!
	Parses multiple commands on one line!
	Redirects using >!
	Can pipe singularly

Attempted:

	Tried to implement < redirects but was not able to
	Planned to implement colors and auto-completion but got stuck on < redirect

Bugs:

	
Files & Function Headers:

shell.c

	Handles everything
	
	/*======== char ** parse_args(char *, char *) ==========
	Inputs:  char *line, and char *parse_for
	Returns: Array of strings where each entry is a token 
	separated by parse_for

	====================*/
	
	/*======== void run(char *, char **) ==========
	Inputs:  char *a, and char **b
	Runs the command using execvp
	
	====================*/
	
	/*======== void exit_cmd(char *) ==========
	Inputs:  char *command
	Exits the program if "exit" is the command
	
	====================*/
		
	/*======== void cd(char **) ==========
	Inputs:  char **command
	Moves the the specified directory if "cd" is found 
	
	====================*/
	
	/*======== char * trim() ==========
	Inputs:  char *line 
	Returns: Pointer to the beginning of line

	Removes leading and trailing whitespace on the string line.
	Terminating '\0' is placed at a new location if necessary.
	====================*/
		
	/*======== void redirect_out(char **) ==========
	Inputs:  char **args
	Takes the output of a command and writes it to a file
	
	====================*/
		
	/*======== int piping(char **) ==========
	Inputs:  char **args
	Creates a pipe if "|" is found and runs it w/ the commands found
	Returns: Whether or not it found "|"
	
	====================*/
		
	/*======== void execute() ==========
	Runs the program, prints "Input a command" and reads input
	
	====================*/
			
main.c
	Runs the program
	
