#include "shell.h"
/**
 * main - Entry point to shell program
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 (Success) 1 (Failure)
 */

int main(int argc, char **argv)
{
info_f info[] = { SET_INFO };
int fd = 2;
asm("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (fd)
	: "r" (fd));
if (argc == 2)
{
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
my_puts_err(argv[0]);
my_puts_err(": 0: Can't open ");
my_puts_err(argv[1]);
my_putchar_err('\n');
my_putchar_err(NEG_ONE);
exit(127);
}
return (EXIT_FAILURE);
}
info->fd_read = fd;
}
my_gather_env(info);
my_read_history(info);
my_shell(info, argv);

return (EXIT_SUCCESS);
}

