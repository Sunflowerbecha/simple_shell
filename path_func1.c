#include "main.h"


/**
* do_path_cattt - Copies path and concatenate path
*	leading/trailing colons (:) with current dir.
* @pwd: working dir.
* @dirpath: The colon-separated list of dir.
* @path_copy: Directory path copied.
*/
void do_path_cattt(char *dirpath, char *path_copy, char *pwd)
{
	int i;

	for (i = 0; dirpath[i]; i++)
	{
		if (dirpath[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (dirpath[i + 1] == ':' || dirpath[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &dirpath[i], 1);
		}
	}

}

/**
* fill_path_dir - Copies path and replaces
*	leading/trailing colons (:).
* @dirpath: The colon-separated list of dir.
* Return: copy of path  replaced
*/
char *fill_path_dir(char *dirpath)
{
	int i, lent = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; dirpath[i]; i++)
	{
		if (dirpath[i] == ':')
		{
			if (dirpath[i + 1] == ':' || i == 0 || dirpath[i + 1] == '\0')
				lent += _strlen(pwd) + 1;
			else
				lent++;
		}
		else
			lent++;
	}
	path_copy = malloc(sizeof(char) * (lent + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	do_path_cattt(dirpath, path_copy, pwd);
	return (path_copy);
}



/**
* add_alias_end - Adds node to end of alias_t linked list.
* @head: Pointer to head of list_t list.
* @name: Name of new alias to add.
* @value: Value of new alias to add.
*
* Return: Pointer to new node, NULL on error.
*/
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *nwNode = malloc(sizeof(alias_t));
	alias_t *lst;

	if (!nwNode)
		return (NULL);

	nwNode->next = NULL;
	nwNode->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!nwNode->name)
	{
		free(nwNode);
		return (NULL);
	}
	nwNode->value = value;
	_strcpy(nwNode->name, name);

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


/**
* get_location - Locates command PATH.
* @cmds: Command to locate.
* Return: Full pathname of command,
*	NULL if error or cannot locate path.
*/
char *get_location(char *cmds)
{
	char **path, *temp;
	list_t *dirColtn, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirColtn = get_path_dir(*path + 5);
	head = dirColtn;

	while (dirColtn)
	{
		temp = malloc(_strlen(dirColtn->dir) + _strlen(cmds) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirColtn->dir);
		_strcat(temp, "/");
		_strcat(temp, cmds);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirColtn = dirColtn->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

