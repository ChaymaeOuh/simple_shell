#include "shell.h"

/**
 * my_shell - main control for the shell program
 * @info: pointer to an info_f struct containing shell information
 * @av: array of strings containing arguments
 *
 * Return: the status of the last executed builtin command
 */

int my_shell(info_f *info, char **av)
{
ssize_t read_result = 0;
int builtin_return_value = 0;
while (read_result != -1 && builtin_return_value != -2)
{
my_clear_info(info);
if (my_from_terminal(info))
my_puts("OurShell> ");
my_putchar_err(NEG_ONE);
read_result = my_get_input(info);
if (read_result != -1)
{
my_set_info(info, av);
builtin_return_value = my_builtin(info);
if (builtin_return_value == -1)
my_check_command(info);
}
else if (my_from_terminal(info))
my_putchar('\n');
my_free_info(info, 0);
}
my_create_history(info);
my_free_info(info, 1);
if (!my_from_terminal(info) && info->status)
exit(info->status);
if (builtin_return_value == -2)
{
if (info->error_code == -1)
exit(info->status);
exit(info->error_code);
}
return (builtin_return_value);
}

/**
 * my_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 (Not found) 0 (Success) 1 (Failure) 2 (exit)
 */

int my_builtin(info_f *info)
{
int i, builtin_return_value = -1;
builtin_cmds builtints[] = {
{"cd", my_cd},
{"env", my_printenv},
{"exit", my_exit},
{"help", my_help},
{"alias", my_alias},
{"setenv", my_check_setenv},
{"history", my_history},
{"unsetenv", my_check_unsetenv},
{NULL, NULL}};

for (i = 0; builtints[i].type; i++)
if (my_strcmp(info->argv[0], builtints[i].type) == 0)
{
info->lines++;
builtin_return_value = builtints[i].func(info);
break;
}
return (builtin_return_value);
}

/**
 * my_check_command - searches for a command in PATH
 * @info: a pointer to the parameter and return info struct
 *
 * Return: Nothing
 */
void my_check_command(info_f *info)
{
char *path = NULL;
int i, word_count;
info->path = info->argv[0];
if (info->lc_flag == 1)
{
info->lines++;
info->lc_flag = 0;
}
for (i = 0, word_count = 0; info->arg[i]; i++)
if (!my_is_delimiter(info->arg[i], " \t\n"))
word_count++;
if (!word_count)
return;
path = my_check_file_in_path(info, my_getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
my_create_process(info);
}
else
{
if ((my_from_terminal(info) || my_getenv(info, "PATH=") || info->argv[0][0] == '/') && my_is_executable(info, info->argv[0]))
my_create_process(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
my_print_error(info, "Permission denied\n");
}
}
}

/**
 * my_create_process - forks a new process to run the command
 * @info: pointer to the parameter
 *
 * Return: Nothing
 */

void my_create_process(info_f *info)
{
pid_t pid;

pid = fork();
if (pid == -1)
{
/* ERROR FUNCTION */
perror("Error:");
return;
}
/* Child process */
if (pid == 0)
{
if (execve(info->path, info->argv, my_get_environ(info)) == -1)
{
my_free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
/* Parent process */
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
/* Set return status to child's exit status */
info->status = WEXITSTATUS(info->status);

/* Print error message for permission denied errors */
if (info->status == 126)
my_print_error(info, "Permission denied\n");
}
}
}
