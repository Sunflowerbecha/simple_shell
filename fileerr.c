#include "main.h"

/**
* cant_open - print cant open err if
* file doesn't exist or lacks permissions.
* @f_path: Path to file.
*
* Return: 127.
*/
int cant_open(char *f_path)
{
	char *err, *h_str;
	int length;

	h_str = _itoa(hist);
	if (!h_str)
		return (127);
	length = _strlen(name) + _strlen(h_str) + _strlen(f_path) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (127);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_str);
	_strcat(err, ": Can't open ");
	_strcat(err, f_path);
	_strcat(err, "\n");
	free(h_str);
	write(STDERR_FILENO, err, length);
	free(err);
	return (127);
}
