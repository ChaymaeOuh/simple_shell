#include "shell.h"

/**
 * my_from_terminal - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int my_from_terminal(info_f *info)
{
	return (isatty(STDIN_FILENO) && info->fd_read <= 2);
}

/**
 * my_isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic else 0 if not
 */

int my_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * my_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string else converted integer
 */

int my_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * my_is_delimiter - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delim: String of charaters to be compated.
 *
 * This function compares a character to one or more of delimiters
 * to see if the character matches any of the delimiters.
 *
 * Return: True if it is a delimiter, else false.
 */

int my_is_delimiter(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}

