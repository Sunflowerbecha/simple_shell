#include "main.h"


/**
* sig_handler - Prints new prompt upon signal.
* (handles ctrl c)
* @sig: The signal.
*/
void sig_handler(int sig)
{
	char *n_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, n_prompt, 3);
}


/**
* main - Runs a UNIX command interpreter.
* @ac: argument count
* @av: argument vector
*
* Return: value of the last executed command.
*/
int main(int ac, char *av[])
{
    int runCmd = 0, retn;
	int *execStatus = &retn;
	char *promptSymbol = "$ ", *newLine = "\n";

	name = av[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*execStatus = 0;
	environ = _duplicateEnv();
	if (!environ)
		exit(-100);

	if (ac != 1)
	{
		runCmd = run_cmd_file(av[1], execStatus);
		free_env();
		free_alias_list(aliases);
		return (*execStatus);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (runCmd != END_OF_FILE && runCmd != EXIT)
			runCmd = handle_args(execStatus);
		free_env();
		free_alias_list(aliases);
		return (*execStatus);
	}

	while (1)
	{
		write(STDOUT_FILENO, promptSymbol, 2);
		runCmd = handle_args(execStatus);
		if (runCmd == END_OF_FILE || runCmd == EXIT)
		{
			if (runCmd == END_OF_FILE)
				write(STDOUT_FILENO, newLine, 1);
			free_env();
			free_alias_list(aliases);
			exit(*execStatus);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*execStatus);
}
