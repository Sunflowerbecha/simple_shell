#include "main.h"


/**
* handle_line - Partitions a line from stdin as needed.
* @line: Pointer to line read from stdin.
* @read: Length of line.
*
* Description: Separate ";", "||", and "&&" by spaces.
*              Replaces "#" with '\0'.
*/
void handle_line(char **line, ssize_t read)
{
	char *oLine, *nwLine;
	char prevs, curr, nxt;
	size_t i, j;
	ssize_t nwLen;

	nwLen = get_new_len(*line);
	if (nwLen == read - 1)
		return;
	nwLine = malloc(nwLen + 1);
	if (!nwLine)
		return;
	j = 0;
	oLine = *line;
	for (i = 0; oLine[i]; i++)
	{
		curr = oLine[i];
		nxt = oLine[i + 1];
		if (i != 0)
		{
			prevs = oLine[i - 1];
			if (curr == ';')
			{
				if (nxt == ';' && prevs != ' ' && prevs != ';')
				{
					nwLine[j++] = ' ';
					nwLine[j++] = ';';
					continue;
				}
				else if (prevs == ';' && nxt != ' ')
				{
					nwLine[j++] = ';';
					nwLine[j++] = ' ';
					continue;
				}
				if (prevs != ' ')
					nwLine[j++] = ' ';
				nwLine[j++] = ';';
				if (nxt != ' ')
					nwLine[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (nxt == '&' && prevs != ' ')
					nwLine[j++] = ' ';
				else if (prevs == '&' && nxt != ' ')
				{
					nwLine[j++] = '&';
					nwLine[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (nxt == '|' && prevs != ' ')
					nwLine[j++]  = ' ';
				else if (prevs == '|' && nxt != ' ')
				{
					nwLine[j++] = '|';
					nwLine[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && oLine[i - 1] != ' ')
				nwLine[j++] = ' ';
			nwLine[j++] = ';';
			if (nxt != ' ' && nxt != ';')
				nwLine[j++] = ' ';
			continue;
		}
		nwLine[j++] = oLine[i];
	}
	nwLine[j] = '\0';

	free(*line);
	*line = nwLine;
}


