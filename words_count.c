#include "shell.h"

/**
 * my_words_count - counts the number of words in a string
 * @str: String to be parsed.
 * @separators: One or more delimiters to separate the string
 * @arr: Pointer to array where the word lengths will be stored
 *
 * Return:  Number of words
 */
int my_words_count(char *str, char *separators, unsigned int *arr)
{
unsigned int c, d, word_len = 1;
unsigned int word_count = 0;
char *str_copy = str;
bool start = false, delimiter;

if (!str)
return (0);

while (!start)
for (d = 0; separators[d]; d++)
{
if (*str_copy == separators[d])
str_copy++;
else
start = true;
}

if (!*(str_copy + 1))
{
arr[0] = 1;
return (1);
}

for (c = 1; str_copy[c]; c++)
{
delimiter = my_is_delimiter(str_copy[c], separators);

if (delimiter && !(my_is_delimiter(str_copy[c - 1], separators)))
{
arr[word_count] = word_len;
word_count++;
}

if ((!str_copy[c + 1]) && !delimiter)
{
word_len++;
arr[word_count] = word_len;
word_count++;
break;
}

if (!delimiter)
word_len++;
else
word_len = 0;
}

return (word_count);
}

