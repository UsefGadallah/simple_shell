#include "Shell.h"

/**
 * _MyHistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _MyHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * UnSet_Alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int UnSet_Alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _StrChr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * Set_Alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int Set_Alias(info_t *info, char *str)
{
	char *p;

	p = _StrChr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (UnSet_Alias(info, str));

	UnSet_Alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * Print_Alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int Print_Alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _StrChr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _MyAlias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _MyAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			Print_Alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _StrChr(info->argv[i], '=');
		if (p)
			Set_Alias(info, info->argv[i]);
		else
			Print_Alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
