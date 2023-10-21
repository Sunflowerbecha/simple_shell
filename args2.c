#include "main.h"


/**
* handle_args - Access and process arguments in a command.
* @exec_resp: Response value of last executed command.
*
* Return: O/w - Exit value of last executed command or
*		END_OF_FILE (-2) if end-of-file is read or
*		-1 if cannot tokenize input
*/
int handle_args(int *exec_resp)
{
	int resp = 0, ind;
	char **args, *line = NULL, **front;

	line = get_args(line, exec_resp);
	if (!line)
		return (END_OF_FILE);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (resp);
	if (check_args(args) != 0)
	{
		*exec_resp = 2;
		free_args(args, args);
		return (*exec_resp);
	}
	front = args;
	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], ";", 1) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			resp = call_args(args, front, exec_resp);
			args = &args[++ind];
			ind = 0;
		}
	}
	if (args)
		resp = call_args(args, front, exec_resp);
	free(front);
	return (resp);
}


/**
* check_args - Checks for any leading ';', ';;', '&&', or '||'.
* @ags: 2D pointer to tokenized cmds and args.
* Return: 2 if ';', '&&', or '||' is at an invalid position.
*	   Otherwise - 0.
*/
int check_args(char **ags)
{
	size_t i;
	char *crnt, *nxt;

	for (i = 0; ags[i]; i++)
	{
		crnt = ags[i];
		if (crnt[0] == ';' || crnt[0] == '&' || crnt[0] == '|')
		{
			if (i == 0 || crnt[1] == ';')
				return (create_error(&ags[i], 2));
			nxt = ags[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (create_error(&ags[i + 1], 2));
		}
	}
	return (0);
}


