#include "main.h"


/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */

char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}



/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t io;

	for (io = 0; io < n && src[io] != '\0'; io++)
		dest[dest_len + io] = src[io];
	dest[dest_len + io] = '\0';

	return (dest);
}


/**
* _strcpy - Copies string pointed by src, including
*           terminating null byte, to buffer pointed by dest.
* @dest: Pointer to destination of copied string.
* @src: Pointer to src of string.
*
* Return: Pointer to dest.
*/
char *_strcpy(char *dest, const char *src)
{
	size_t ii;

	for (ii = 0; src[ii] != '\0'; ii++)
		dest[ii] = src[ii];
	dest[ii] = '\0';
	return (dest);
}



