#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: contains simulated arguments for a function pointer
 *
 * Return: exit status
 */
int my_exit(info_f *info)
{
int exitcheck;
if (info->argv[1]) /* If there is an exit arguement */
{
exitcheck = my_err_num(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
my_print_error(info, "Illegal number: ");
my_puts_err(info->argv[1]);
my_putchar_err('\n');
return (1);
}
info->error_code = my_err_num(info->argv[1]);
return (-2);
}
info->error_code = -1;
return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @info: contains simulated arguments for a function pointer
 *
 * Return: 0
 */
int my_cd(info_f *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
my_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = my_getenv(info, "HOME=");
if (!dir)
chdir_ret = chdir((dir = my_getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (my_strcmp(info->argv[1], "-") == 0)
{
if (!my_getenv(info, "OLDPWD="))
{
my_puts(s);
my_putchar('\n');
return (1);
}
my_puts(my_getenv(info, "OLDPWD=")), my_putchar('\n');
chdir_ret = chdir((dir = my_getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
my_print_error(info, "can't cd to ");
my_puts_err(info->argv[1]), my_putchar_err('\n');
}
else
{
my_setenv(info, "OLDPWD", my_getenv(info, "PWD="));
my_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * my_help - prints a message for aa function not implemented
 * @info: contains simulated arguments for a function pointer
 *
 * Return: 0
 */
int my_help(info_f *info)
{
char **arg_array;
arg_array = info->argv;
my_puts("help call works. Function not yet implemented \n");
if (0)
my_puts(*arg_array);

return (0);
}

/**
 * my_history - displays the history list
 * @info: contains simulated arguments for a function pointer
 *
 * Return: 0
 */
int my_history(info_f *info)
{
my_print_list(info->history);
return (0);
}

