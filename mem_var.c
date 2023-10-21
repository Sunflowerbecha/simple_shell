#include "main.h"


/**
* assign_lineptr - Reassigns lineptr variable to _getline
* @lptr: Buffer to store input string.
* @n: Size of lineptr.
* @buff: String to assign.
* @b: Size of buffer.
*/
void assign_lineptr(char **lptr, size_t *n, char *buff, size_t b)
{
	if (*lptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lptr = buff;
	}
	else
	{
		_strcpy(*lptr, buff);
		free(buff);
	}
}



/**
* _realloc - Reallocates memory block using malloc and free.
* @ptr: Pointer to previously allocated memory
* @old_size: Size in bytes of allocated ptr memory
* @new_size: Size in bytes for new memory block
* Return: ptr - pointer to reallocated memory block
*	if new_size == old_size,
*	NULL if new_size == 0 and ptr is not NULL.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mry;
	char *ptrDup, *loader;
	unsigned int ind;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		mry = malloc(new_size);
		if (mry == NULL)
			return (NULL);
		return (mry);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptrDup = ptr;
	mry = malloc(sizeof(ptrDup) * new_size);
	if (mry == NULL)
	{
		free(ptr);
		return (NULL);
	}
	loader = mry;
	for (ind = 0; ind < old_size && ind < new_size; ind++)
		loader[ind] = *ptrDup++;
	free(ptr);
	return (mry);
}

