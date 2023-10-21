#include "main.h"


/**
* num_len - Counts length of a number.
* @num: Number to count.
*
* Return: Length of number.
*/
int num_len(int num)
{
	unsigned int num1;
	int ln = 1;

	if (num < 0)
	{
		ln++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		ln++;
		num1 /= 10;
	}
	return (ln);
}




/**
* _strchr - Locates a character in a string.
* @s: The string to be searched.
* @c: The character to be located.
*
* Return: If c is found - a pointer to the first occurence.
*         If c is not found - NULL.
*/
char *_strchr(char *s, char c)
{
	int ind;

	for (ind = 0; s[ind]; ind++)
	{
		if (s[ind] == c)
			return (s + ind);
	}

	return (NULL);
}


/**
* _strcmp - Compares two strings.
* @s1: First string to compare.
* @s2: Second string to compare.
*
* Return: Positive byte difference if s1 > s2
*         0 if s1 = s2
*         Negative byte difference if s1 < s2
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}



/**
* _strspn - Gets length of prefix substring.
* @s: String to search.
* @accept: Prefix to measure.
*
* Return: Number of bytes in s.
*/
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int ind;

	while (*s)
	{
		for (ind = 0; accept[ind]; ind++)
		{
			if (*s == accept[ind])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

