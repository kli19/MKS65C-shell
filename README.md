# MKS65C-shell
by Karen Li and Alex Liu

Features:
	Forks and executes commands!
	Parses multiple commands on one line!

Attempted:


Bugs:
	Putting two ;'s next to each other will break the parser
	Typing nothing and hitting the enter key breaks the parser
	
Files & Function Headers:
parse.c
	Handles all line parsing functions

	/*======== char ** parse_args() ==========
	Inputs:  char * line 
	Returns: Array of strings where each entry is a token 
	separated by delim

	====================*/

	/*======== char * trim() ==========
	Inputs:  char *line 
	Returns: Pointer to the beginning of a string

	Removes leading and trailing whitespace on the string line.
	====================*/

shell.c
	Handles the forking an executing of commands
	/*======== void execute() ==========
	Inputs:  Nothing
	Returns: Nothing

	Reads commands, forks, and executes.
	====================*/

