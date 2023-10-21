#include "main.h"

/**
* get_path_dir - Tokenizes colon-separated list of
*	directories.
* @dir_list: The colon-separated list of directories.
*
* Return: Pointer to initialized linked list.
*/
list_t *get_path_dir(char *dir_list)
{
	int ind;
	char **ds, *pathDup;
	list_t *head = NULL;

	pathDup = fill_path_dir(dir_list);
	if (!pathDup)
		return (NULL);
	ds = _strtok(pathDup, ":");
	free(pathDup);
	if (!ds)
		return (NULL);

	for (ind = 0; ds[ind]; ind++)
	{
		if (add_node_end(&head, ds[ind]) == NULL)
		{
			free_list(head);
			free(ds);
			return (NULL);
		}
	}
	free(ds);
	return (head);
}



/**
* add_node_end - Adds node to end of list_t linked list.
* @head: Pointer to head of list_t list.
* @dir: Directory path for new node.
*
* Return: Pointer to new node, NULL on error.
*/
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *nwNode = malloc(sizeof(list_t));
	list_t *lst;

	if (!nwNode)
		return (NULL);

	nwNode->dir = dir;
	nwNode->next = NULL;

	if (*head)
	{
		lst = *head;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = nwNode;
	}
	else
		*head = nwNode;

	return (nwNode);
}

