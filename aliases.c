#include "main.h"


/**
* set_alias - To set an alias 'name' with new value,
* or creates new alias with name and value.
* @var_name: Name of alias.
* @value: Value of alias. First character is a '='.
*/
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int length, zi, qi;
	char *newValue;

	*value = '\0';
	value++;
	length = _strlen(value) - _strspn(value, "'\"");
	newValue = malloc(sizeof(char) * (length + 1));
	if (!newValue)
		return;
	for (zi = 0, qi = 0; value[zi]; zi++)
	{
		if (value[zi] != '\'' && value[zi] != '"')
			newValue[qi++] = value[zi];
	}
	newValue[qi] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = newValue;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, newValue);
}



/**
* print_alias - Prints alias in format name='value'.
* @alias: Pointer to alias.
*/
void print_alias(alias_t *alias)
{
	char *a_str;
	int l = _strlen(alias->name) + _strlen(alias->value) + 4;

	a_str = malloc(sizeof(char) * (l + 1));
	if (!a_str)
		return;
	_strcpy(a_str, alias->name);
	_strcat(a_str, "='");
	_strcat(a_str, alias->value);
	_strcat(a_str, "'\n");
	write(STDOUT_FILENO, a_str, l);
	free(a_str);
}



/**
* sh_alias - Builtin command to prints all or
* specific aliases, or sets an alias.
* @args: Array of arguments.
* @front: Double pointer to beginning of args.
* Return: 0 on success or -1 on error.
*/
int sh_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int ind, pResponse = 0;
	char *v;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (pResponse);
	}
	for (ind = 0; args[ind]; ind++)
	{
		temp = aliases;
		v = _strchr(args[ind], '=');
		if (!v)
		{
			while (temp)
			{
				if (_strcmp(args[ind], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				pResponse = create_error(args + ind, 1);
		}
		else
			set_alias(args[ind], v);
	}
	return (pResponse);
}




/**
* replace_aliases - Replaces matching alias in
* arguments with it value.
* @ags: 2D pointer to arguments.
* Return: 2D pointer to arguments.
*/
char **replace_aliases(char **ags)
{
	alias_t *temp;
	int ind;
	char *newValue;

	if (_strcmp(ags[0], "alias") == 0)
		return (ags);
	for (ind = 0; ags[ind]; ind++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(ags[ind], temp->name) == 0)
			{
				newValue = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!newValue)
				{
					free_args(ags, ags);
					return (NULL);
				}
				_strcpy(newValue, temp->value);
				free(ags[ind]);
				ags[ind] = newValue;
				ind--;
				break;
			}
			temp = temp->next;
		}
	}
	return (ags);
}

