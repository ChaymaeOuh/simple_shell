#include "shell.h"
/**
 * my_is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter else 0
 */
bool is_chain(info_f *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = OR_FLAG;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = AND_FLAG;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->sep_buff_kind = CHAIN_FLAG;
	}
	else
		return (false);
	*p = j;
	return (true);
}

/**
 * my_check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void my_check_chain(info_f *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->sep_buff_kind == AND_FLAG)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->sep_buff_kind == OR_FLAG)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * my_change_v - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int my_change_v(info_f *info)
{
	int i = 0;
	list_f *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!my_strcmp(info->argv[i], "$?"))
		{
			my_change_string(&(info->argv[i]));

						   my_strdup(my_change_base(info->status, 10, 0));

			continue;
		}
		if (!my_strcmp(info->argv[i], "$$"))
		{
			my_change_string(&(info->argv[i]));

						   my_strdup(my_change_base(getpid(), 10, 0));

			continue;
		}
		node = my_node_str_start(info->env, &info->argv[i][1], '=');
		if (node)
		{
			my_change_string(&(info->argv[i]));

						   my_strdup(my_strchr(node->str, '=') + 1);

			continue;
		}
		my_change_string(&info->argv[i], my_strdup(""));
	}
	return (0);
}
/**
 * my_change_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int my_change_string(char **old, char *new)
{
	free(*old);
	*old = new;

	return (1);
}
