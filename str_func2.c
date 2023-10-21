#include "main.h"


/**
* _strlen - Returns the length of a string.
* @s: Pointer to characters string.
*
* Return: Length of character string.
*/
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}



/**
* _strncmp - Compare two strings.
* @s1: Pointer to a string.
* @s2: Pointer to a string.
* @n: The first n bytes of the strings to compare.
*
* Return: Less than 0 if s1 is shorter than s2.
*         0 if s1 and s2 match.
*         Greater than 0 if s1 is longer than s2.
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}





/**
* _itoa - Converts integer to string.
* @num: The integer to convert.
*
* Return: Converted string.
*/
char *_itoa(int num)
{
	char *buf;
	int length = num_len(num);
	unsigned int num1;

	buf = malloc(sizeof(char) * (length + 1));
	if (!buf)
		return (NULL);

	buf[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buf[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buf[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buf);
}


