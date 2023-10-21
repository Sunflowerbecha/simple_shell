#include "main.h"


/**
* free_env - Frees the the environment copy.
*/
void free_env(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}



/**
* free_list - Frees a list_t linked list.
* @head: Head of list_t list.
*/
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}



/**
* free_alias_list - Frees alias_t linked list.
* @head: Head of the alias_t list.
*/
void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}



/**
* free_args - Frees memory taken by args.
* @args: Null-terminated double pointer containing cmds/args.
* @front: Double pointer to beginning of args.
*/
void free_args(char **args, char **front)
{
	size_t ii;

	for (ii = 0; args[ii] || args[ii + 1]; ii++)
		free(args[ii]);

	free(front);
}

