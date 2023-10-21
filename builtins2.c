#include "main.h"

/**
* set_pa - sets task variables.
*
* @args: Array of arguments.
* Return: -1 on error occurs, Otherwise 0.
*/
int set_pa(char **args)
{
	char **d_Info, *nwLine = "\n";
	char *o_pwd = NULL, *pwd = NULL;

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);
	d_Info = malloc(sizeof(char *) * 2);
	if (!d_Info)
		return (-1);
	d_Info[0] = "OLDPWD";
	d_Info[1] = o_pwd;
	if (sh_setenv(d_Info, d_Info) == -1)
		return (-1);
	d_Info[0] = "PWD";
	d_Info[1] = pwd;
	if (sh_setenv(d_Info, d_Info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, nwLine, 1);
	}
	free(o_pwd);
	free(pwd);
	free(d_Info);
	return (0);
}


/**
* chk_agv_val - checks the nettd vslu of agrv
* @o_pwd: Working directory to be changed
* @args: Array of arguments.
*/
char chk_agv_val(char **args, char *o_pwd)
{
	if ((args[0][1] == '-' && args[0][2] == '\0') ||
	args[0][1] == '\0')
	{
		if (_getenv("OLDPWD") != NULL)
		(chdir(*_getenv("OLDPWD") + 7));
	}
	else
	{
		free(o_pwd);
		return (create_error(args, 2));
	}
	return (0);
}



/**
* sh_cd - Changes current directory of sh process.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
* Return: 2 if given string is not a directory,
*         -1 on error occurs, Otherwise 0.
*/
int sh_cd(char **args, char __attribute__((__unused__)) **front)
{
	char *o_pwd = NULL;
	struct stat dir;

	o_pwd = getcwd(o_pwd, 0);
	if (!o_pwd)
		return (-1);
	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			chk_agv_val(args, o_pwd);
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(o_pwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}
	set_pa(args);
	return (0);
}

