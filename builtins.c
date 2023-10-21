#include "main.h"


/**
* get_builtin - Matches a cmd with corresponding
* builtin function.
* @command: The command to match.
* Return: A function pointer to builtin.
*/
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", sh_exit },
		{ "env", sh_env },
		{ "setenv", sh_setenv },
		{ "unsetenv", sh_unsetenv },
		{ "cd", sh_cd },
		{ "alias", sh_alias },
		{ "help", sh_help },
		{ "history", NULL },
		{ NULL, NULL }
	};

	int ind;

	for (ind = 0; funcs[ind].name; ind++)
	{
		if (_strcmp(funcs[ind].name, command) == 0)
			break;
	}
	return (funcs[ind].f);
}




/**
* sh_exit - Terminate shell process normally.
* @ags: Array of args containing exit value.
* @front: Double pointer to beginning of args.
* Return: O/w - exits with the status value,
*	-3 if there are no arguments,
*	-2 if the exit value is invalid,
* Description: At -3, program exits back in the main function.
*/
int sh_exit(char **ags, char **front)
{
	int i = 0, intLnt = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (ags[0])
	{
		if (ags[0][0] == '+')
		{
			i += 1;
			intLnt++;
		}
		for (; ags[0][i]; i++)
		{
			if (i <= intLnt && (ags[0][i] >= '0' && ags[0][i] <= '9'))
				num = (num * 10) + (ags[0][i] - '0');
			else
				return (create_error(--ags, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--ags, 2));
	ags -= 1;
	free_args(ags, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}




/**
* sh_help - Displays info about builtin cmds.
* @args: Array of arguments.
* @front: Pointer to the beginning of args.
* Return: 0 or -1 on error
*/
int sh_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else
		write(STDERR_FILENO, name, _strlen(name));
	return (0);
}

