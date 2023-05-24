#include "shell.h"

/**
 * my_getenv - gets the value of an environ variable
 * @info: contains simulated arguments for a function pointer,
 * @name: env var name
 *
 * Return: the value
 */

char *my_getenv(info_f *info, const char *name)
{
	char *p;
	list_f *node = info->env;

	while (node)
	{
		p = my_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_check_setenv - Checks if an environment variable has been set.
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 *
 * Return: 0 if set, else 1.
 */

int my_check_setenv(info_f *info)
{
	if (info->argc != 3)
	{
		my_puts_err("Incorrect number of arguements\n");
		return (1);
	}

	if (my_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_check_unsetenv - Remove an environment variable
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int my_check_unsetenv(info_f *info)
{
	int i;

	if (info->argc == 1)
	{
		my_puts_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		my_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * my_gather_env - populates env linked list
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int my_gather_env(info_f *info)
{
	list_f *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		my_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * my_printenv - prints the current environment
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int my_printenv(info_f *info)
{
	my_print_list_str(info->env);
	return (0);
}
