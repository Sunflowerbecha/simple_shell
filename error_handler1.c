#include "main.h"

/**
* error_env - Creates error message for sh_env errors.
* @args: Array of args passed.
* Return: error string.
*/
char *error_env(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	args--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
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
	_strcat(err, ": Unable to add/remove from environment\n");
	free(hist_str);
	return (err);
}



/**
* error_1 - Creates error message for sh_alias errors.
* @args: Array of args passed.
* Return: Error string.
*/
char *error_1(char **args)
{
	char *err;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
		return (NULL);
	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " not found\n");
	return (err);
}




/**
* error_2_exit - Creates error message for sh_exit errors.
* @args: Array of args passed.
* Return: Error string.
*/
char *error_2_exit(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");
	free(hist_str);
	return (err);
}
