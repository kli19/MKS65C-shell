# MKS65C-shell
by Karen Li and Alex Liu

Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Simple redirection (>, <, >>) and piping

Attempted:
	Attempted tabbing but we had issues concatenating spaces to our line.

Bugs:
	Putting two ;'s next to each other will break the parser
	Using Backspace will not work; need to press enter to reset


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

extra.c
	Handles tabbing

	/*======== char ** listFiles(char * path); ==========
	Inputs:  char * path
	Returns: char ** (array of files in current path)

	Returns an array of files in current path
	====================*/

	/*======== char * split( char * line ); ==========
	Inputs:  char * line
	Returns: char * (last item typed)

	Returns an the last portion typed in the command line (items are separated by spaces)
	====================*/

	/*======== int getch(); ==========
	Inputs:  void
	Returns: int (The keystroke on the ASCII Table)

	Uses termios.h to get the keystroked typed in
	====================*/

	/*======== 	char * tabby(char * line); ==========
	Inputs:  char * line
	Returns: char * (Based on if the tab can determine which file name is about to be typed)

	Returns the finished file name if it can be determined
	====================*/

	/*======== char * keyFinder(); ==========
	Inputs:  void
	Returns: char * (A string or character based on what was typed in)

	Determines whether the keystroke was special or just a normal character
	====================*/


	void history(char * line);
	char * removeLast(char* name);
