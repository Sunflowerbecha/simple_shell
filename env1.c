#include "main.h"

/**
* _duplicateEnv - Create a copy of environment
*
* Return: O/w - double pointer to new copy or
* NULL on error.
*/
char **_duplicateEnv(void)
{
	char **newEnv;
	size_t size;
	int ind;

	for (size = 0; environ[size]; size++)
		;

	newEnv = malloc(sizeof(char *) * (size + 1));
	if (!newEnv)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		newEnv[ind] = malloc(_strlen(environ[ind]) + 1);
		if (!newEnv[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(newEnv[ind]);
			free(newEnv);
			return (NULL);
		}
		_strcpy(newEnv[ind], environ[ind]);
	}
	newEnv[ind] = NULL;
	return (newEnv);
}




/**
* get_env_value - Gets value of an environment var.
* @beginning: Environment variable to search for.
* @len: Length of environment var to search for.
* Return: Value of the environment varriable
*	or an empty string if not found
* Description: Variables are stored in the
*	format VARIABLE=VALUE.
*/
char *get_env_value(char *beginning, int len)
{
	char **varAdr;
	char *newAdr = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);
	varAdr = _getenv(var);
	free(var);
	if (varAdr)
	{
		tmp = *varAdr;
		while (*tmp != '=')
			tmp++;
		tmp++;
		newAdr = malloc(_strlen(tmp) + 1);
		if (newAdr)
			_strcpy(newAdr, tmp);
	}
	return (newAdr);
}



/**
* sh_env - Prints current environment.
* @args: Array of args passed.
* @front: Double pointer to beginning of args.
* Return: 0 on success, -1 on error
* Description: Prints one variable info per line
*	format 'variable'='value'.
*/
int sh_env(char **args, char __attribute__((__unused__)) **front)
{
	int ind;
	char nwLine = '\n';

	if (!environ)
		return (-1);
	for (ind = 0; environ[ind]; ind++)
	{
		write(STDOUT_FILENO, environ[ind], _strlen(environ[ind]));
		write(STDOUT_FILENO, &nwLine, 1);
	}
	(void)args;
	return (0);
}

