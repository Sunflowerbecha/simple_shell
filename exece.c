#include "main.h"

/**
* child_zero - gives exec procedures.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
* @cmd: Command to execute.
*/
void child_zero(char **args, char *cmd, char **front)
{
	int presponse = 0;

	execve(cmd, args, environ);
	if (errno == EACCES)
		presponse = (create_error(args, 126));
	free_env();
	free_args(args, front);
	free_alias_list(aliases);
	_exit(presponse);
}



/**
* try_execute - Command execution.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
* @cmd: Command to execute.
* @flag: execution flag.
*
* Return: O/w - The exit value of the last executed command
*	or an error code if error occurs.
*/
int try_execute(char **args, char **front, char *cmd, int flag)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		if (flag)
			free(cmd);
		perror("Error child:");
		return (1);
	}
	if (child_pid == 0)
	{
		child_zero(args, cmd, front);
	}
	else
	{
		wait(&status);
	}
	return (0);
}


/**
* execute - Executes command in child process.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
*
* Return: O/w - The exit value of the last executed command
*	or an error code if error occurs.
*/
int execute(char **args, char **front)
{
	int flag = 0, presponse = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_location(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			presponse = (create_error(args, 126));
		else
			presponse = (create_error(args, 127));
	}
	else
	{
		try_execute(args, front, cmd, flag);
	}
	if (flag)
		free(cmd);
	return (presponse);
}
