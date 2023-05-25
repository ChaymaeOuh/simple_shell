#include "shell.h"

/**
 * my_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int my_unset_alias(info_f *info, char *str)
{
	char *p, c;
	int ret;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = my_delete_node_at_index(&(info->alias),
							   my_node_index(info->alias, my_node_str_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * my_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int my_set_alias(info_f *info, char *str)
{
	char *p;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (my_unset_alias(info, str));

	my_unset_alias(info, str);
	return (my_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * my_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int my_print_alias(list_f *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = my_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			my_putchar(*a);
		my_putchar('\'');
		my_puts(p + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 *	Return: Always 0
 */
int my_alias(info_f *info)
{
	int i = 0;
	char *p = NULL;
	list_f *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			my_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = my_strchr(info->argv[i], '=');
		if (p)
			my_set_alias(info, info->argv[i]);
		else
			my_print_alias(my_node_str_start(info->alias, info->argv[i], '='));
	}
	return (0);
}

/**
 * my_change_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int my_change_alias(info_f *info)
{
	int i;
	list_f *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = my_node_str_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = my_strchr(node->str, '=');
		if (!p)
			return (0);
		p = my_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}
