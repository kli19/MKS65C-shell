# MKS65C-shell
by Karen Li and Alex Liu

Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Simple redirection (>, <, >>) and piping

Attempted:


Bugs:
	Putting two ;'s next to each other will break the parser

	
Files & Function Headers:
parse.c
	Handles all line parsing functions

	/*======== char ** parse_args() ==========
	Inputs:  char * line 
	Returns: Array of strings where each entry is a token 
	separated by delim

	====================*/

	/*======== char * trim() ==========
	Inputs:  char * line 
	Returns: Pointer to the beginning of a string

	Removes leading and trailing whitespace on the string line.
	====================*/

shell.c
	Handles the forking an executing of simple commands
	/*======== void execute() ==========
	Inputs:  char * command
	Returns: Nothing

	Reads forks and executes simple commands.
	====================*/

	Handles the forking an executing of all commands
	/*======== void execute_all() ==========
	Inputs:  char * line
	Returns: Nothing

	Parses through every command and determines method of execution.
	====================*/

redirect.c
	Handles redirection

	/*======== int redirect() ==========
	Inputs:  char * command, int * fd
	Returns: The value of the filedescriptor that was used.

	Redirects standard output.
	====================*/

	/*======== int direction() ==========
	Inputs:  char * symbol
	Returns: The index of an array 

	Determines the index of the files array to be used.
	====================*/

	/*======== int flag() ==========
	Inputs:  char * symbol
	Returns: The index of an array 

	Determines the index of the flags array to be used.
	====================*/
	
	/*======== char * redirect_symbol() ==========
	Inputs: char * command
	Returns:  A string containing a symbol

	Determines the redirection symbol that is being used.
	====================*/

redirect.c
	Handles piping

	/*======== void my_pipe(); ==========
	Inputs:  char * command
	Returns: Nothing

	Directs standard output from one command to standard input of another command.
	====================*/