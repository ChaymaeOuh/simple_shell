#include "shell.h"
/**
 * my_clear_info - initializes info_s struct
 * @info: struct address
 */
void my_clear_info(info_f *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * my_set_info - initializes info_s struct
 * @info: struct address
 * @av: argument vector
 */
void my_set_info(info_f *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = my_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = my_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		my_change_alias(info);
		my_change_v(info);
	}
}
/**
 * my_free_info - frees info_s struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void my_free_info(info_f *info, int all)
{
	my_free_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->sep_buff)
			free(info->arg);
		if (info->env)
			my_free_list(&(info->env));
		if (info->history)
			my_free_list(&(info->history));
		if (info->alias)
			my_free_list(&(info->alias));
		my_free_vector(info->environ);
		info->environ = NULL;
		my_bfree((void **)info->sep_buff);
		if (info->fd_read > 2)
			close(info->fd_read);
		my_putchar(NEG_ONE);
	}
}
