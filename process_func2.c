#include "main.h"


/**
* get_new_len - Gets new length of a line partitioned
*		by ";", "||", "&&&", or "#".
* @line: Line to check.
*
* Return: New length of line.
*/
ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t nwLnt = 0;
	char curr, nxt;

	for (i = 0; line[i]; i++)
	{
		curr = line[i];
		nxt = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (nxt == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					nwLnt += 2;
					continue;
				}
				else if (line[i - 1] == ';' && nxt != ' ')
				{
					nwLnt += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					nwLnt++;
				if (nxt != ' ')
					nwLnt++;
			}
			else
				logical_ops(&line[i], &nwLnt);
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				nwLnt++;
			if (nxt != ' ' && nxt != ';')
				nwLnt++;
		}
		nwLnt++;
	}
	return (nwLnt);
}



/**
* variable_replacement - Handles variable replacement.
* @line: Double pointer containing cmds and args.
* @exec_resp: Pointer to return value of the last executed command.
*
* Description: Replaces $$ with current PID, $? with return value
*              of last executed program, and envrionment variables
*              preceded by $ with corresponding value.
*/
void variable_replacement(char **line, int *exec_resp)
{
	int j, k = 0, length;
	char *duplcte = NULL, *od_Line = NULL, *nwLine;

	od_Line = *line;
	for (j = 0; od_Line[j]; j++)
	{
		if (od_Line[j] == '$' && od_Line[j + 1] &&
				od_Line[j + 1] != ' ')
		{
			if (od_Line[j + 1] == '$')
			{
				duplcte = get_pid();
				k = j + 2;
			}
			else if (od_Line[j + 1] == '?')
			{
				duplcte = _itoa(*exec_resp);
				k = j + 2;
			}
			else if (od_Line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; od_Line[k] &&
						od_Line[k] != '$' &&
						od_Line[k] != ' '; k++)
					;
				length = k - (j + 1);
				duplcte = get_env_value(&od_Line[j + 1], length);
			}
			nwLine = malloc(j + _strlen(duplcte)
					  + _strlen(&od_Line[k]) + 1);
			if (!line)
				return;
			nwLine[0] = '\0';
			_strncat(nwLine, od_Line, j);
			if (duplcte)
			{
				_strcat(nwLine, duplcte);
				free(duplcte);
				duplcte = NULL;
			}
			_strcat(nwLine, &od_Line[k]);
			free(od_Line);
			*line = nwLine;
			od_Line = nwLine;
			j = -1;
		}
	}
}
