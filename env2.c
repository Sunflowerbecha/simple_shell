#include "main.h"


/**
* sh_setenv - Changes or adds environment var to PATH.
* @args: Array of arguments passed.
* @front: Double pointer to beginning of args.
* Description: args[1] - name of new or existing PATH var.
*	args[2] - value to set to.
* Return: 0 on success, -1 on error.
*/
int sh_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_v = NULL, **new_env, *nVal;
	size_t size;
	int ind;

	if (!args[0] || !args[1])
		return (create_error(args, -1));
	nVal = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!nVal)
		return (create_error(args, -1));
	_strcpy(nVal, args[0]);
	_strcat(nVal, "=");
	_strcat(nVal, args[1]);
	env_v = _getenv(args[0]);
	if (env_v)
	{
		free(*env_v);
		*env_v = nVal;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(nVal);
		return (create_error(args, -1));
	}
	for (ind = 0; environ[ind]; ind++)
		new_env[ind] = environ[ind];
	free(environ);
	environ = new_env;
	environ[ind] = nVal;
	environ[ind + 1] = NULL;
	return (0);
}




/**
* sh_unsetenv - Deletes environment variable.
* @args: Array of arguments passed.
* @front: Double pointer to beginning of args.
* Description: args[1] - variable PATH to remove.
* Return: 0 on success, -1 on error.
*/
int sh_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_v, **new_env;
	size_t size;
	int ind, ind2;

	if (!args[0])
		return (create_error(args, -1));
	env_v = _getenv(args[0]);
	if (!env_v)
		return (0);
	for (size = 0; environ[size]; size++)
		;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (create_error(args, -1));
	for (ind = 0, ind2 = 0; environ[ind]; ind++)
	{
		if (*env_v == environ[ind])
		{
			free(*env_v);
			continue;
		}
		new_env[ind2] = environ[ind];
		ind2++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;
	return (0);
}




/**
* _getenv - Gets environment var from PATH.
* @var: Name of environment var to get.
* Return: Pointer to environment variable
*	NULL if not exit
*/
char **_getenv(const char *var)
{
	int ind, len;

	len = _strlen(var);
	for (ind = 0; environ[ind]; ind++)
	{
		if (_strncmp(var, environ[ind], len) == 0)
			return (&environ[ind]);
	}
	return (NULL);
}
