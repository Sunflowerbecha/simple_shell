#include "main.h"

/**
 * logical_ops - Checks for logical operators "||" or "&&".
 * @line: Pointer to character to be checked
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prevs, crnt, nxt;

	prevs = *(line - 1);
	crnt = *line;
	nxt = *(line + 1);

	if (crnt == '&')
	{
		if (nxt == '&' && prevs != ' ')
			(*new_len)++;
		else if (prevs == '&' && nxt != ' ')
			(*new_len)++;
	}
	else if (crnt == '|')
	{
		if (nxt == '|' && prevs != ' ')
			(*new_len)++;
		else if (prevs == '|' && nxt != ' ')
			(*new_len)++;
	}
}

