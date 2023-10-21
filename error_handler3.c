#include "main.h"


/**
* error_127 - Creates error msg for command not found.
* @args: Array of arguments passed.
* Return: Error string.
*/
char *error_127(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": not found\n");
	free(hist_str);
	return (err);
}



/**
* create_error - Writes custom error message to stderr.
* @args: Array of arguments.
* @err: Error value.
* Return: Error value.
*/
int create_error(char **args, int err)
{
	char *eror;

	switch (err)
	{
		case -1:
			eror = error_env(args);
			break;
		case 1:
			eror = error_1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				eror = error_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				eror = error_2_syntax(args);
			else
				eror = error_2_cd(args);
			break;
		case 126:
			eror = error_126(args);
			break;
		case 127:
			eror = error_127(args);
			break;
	}
	write(STDERR_FILENO, eror, _strlen(eror));
	if (eror)
		free(eror);
	return (err);
}
