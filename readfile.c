#include "main.h"

/**
* run_cmd_file - Run the commands in a file
* @f_path: File path.
* @exec_resp: response value of last executed command.
*
* Return: response of the last executed command or
* 127 - couldn't be opened, -1 - malloc fails.
*/
int run_cmd_file(char *f_path, int *exec_resp)
{
	ssize_t file, b_read, i;
	unsigned int l_size = 0, old_size = 120;
	char *readLine, **args, **front;
	char buffer[120];
	int runCmd;

	hist = 0;
	file = open(f_path, O_RDONLY);
	if (file == -1)
	{
		*exec_resp = cant_open(f_path);
		return (*exec_resp);
	}
	readLine = malloc(sizeof(char) * old_size);
	readLine[0] = '\0';
	if (!readLine)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && l_size == 0)
		{
			free(readLine);
			return (*exec_resp);
		}
		buffer[b_read] = '\0';
		l_size += b_read;
		readLine = _realloc(readLine, old_size, l_size);
		_strcat(readLine, buffer);
		old_size = l_size;
	} while (b_read);
	for (i = 0; readLine[i] == '\n'; i++)
		readLine[i] = ' ';
	for (; i < l_size; i++)
	{
		if (readLine[i] == '\n')
		{
			readLine[i] = ';';
			for (i += 1; i < l_size && readLine[i] == '\n'; i++)
				readLine[i] = ' ';
		}
	}
	variable_replacement(&readLine, exec_resp);
	handle_line(&readLine, l_size);
	args = _strtok(readLine, " ");
	free(readLine);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exec_resp = 2;
		free_args(args, args);
		return (*exec_resp);
	}
	front = args;
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			runCmd = call_args(args, front, exec_resp);
			args = &args[++i];
			i = 0;
		}
	}
	runCmd = call_args(args, front, exec_resp);
	free(front);
	return (runCmd);
}



/**
* _getline - Reads input from stream.
* @lptr: Buffer to store input.
* @n: Size of lptr.
* @stream: Stream to read from.
* Return: Number of bytes read.
*/
ssize_t _getline(char **lptr, size_t *n, FILE *stream)
{
	static ssize_t inpt;
	ssize_t resp;
	char c = 'x', *buff;
	int r;

	if (inpt == 0)
		fflush(stream);
	else
		return (-1);
	inpt = 0;
	buff = malloc(sizeof(char) * 120 + 1);
	if (!buff)
		return (-1);
	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && inpt == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && inpt != 0)
		{
			inpt++;
			break;
		}
		if (inpt >= 120)
			buff = _realloc(buff, inpt, inpt + 1);
		buff[inpt] = c;
		inpt++;
	}
	buff[inpt] = '\0';
	assign_lineptr(lptr, n, buff, inpt);
	resp = inpt;
	if (r != 0)
		inpt = 0;
	return (resp);
}


/**
* get_pid - Gets the current process ID.
* Return: The current process ID or NULL on failure.
*/
char *get_pid(void)
{
	size_t i = 0;
	char *buf;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(file);
		return (NULL);
	}
	read(file, buf, 120);
	while (buf[i] != ' ')
		i++;
	buf[i] = '\0';

	close(file);
	return (buf);
}


