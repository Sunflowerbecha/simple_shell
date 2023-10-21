#include "main.h"

/**
* token_len - Locates delimiter index marking end of token
* @str: string to search
* @delim: delimiter character
* Return: delimiter index marking end of token pointer
*/
int token_len(char *str, char *delim)
{
	int indx = 0, lent = 0;

	while (*(str + indx) && *(str + indx) != *delim)
	{
		lent++;
		indx++;
	}
	return (lent);
}



/**
* _strtok - Tokenizes a string.
* @line: String to tokenize
* @delim: delimiter character.
* Return: pointer to array containing tokenized words.
*/
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int indx = 0, tokens, t, letas, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[indx] == *delim)
			indx++;

		letas = token_len(line + indx, delim);
		ptr[t] = malloc(sizeof(char) * (letas + 1));
		if (!ptr[t])
		{
			for (indx -= 1; indx >= 0; indx--)
				free(ptr[indx]);
			free(ptr);
			return (NULL);
		}
		for (l = 0; l < letas; l++)
		{
			ptr[t][l] = line[indx];
			indx++;
		}
		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;
	return (ptr);
}



/**
* count_tokens - Counts number of words in a string
* @str: string to search
* @delim: delimiter character.
* Return: number of words contained in str.
*/
int count_tokens(char *str, char *delim)
{
	int indx, toks = 0, lent = 0;

	for (indx = 0; *(str + indx); indx++)
		lent++;

	for (indx = 0; indx < lent; indx++)
	{
		if (*(str + indx) != *delim)
		{
			toks++;
			indx += token_len(str + indx, delim);
		}
	}

	return (toks);
}


