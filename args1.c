#include "main.h"

/**
* exet_nzero - Sets args and index if !0.
* @args: Array of arguments.
* @front: Double pointer to args.
* @exec_resp: Value of last executed command.
* @ind: counter.
* Return: Value of executed command.
*/
int exet_nzero(char **args, char **front, int *exec_resp, int ind)
{
	int ret = run_args(args, front, exec_resp);

	if (*exec_resp != 0)
	{
		args = &args[++ind];
		ind = 0;
	}
	else
	{
		for (ind++; args[ind]; ind++)
			free(args[ind]);
		return (ret);
	}
	return (0);
}



/**
* exet_zero - Sets args and index if 0.
* @args: Array of arguments.
* @front: Double pointer to args.
* @exec_resp: Value of last executed command.
* @ind: counter.
* Return: Value of executed command.
*/
int exet_zero(char **args, char **front, int *exec_resp, int ind)
{
	int ret = run_args(args, front, exec_resp);

	if (*exec_resp == 0)
	{
		args = &args[++ind];
		ind = 0;
	}
	else
	{
		for (ind++; args[ind]; ind++)
			free(args[ind]);
		return (ret);
	}
	return (0);
}



/**
* get_args - Gets command from standard input.
* @line: Buffer to store command.
* @exec_resp: Response value of last executed command.
* Return: Pointer to the stored command
* or NULL if error.
*/
char *get_args(char *line, int *exec_resp)
{
	size_t n = 0;
	ssize_t readInput;
	char *prompt = "$ ";

	if (line)
		free(line);
	readInput = _getline(&line, &n, STDIN_FILENO);
	if (readInput == -1)
		return (NULL);
	if (readInput == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exec_resp));
	}
	line[readInput - 1] = '\0';
	variable_replacement(&line, exec_resp);
	handle_line(&line, readInput);
	return (line);
}



/**
* call_args - Partitions operators from commands and calls them.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
* @exec_resp: Response value of last executed command.
* Return: Value of the last executed command.
*/
int call_args(char **args, char **front, int *exec_resp)
{
	int resp, ind;

	if (!args[0])
		return (*exec_resp);
	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], "||", 2) == 0)
		{
			exet_nzero(args, front, exec_resp, ind);
		}
		else if (_strncmp(args[ind], "&&", 2) == 0)
		{
			exet_zero(args, front, exec_resp, ind);
		}
	}
	args = replace_aliases(args);
	resp = run_args(args, front, exec_resp);
	return (resp);
}


/**
* run_args - Call to execute a command.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
* @exec_resp: Response value of last executed command.
* Return: Value of last executed command.
*/
int run_args(char **args, char **front, int *exec_resp)
{
	int resp, ii;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);
	if (builtin)
	{
		resp = builtin(args + 1, front);
		if (resp != EXIT)
			*exec_resp = resp;
	}
	else
	{
		*exec_resp = execute(args, front);
		resp = *exec_resp;
	}
	hist++;
	for (ii = 0; args[ii]; ii++)
		free(args[ii]);
	return (resp);
}
